#pragma once

#include "PlanStorageBuffer.h"
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

    void storePlan(QString const& name, std::shared_ptr<Plan> const&);

    [[nodiscard]] QList<QString> nameOfAllPlans() const;

    [[nodiscard]] bool containsPlan(QString const& name) const;

    [[nodiscard]] std::shared_ptr<Plan> loadPlan(QString const& name);
    void deletePlan(QString const& name);

    void initialize();

    void setPlanBuffer(PlanStorageBuffer* newBuffer);

    [[nodiscard]] QString getName(size_t const& index) const;
    [[nodiscard]] std::shared_ptr<Plan> getPlan(size_t const& index) const;

protected:
    [[nodiscard]] static QString getDatabaseDefaultPath();
    [[nodiscard]] bool databaseExists();
    void createDatabase();

    [[nodiscard]] static QString planToString(std::shared_ptr<Plan> const&);
    [[nodiscard]] QSqlQuery transformToWriteQuery(QString const& name, std::shared_ptr<Plan> const& plan);
    [[nodiscard]] QSqlQuery transformToInsertQuery(QString const& name, std::shared_ptr<Plan> const& plan);
    [[nodiscard]] QSqlQuery transformToUpdateQuery(QString const& name, std::shared_ptr<Plan> const& plan);
    [[nodiscard]] QSqlQuery transformToReadQuery(QString const& name);

    void loadAllPlans();

    std::shared_ptr<QSqlDatabase> database;
    QString databasePath;

    void createDatabaseFolder();

private:
    std::unique_ptr<PlanStorageBuffer> planBuffer{};
};
