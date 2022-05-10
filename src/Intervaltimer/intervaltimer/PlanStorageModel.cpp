#include "PlanStorageModel.h"

PlanStorageModel* PlanStorageModel::instance = nullptr;

PlanStorageModel::PlanStorageModel(QObject* parent)
    : QAbstractListModel{parent} {
    databaseProvider->initialize();
}

PlanStorageModel* PlanStorageModel::create(QQmlEngine* /* unused */, QJSEngine* engine) {
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
    if (role == nameRole) {
        return databaseProvider->getName(index.row());
    }
    if (role == planRole) {
        return QVariant::fromValue(databaseProvider->getPlan(index.row()));
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
    databaseProvider->storePlan(name, plan);
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

bool PlanStorageModel::containsPlan(const QString& name) const { return databaseProvider->containsPlan(name); }
