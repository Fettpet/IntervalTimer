#include "PlanModel.h"
#include "PlanFromJson.h"
#include "PlanToJson.h"
#include <QFile>
#include <QJsonDocument>
#include <stdexcept>

PlanModel* PlanModel::instance = nullptr;

PlanModel::PlanModel(QObject* parent)
    : QAbstractItemModel(parent)
    , rootPlan(new Plan{}) {}

int PlanModel::rowCount(const QModelIndex& parent) const {
    if (parent.column() > 0) {
        return 0;
    }
    std::shared_ptr<Plan> parentItem;
    if (!parent.isValid()) {
        parentItem = rootPlan;
    }
    else if (parent.internalPointer() != nullptr)
        parentItem = static_cast<Plan*>(parent.internalPointer())->shared_from_this();
    else {
        return 0;
    }
    return parentItem->getNumberItems();
}

int PlanModel::columnCount(const QModelIndex& parent) const { return 2; }

QModelIndex PlanModel::index(int row, int column, const QModelIndex& parent) const {
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }
    std::shared_ptr<Plan> parentItem;

    if (!parent.isValid())
        parentItem = rootPlan;
    else if (parent.internalPointer() != nullptr) {
        parentItem = static_cast<Plan*>(parent.internalPointer())->shared_from_this();
    }
    else {
        qWarning() << "Should not happen";
        return QModelIndex();
    }
    QVariant childItem = parentItem->getItemAt(row);
    if (childItem.isNull()) {
        return QModelIndex();
    }
    if (containsPlan(childItem)) {
        auto newIndex = createIndex(row, planColumn, childItem.value<std::shared_ptr<Plan>>().get());
        return newIndex;
    }
    if (containsInterval(childItem)) {
        auto newIndex = createIndex(row, intervalColumn, parentItem.get());
        return newIndex;
    }
    return QModelIndex();
}

QVariant PlanModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) return QVariant();

    switch (role) {
    case isIntervalRole: return QVariant(containsInterval(index));
    case isPlanRole: return QVariant(containsPlan(index));
    }

    auto itemPtr = static_cast<Plan*>(index.internalPointer())->shared_from_this();

    if (containsPlan(index)) {
        switch (role) {
        case nameRole: return QVariant::fromValue(itemPtr->getName());
        case subPlanRole: {
            auto result = new PlanModel(const_cast<PlanModel*>(this));
            result->setPlan(itemPtr);
            return QVariant::fromValue(result);
        }
        default: return QVariant{};
        }
    }
    if (containsInterval(index)) {
        auto item = itemPtr->getItemAt(index.row()).value<Interval>();
        switch (role) {
        case descriptionRole: return QVariant::fromValue(item.getDescription());
        case durationRole: return QVariant::fromValue(item.getDuration<std::chrono::seconds>().count());
        default: return QVariant{};
        }
    }

    return QVariant{};
}

bool PlanModel::isDataSetable(const QModelIndex& index, const QVariant& value, int role) const {
    if (!rootPlan) return false;
    if (data(index, role) == value) {
        return false;
    }
    switch (role) {
    case isIntervalRole: [[fallthrough]];
    case isPlanRole: //
        qWarning() << "This should not happen";
        return false;
    }
    return true;
}

bool PlanModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (!isDataSetable(index, value, role)) {
        return false;
    }

    auto itemPtr = static_cast<Plan*>(index.internalPointer())->shared_from_this();

    if (containsPlan(index)) {
        switch (role) {
        case nameRole: //
            itemPtr->setName(value.toString());
            emit dataChanged(index, index, QVector<int>() << role);
            return true;
        case subPlanRole: {
            qWarning() << "This should not happen";
            return false;
        }
        default: return false;
        }
    }
    if (containsInterval(index)) {
        auto interval = itemPtr->getItemAt(index.row()).value<Interval>();
        switch (role) {
        case descriptionRole: {
            interval.setDescripton(value.toString());
            break;
        }
        case durationRole: {
            interval.setDuration(std::chrono::seconds{value.toInt()});
            break;
        }
        default: {
            auto roleName = roleNames()[role];
            qWarning() << "Role " << roleName << " is not useable in Interval";
            return false;
        }
        }
        rootPlan->setItemAt(index.row(), interval);
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags PlanModel::flags(const QModelIndex& index) const {
    if (!index.isValid()) return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}

QModelIndex PlanModel::parent(const QModelIndex& index) const {
    if (!index.isValid()) return QModelIndex();
    auto* currentPlan = static_cast<Plan*>(index.internalPointer());

    if (containsPlan(index)) {
        auto parentItem = currentPlan->getParentPlan();
        if (parentItem.expired()) {
            return QModelIndex();
        }
        auto parentPtr = parentItem.lock();
        if (parentPtr == rootPlan || parentPtr == nullptr) return QModelIndex();

        return createIndex(parentPtr->getRow(), planColumn, parentPtr.get());
    }
    if (containsInterval(index)) {
        return createIndex(currentPlan->getRow(), planColumn, currentPlan);
    }
    return QModelIndex();
}

QHash<int, QByteArray> PlanModel::roleNames() const {
    QHash<int, QByteArray> names;
    names[durationRole] = "duration";
    names[descriptionRole] = "description";
    names[subPlanRole] = "subPlan";
    names[nameRole] = "name";
    names[isIntervalRole] = "isInterval";
    names[isPlanRole] = "isPlan";

    return names;
}

std::weak_ptr<Plan> PlanModel::getPlan() const { return rootPlan; }

void PlanModel::setPlan(std::shared_ptr<Plan> newPlan) {
    if (newPlan.use_count() == 0) {
        throw std::invalid_argument("setPlan must contain a plan");
    }
    beginResetModel();
    rootPlan = newPlan;
    endResetModel();
}

QString PlanModel::getName() const { return rootPlan->getName(); }

void PlanModel::setName(const QString& name) { rootPlan->setName(name); }

void PlanModel::setRepetitionCount(const int& counter) { rootPlan->setNumberRepetitions(counter); }
int PlanModel::getRepetitionCount() const { return rootPlan->getNumberRepetitions(); }

void PlanModel::appendInterval() {
    beginInsertRows(QModelIndex(), rootPlan->getNumberItems(), rootPlan->getNumberItems());
    rootPlan->appendInterval();
    endInsertRows();
}

void PlanModel::appendPlan() {
    beginInsertRows(QModelIndex(), rootPlan->getNumberItems(), rootPlan->getNumberItems());
    rootPlan->appendPlan();
    endInsertRows();
}

void PlanModel::removeItem(const int& index) {
    beginRemoveRows(QModelIndex(), index, index);
    rootPlan->removeItem(index);
    endRemoveRows();
}

void PlanModel::reset() {
    beginResetModel();
    emit changedRepetitions();
    emit changedName();
    endResetModel();
}

PlanModel* PlanModel::create(QQmlEngine*, QJSEngine* engine) {
    if (!instance) {
        instance = new PlanModel{};
    }
    return instance;
}

bool PlanModel::containsPlan(const QModelIndex& index) { return index.column() == planColumn; }

bool PlanModel::containsInterval(const QModelIndex& index) { return index.column() == intervalColumn; }

bool PlanModel::containsPlan(const QVariant& variant) { return variant.canConvert<std::shared_ptr<Plan>>(); }

bool PlanModel::containsInterval(const QVariant& variant) { return variant.canConvert<Interval>(); }
