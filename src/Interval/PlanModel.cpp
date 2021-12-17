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
    Plan* parentItem;
    if (!parent.isValid()) {
        parentItem = rootPlan.get();
    }
    else if (parent.internalPointer() != nullptr)
        parentItem = static_cast<Plan*>(parent.internalPointer());
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
    if (childItem.canConvert<std::shared_ptr<Plan>>()) {
        auto newIndex = createIndex(row, 0, childItem.value<std::shared_ptr<Plan>>().get());
        return newIndex;
    }
    else if (childItem.canConvert<Interval>()) {
        auto newIndex = createIndex(row, 1, parentItem.get());
        return newIndex;
    }
    return QModelIndex();
}

QVariant PlanModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) return QVariant();

    Plan* itemPtr = static_cast<Plan*>(index.internalPointer());

    switch (role) {
    case isIntervalRole: return QVariant(item.canConvert<Interval>());
    case isPlanRole: return QVariant(item.canConvert<std::shared_ptr<Plan>>());
    }

    // if (item.canConvert<std::shared_ptr<Plan>>()) {

    if (index.column() == 0) {
        switch (role) {
        case nameRole: return QVariant::fromValue(itemPtr->getName());
        default: return QVariant{};
        }
    }
    if (containsInterval(index)) {
        return QVariant::fromValue(itemPtr->getItemAt(index.row()).value<Interval>().getDescripton());
    }
    // }
    // }

    // switch (role) {
    // case descriptionRole: return QVariant::fromValue(QString::fromStdString(item.value<Interval>().getDescripton()));
    // case durationRole: return
    // QVariant::fromValue(item.value<Interval>().getDuration<std::chrono::seconds>().count()); default:
    //     qWarning() << "Fix Default to QVariant" << QString::fromStdString(item.value<Interval>().getDescripton());
    // return QVariant::fromValue(QString::fromStdString(item.value<Interval>().getDescripton()));
    //    }
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

    if (index.column() == 0) {

        auto parentItem = currentPlan->getParentPlan();
        if (parentItem.expired()) {
            return QModelIndex();
        }
        auto parentPtr = parentItem.lock();
        if (parentPtr == rootPlan || parentPtr == nullptr) return QModelIndex();

        return createIndex(parentPtr->getRow(), 0, parentPtr.get());
    }
    else if (index.column() == 1) {
        return createIndex(currentPlan->getRow(), 0, currentPlan);
    }
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
