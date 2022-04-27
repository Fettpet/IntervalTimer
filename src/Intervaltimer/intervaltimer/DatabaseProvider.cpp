#include "DatabaseProvider.h"
#include "PlanFromJson.h"
#include "PlanToJson.h"
#include <QDir>
#include <QFileInfo>
#include <QJsonDocument>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QSysInfo>
#include <exception>
#include <utility>

DatabaseProvider::DatabaseProvider()
    : database(new QSqlDatabase{})
    , databasePath(getDatabaseDefaultPath()) {}

void DatabaseProvider::setDatabasePath(const QString& path) { databasePath = path; }

void DatabaseProvider::setDatabase(std::shared_ptr<QSqlDatabase> newDatabase) { database = std::move(newDatabase); }

void DatabaseProvider::storePlan(QString const& name, const std::shared_ptr<Plan>& plan) {
    QSqlQuery query;
    if (planBuffer.contains(name)) {
        query = transformToUpdateQuery(name, plan);
    }
    else {
        query = transformToWriteQuery(name, plan);
    }
    query.exec();
    planBuffer.insert(name, Plan::copy(plan));
}

QList<QString> DatabaseProvider::nameOfAllPlans() const { return planBuffer.keys(); }

std::shared_ptr<Plan> DatabaseProvider::loadPlan(QString const& name) {
    if (planBuffer.contains(name)) {
        return Plan::copy(planBuffer.value(name));
    }

    auto query = transformToReadQuery(name);
    Q_ASSERT(query.exec());
    Q_ASSERT(query.first());
    Q_ASSERT(query.isValid());

    QSqlRecord rec = query.record();
    auto text = rec.value(0).toString();
    return PlanFromJson::transform(text);
}

void DatabaseProvider::deletePlan(const QString& name) {
    QSqlQuery query(*database);
    query.prepare(
        "DELETE FROM Plans "
        "WHERE name = :name;");
    query.bindValue(":name", name);
    query.exec();
    planBuffer.remove(name);
}

void DatabaseProvider::initialize() {
    auto const bufferDatabaseExists = databaseExists();
    *database = QSqlDatabase::addDatabase("QSQLITE");
    database->setDatabaseName(databasePath);
    if (!bufferDatabaseExists) {
        createDatabaseFolder();
    }
    if (!database->open()) {
        qWarning() << "ERROR: " << database->lastError();
        return;
    }
    if (!bufferDatabaseExists) {
        createDatabase();
    }
    loadAllPlans();
}

QMap<QString, std::shared_ptr<Plan>>::const_iterator DatabaseProvider::beginPlans() const {
    return planBuffer.cbegin();
}
QMap<QString, std::shared_ptr<Plan>>::const_iterator DatabaseProvider::endPlans() const { return planBuffer.cend(); }

QString DatabaseProvider::getDatabaseDefaultPath() {
    if (QSysInfo::productType() == "windows" || QSysInfo::productType() == "winrt") {
        return QFile(QDir::homePath() + QDir::separator() + ".intervaltimer" + QDir::separator() + "storage.sqlite")
            .fileName();
    }
    if (QSysInfo::productType() == "android") {
        return QFile(QDir::homePath() + QDir::separator() + ".intervaltimer" + QDir::separator() + "storage.sqlite")
            .fileName();
    }
    if (QSysInfo::kernelType() == "linux") {
        return QFile(QDir::homePath() + QDir::separator() + ".intervaltimer" + QDir::separator() + "storage.sqlite")
            .fileName();
    }
    throw std::runtime_error("Operating System not supported");
}

void DatabaseProvider::createDatabaseFolder() {
    QFileInfo file(databasePath);
    QDir dir = file.absoluteDir().path();
    dir.mkdir(file.absoluteDir().path());
}

bool DatabaseProvider::databaseExists() { return databasePath != ":memory:" && QFileInfo::exists(databasePath); }

void DatabaseProvider::createDatabase() {

    QSqlQuery query("CREATE TABLE Plans (name TEXT PRIMARY KEY, plan TEXT)", *database);
    query.exec();
}

QString DatabaseProvider::planToString(const std::shared_ptr<Plan>& plan) {
    auto jsonObject = PlanToJson::transform(*plan);
    QJsonDocument document(jsonObject);
    auto string = document.toJson();
    return string;
}

QSqlQuery DatabaseProvider::transformToWriteQuery(const QString& name, const std::shared_ptr<Plan>& plan) {
    QSqlQuery query(*database);
    auto planStr = planToString(plan);
    query.prepare(
        "INSERT INTO Plans (name, plan) "
        "VALUES (:name, :plan);");
    query.bindValue(":name", name);
    query.bindValue(":plan", planStr);
    return query;
}

QSqlQuery DatabaseProvider::transformToUpdateQuery(const QString& name, const std::shared_ptr<Plan>& plan) {
    QSqlQuery query(*database);
    auto planStr = planToString(plan);
    query.prepare(
        "UPDATE Plans"
        "SET plan = :plan"
        "WHERE name = :name;");
    query.bindValue(":name", name);
    query.bindValue(":plan", planStr);
    return query;
}

QSqlQuery DatabaseProvider::transformToReadQuery(const QString& name) {
    QSqlQuery query(*database);
    query.prepare("Select plan from Plans where name = :name;");
    query.bindValue(":name", name);
    return query;
}

void DatabaseProvider::loadAllPlans() {
    QSqlQuery query("SELECT name, plan FROM Plans", *database);
    if (query.exec() && query.first()) {
        do {
            auto record = query.record();
            auto name = record.value("name").toString();
            auto plan = record.value("plan").toString();
            planBuffer[name] = PlanFromJson::transform(plan);
        } while (query.next());
    }
}

bool DatabaseProvider::containsPlan(const QString& name) const { return planBuffer.contains(name); }
