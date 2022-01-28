#pragma once

#include <Plan.h>
#include <QDir>
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

    QVector<QString> nameOfAllPlans();

    Plan loadPlan(QString const& name);

    void initialize();

protected:
    static QString getDatabaseDefaultPath();
    bool databaseExists();
    void createDatabase();

    static QString planToString(Plan const&);
    QSqlQuery transformToWriteQuery(QString const& name, Plan const& plan);
    QSqlQuery transformToReadQuery(QString const& name);
    static bool nameIsValid(QString const&);

    std::shared_ptr<QSqlDatabase> database;
    QString databasePath;

    void createDatabaseFolder();

};
