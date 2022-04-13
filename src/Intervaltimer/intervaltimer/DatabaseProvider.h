#pragma once

#include <Plan.h>
#include <QDir>
#include <QMap>
#include <QObject>
#include <QSqlDatabase>
#include <QString>
#include <memory>

class DatabaseProvider : public QObject {
    Q_OBJECT

public:
    DatabaseProvider();

    void setDatabasePath(QString const&);
    void setDatabase(std::shared_ptr<QSqlDatabase> database);

    void storePlan(QString const& name, Plan const&);

    [[nodiscard]] QList<QString> nameOfAllPlans() const;

    [[nodiscard]] bool containsPlan(QString const& name) const;

    [[nodiscard]] Plan loadPlan(QString const& name);
    void deletePlan(QString const& name);

    void initialize();

    [[nodiscard]] QMap<QString, Plan>::const_iterator beginPlans() const;
    [[nodiscard]] QMap<QString, Plan>::const_iterator endPlans() const;

protected:
    static QString getDatabaseDefaultPath();
    bool databaseExists();
    void createDatabase();

    static QString planToString(Plan const&);
    QSqlQuery transformToWriteQuery(QString const& name, Plan const& plan);
    QSqlQuery transformToUpdateQuery(QString const& name, Plan const& plan);
    QSqlQuery transformToReadQuery(QString const& name);

    void loadAllPlans();

    std::shared_ptr<QSqlDatabase> database;
    QString databasePath;

    void createDatabaseFolder();

private:
    QMap<QString, Plan> planBuffer;
};
