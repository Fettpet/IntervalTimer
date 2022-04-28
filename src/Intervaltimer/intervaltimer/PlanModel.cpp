#include "PlanModel.h"
#include "PlanFromJson.h"
#include "PlanToJson.h"
#include <QFile>
#include <QJsonDocument>
#include <stdexcept>

PlanModel::PlanModel(QObject* parent)
    : QAbstractItemModel(parent)
    , rootPlan(Plan::create()) {}

int PlanModel::rowCount(const QModelIndex& parent) const {
    if (parent.column() > 0) {
        return 0;
    }
    auto parentItem = extractParentPlan(parent);
    return parentItem->getNumberItems();
}

int PlanModel::columnCount(const QModelIndex& parent) const { return 2; }

std::shared_ptr<Plan> PlanModel::extractParentPlan(const QModelIndex& parent) const {
    if (parent.isValid() && parent.internalPointer() != nullptr) {
        return static_cast<Plan*>(parent.internalPointer())->shared_from_this();
    }
    return rootPlan;
}

QModelIndex PlanModel::index(int row, int column, const QModelIndex& parent) const {
    if (!hasIndex(row, column, parent)) {
        return {};
    }
    auto parentItem = extractParentPlan(parent);

    QVariant childItem = parentItem->getItemAt(row);
    if (childItem.isNull()) {
        return {};
    }
    if (containsPlan(childItem)) {
        auto newIndex = createIndex(row, planColumn, childItem.value<std::shared_ptr<Plan>>().get());
        return newIndex;
    }
    if (containsInterval(childItem)) {
        auto newIndex = createIndex(row, intervalColumn, parentItem.get());
        return newIndex;
    }
    return {};
}

QVariant PlanModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) return {};

    switch (role) {
    case isIntervalRole: return {containsInterval(index)};
    case isPlanRole: return {containsPlan(index)};
    }

    if (containsPlan(index)) {
        return getDataForPlan(index, role);
    }
    if (containsInterval(index)) {
        return getDataForInterval(index, role);
    }

    return QVariant{};
}

QVariant PlanModel::getDataForPlan(const QModelIndex& index, int role) const {
    Q_ASSERT(containsPlan(index));

    switch (role) {
    case nameRole: {
        auto itemPtr = static_cast<Plan*>(index.internalPointer())->shared_from_this();
        return QVariant::fromValue(itemPtr->getName());
    }
    case repetitionCountRole: {
        auto itemPtr = static_cast<Plan*>(index.internalPointer())->shared_from_this();
        return QVariant::fromValue(itemPtr->getNumberRepetitions());
    }
    default: return QVariant{};
    }
}

QVariant PlanModel::getDataForInterval(const QModelIndex& index, int role) const {
    Q_ASSERT(containsInterval(index));
    auto itemPtr = static_cast<Plan*>(index.internalPointer())->shared_from_this();
    auto item = itemPtr->getItemAt(index.row()).value<Interval>();
    switch (role) {
    case descriptionRole: return QVariant::fromValue(item.getDescription());
    case durationRole: return QVariant::fromValue(item.getDuration<std::chrono::seconds>().count());
    default: return QVariant{};
    }
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
        return setDataForPlan(index, value, role);
    }
    if (containsInterval(index)) {
        return setDataForInterval(index, value, role);
    }
    return false;
}

bool PlanModel::setDataForPlan(const QModelIndex& index, const QVariant& value, int role) {
    Q_ASSERT(containsPlan(index));
    auto itemPtr = static_cast<Plan*>(index.internalPointer())->shared_from_this();
    switch (role) {
    case nameRole: //
        itemPtr->setName(value.toString());
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    case repetitionCountRole:
        itemPtr->setNumberRepetitions(value.toUInt());
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    default: return false;
    }
}

bool PlanModel::setDataForInterval(const QModelIndex& index, const QVariant& value, int role) {
    Q_ASSERT(containsInterval(index));
    auto itemPtr = static_cast<Plan*>(index.internalPointer())->shared_from_this();
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
        auto names = roleNames();
        auto roleName = names[role];
        qWarning() << "Role " << roleName << " is not useable in Interval";
        return false;
    }
    }
    rootPlan->setItemAt(index.row(), interval);
    emit dataChanged(index, index, QVector<int>() << role);
    if (role == durationRole) {
        emit changeHasZeroDuration();
    }
    return true;
}

Qt::ItemFlags PlanModel::flags(const QModelIndex& index) const {
    if (!index.isValid()) return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}

QModelIndex PlanModel::parent(const QModelIndex& index) const {
    if (!index.isValid()) return {};
    auto* currentPlan = static_cast<Plan*>(index.internalPointer());

    if (containsPlan(index)) {
        auto parentItem = currentPlan->getParentPlan();
        if (parentItem.expired()) {
            return {};
        }
        auto parentPtr = parentItem.lock();
        if (parentPtr == rootPlan || parentPtr == nullptr) return {};

        return createIndex(parentPtr->getRow(), planColumn, parentPtr.get());
    }
    if (containsInterval(index)) {
        return createIndex(currentPlan->getRow(), planColumn, currentPlan);
    }
    return {};
}

QHash<int, QByteArray> PlanModel::roleNames() const {
    QHash<int, QByteArray> names;
    names[durationRole] = "duration";
    names[descriptionRole] = "description";
    names[nameRole] = "name";
    names[isIntervalRole] = "isInterval";
    names[isPlanRole] = "isPlan";
    names[repetitionCountRole] = "repetionCount";

    return names;
}

std::weak_ptr<Plan> PlanModel::getPlan() const { return rootPlan; }

void PlanModel::setPlan(std::shared_ptr<Plan> const& newPlan) {
    if (newPlan.use_count() == 0) {
        throw std::invalid_argument("setPlan must contain a plan");
    }
    beginResetModel();
    rootPlan = newPlan;
    endResetModel();
}

bool PlanModel::getHasZeroDuration() const { return rootPlan->getDuration().count() == 0; }

void PlanModel::appendInterval(const QModelIndex& parent) {
    if (containsInterval(parent)) return;

    auto plan = extractParentPlan(parent);
    beginInsertRows(parent, plan->getNumberItems(), plan->getNumberItems());
    plan->appendInterval();
    endInsertRows();
    emit changeHasZeroDuration();
}

void PlanModel::appendPlan(const QModelIndex& parent) {
    if (containsInterval(parent)) return;
    auto plan = extractParentPlan(parent);

    beginInsertRows(parent, plan->getNumberItems(), plan->getNumberItems());
    plan->appendPlan();
    endInsertRows();
}

void PlanModel::removeItem(const QModelIndex& parent) {
    if (containsInterval(parent)) {
        removeInterval(parent);
        return;
    };
    if (containsPlan(parent)) {
        removePlan(parent);
        return;
    }
    throw std::invalid_argument("Neightor a plan nor an interval");
}

void PlanModel::removeInterval(const QModelIndex& index) {
    auto plan = extractParentPlan(index);
    auto toDeleteRow = index.row();
    if (plan->getNumberItems() <= toDeleteRow) return;
    beginRemoveRows(parent(index), toDeleteRow, toDeleteRow);
    plan->removeItem(toDeleteRow);
    endRemoveRows();
    emit changeHasZeroDuration();
}

void PlanModel::removePlan(const QModelIndex& index) {
    auto plan = extractParentPlan(index);
    auto toDeleteRow = index.row();
    auto parentPlan = plan->getParentPlan();

    if (parentPlan.expired()) return;
    if (parentPlan.lock()->getNumberItems() <= toDeleteRow) return;

    beginRemoveRows(parent(index), toDeleteRow, toDeleteRow);
    parentPlan.lock()->removeItem(toDeleteRow);
    endRemoveRows();
    emit changeHasZeroDuration();
}

void PlanModel::reset() {
    beginResetModel();
    emit changeHasZeroDuration();
    endResetModel();
}

bool PlanModel::containsPlan(const QModelIndex& index) { return index.column() == planColumn; }

bool PlanModel::containsInterval(const QModelIndex& index) { return index.column() == intervalColumn; }

bool PlanModel::containsPlan(const QVariant& variant) { return variant.canConvert<std::shared_ptr<Plan>>(); }

bool PlanModel::containsInterval(const QVariant& variant) { return variant.canConvert<Interval>(); }
