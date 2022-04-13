#pragma once
#include "DatabaseProvider.h"
#include "Plan.h"
#include <QAbstractListModel>
#include <QQmlEngine>
#include <QtQml/qqmlregistration.h>
#include <memory>

class PlanStorageModel : public QAbstractListModel {
    Q_OBJECT
    QML_SINGLETON
    QML_NAMED_ELEMENT(PlanStorageModel)

    explicit PlanStorageModel(QObject* parent = nullptr);
    static PlanStorageModel* instance;

public:
    static PlanStorageModel* create(QQmlEngine*, QJSEngine* engine);

    enum { nameRole = Qt::UserRole, planRole };

    // Basic functionality:
    [[nodiscard]] int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    [[nodiscard]] QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void appendPlan(QString const& name);
    Q_INVOKABLE void removePlan(QString const& name);
    Q_INVOKABLE void loadPlan(QString const& name);
    [[nodiscard]] Q_INVOKABLE bool containsPlan(QString const& name) const;

    void setDatabaseProvider(DatabaseProvider*);
    void setPlan(std::shared_ptr<Plan> const&);

signals:
    void planChanged();

protected:
    DatabaseProvider* databaseProvider{new DatabaseProvider{}};
    std::shared_ptr<Plan> plan{nullptr};
};
