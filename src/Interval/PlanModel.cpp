#include "PlanModel.h"
#include <stdexcept>

PlanModel::PlanModel(QObject* parent)
    : QAbstractItemModel(parent)
    , rootPlan(new Plan{}) {}

QVariant PlanModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) return QVariant(rootPlan->getName());

    return QVariant();
}

// bool PlanModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant& value, int role) {
//     if (value != headerData(section, orientation, role)) {
//         // FIXME: Implement me!
//         emit headerDataChanged(orientation, section, section);
//         return true;
//     }
//     return false;
// }

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
        case descriptionRole: return QVariant::fromValue(item.getDescripton());
        case durationRole: return QVariant::fromValue(item.getDuration<std::chrono::seconds>().count());
        default: return QVariant{};
        }
    }

    return QVariant{};
}

bool PlanModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    // if (!rootPlan) return false;
    // if (data(index, role) == value) {
    //     return false;
    // }

    // auto item = rootPlan->getItemAt(index.row());
    // if (item.canConvert<std::shared_ptr<Plan>>()) {
    //     auto plan = item.value<std::shared_ptr<Plan>>();
    //     switch (role) {
    //     case nameRole: {
    //         plan->setName(value.toString());
    //         break;
    //     }
    //     case subPlanRole: {
    //         break;
    //     }
    //     default: {
    //         auto roleName = roleNames()[role];
    //         qWarning() << "Role " << roleName << " is not useable in Interval";
    //         return false;
    //     }
    //     }

    //     plan->setItemAt(index.row(), plan);
    //     emit dataChanged(index, index, QVector<int>() << role);
    //     return true;
    // }

    // if (item.canConvert<Interval>()) {
    //     auto interval = item.value<Interval>();
    //     switch (role) {
    //     case descriptionRole: {
    //         interval.setDescripton(value.toString().toStdString());
    //         break;
    //     }
    //     case durationRole: {
    //         interval.setDuration(std::chrono::seconds{value.toInt()});
    //         break;
    //     }
    //     default: {
    //         auto roleName = roleNames()[role];
    //         qWarning() << "Role " << roleName << " is not useable in Interval";
    //         return false;
    //     }
    //     }

    //     rootPlan->setItemAt(index.row(), interval);
    //     emit dataChanged(index, index, QVector<int>() << role);
    //     return true;
    // }

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

// bool PlanModel::insertRows(int row, int count, const QModelIndex& parent) {
//     beginInsertRows(parent, row, row + count - 1);
//     // FIXME: Implement me!
//     endInsertRows();
//     return true;
// }

// bool PlanModel::removeRows(int row, int count, const QModelIndex& parent) {
//     beginRemoveRows(parent, row, row + count - 1);
//     // FIXME: Implement me!
//     endRemoveRows();
//     return true;
// }

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
    rootPlan = newPlan;
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

bool PlanModel::containsPlan(const QModelIndex& index) { return index.column() == planColumn; }

bool PlanModel::containsInterval(const QModelIndex& index) { return index.column() == intervalColumn; }

bool PlanModel::containsPlan(const QVariant& variant) { return variant.canConvert<std::shared_ptr<Plan>>(); }

bool PlanModel::containsInterval(const QVariant& variant) { return variant.canConvert<Interval>(); }

// void PlanModel::setPlan(Plan* newPlan) {
//     beginResetModel();
//     rootPlan = newPlan;
//     // TODO
//     // if (plan) {
//     //     plan->disconnect(this);
//     // }
//     // plan = newPlan;
//     // if (plan) {
//     //     connect(plan, &Plan::preItemAppended, this, [=]() {
//     //         const int index = plan->getNumberItems();
//     //         beginInsertRows(QModelIndex(), index, index);
//     //     });
//     //     connect(plan, &Plan::postItemAppended, this, [=]() { endInsertRows(); });
//     //     connect(plan, &Plan::preItemRemoved, this, [=](size_t index) { beginRemoveRows(QModelIndex(), index,
//     index);
//     //     }); connect(plan, &Plan::postItemRemoved, this, [=]() { endRemoveRows(); });
//     // }
//     endResetModel();
// }
