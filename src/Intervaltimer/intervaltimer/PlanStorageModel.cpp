#include "PlanStorageModel.h"

PlanStorageModel* PlanStorageModel::instance = nullptr;

PlanStorageModel::PlanStorageModel(QObject* parent)
    : QAbstractListModel{parent} {
    databaseProvider->initialize();
}

PlanStorageModel* PlanStorageModel::create(QQmlEngine*, QJSEngine* engine) {
    if (instance == nullptr) {
        instance = new PlanStorageModel{};
    }
    return instance;
}

int PlanStorageModel::rowCount(const QModelIndex& parent) const {
    Q_ASSERT(databaseProvider != nullptr);
    return databaseProvider->nameOfAllPlans().size();
}

QVariant PlanStorageModel::data(const QModelIndex& index, int role) const {
    auto counter = 0;
    auto iter = databaseProvider->beginPlans();
    while (counter < index.row()) {
        ++iter;
        ++counter;
    }
    if (role == nameRole) {
        return iter.key();
    }
    if (role == planRole) {
        return QVariant::fromValue(iter.value());
    }
    return QVariant{};
}

QHash<int, QByteArray> PlanStorageModel::roleNames() const {
    QHash<int, QByteArray> names;
    names[nameRole] = "nameRole";
    names[planRole] = "planRole";
    return names;
}

void PlanStorageModel::appendPlan(const QString& name) {
    beginResetModel();
    databaseProvider->storePlan(name, *plan);
    endResetModel();
}

void PlanStorageModel::removePlan(const QString& name) {
    beginResetModel();
    databaseProvider->deletePlan(name);
    endResetModel();
}

void PlanStorageModel::loadPlan(const QString& name) {
    beginResetModel();
    (*plan) = databaseProvider->loadPlan(name);
    endResetModel();
    emit planChanged();
}

void PlanStorageModel::setDatabaseProvider(DatabaseProvider* provider) { databaseProvider = provider; }

void PlanStorageModel::setPlan(const std::shared_ptr<Plan>& newPlan) { plan = newPlan; }
