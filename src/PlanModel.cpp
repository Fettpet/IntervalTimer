#include "PlanModel.h"

PlanModel::PlanModel(QObject* parent)
    : QAbstractListModel(parent) {}

QVariant PlanModel::headerData(int section, Qt::Orientation orientation, int role) const {
    // FIXME: Implement me!
    return {};
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
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !plan) return 0;

    return plan->getItems().size();
}

QVariant PlanModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || !plan) return QVariant();

    auto const& item = plan->getItems().at(index.row());
    if (item.canConvert<Plan*>()) {
        // todo fixme
        return QVariant();
    }

    switch (role) {
    case descriptionRole: return QVariant::fromValue(QString::fromStdString(item.value<Interval>().getDescripton()));
    case durationRole: return QVariant::fromValue(item.value<Interval>().getDuration<std::chrono::seconds>().count());
    }

    return QVariant();
}

bool PlanModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (!plan) return false;
    if (data(index, role) == value) {
        return false;
    }
    auto item = plan->getItems().at(index.row());
    if (item.canConvert<Plan*>()) {
        // todo fixme
        return false;
    }
    if (item.canConvert<Interval>()) {
        auto interval = item.value<Interval>();
        switch (role) {
        case descriptionRole: {
            interval.setDescripton(value.toString().toStdString());
            qDebug() << "after setDescription" << item;
            break;
        }
        case durationRole: {
            interval.setDuration(std::chrono::seconds{value.toInt()});
            qDebug() << "after setDuration" << item;
            break;
        }
        default: return false;
        }

        plan->setItemAt(index.row(), interval);
        emit changedPlan();
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }

    return false;
}

Qt::ItemFlags PlanModel::flags(const QModelIndex& index) const {
    if (!index.isValid()) return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
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
    return names;
}

Plan* PlanModel::getPlan() const { return plan; }
void PlanModel::setPlan(Plan* newPlan) {
    beginResetModel();
    if (plan) {
        plan->disconnect(this);
    }
    plan = newPlan;
    if (plan) {
        connect(plan, &Plan::preItemAppended, this, [=]() {
            const int index = plan->getItems().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(plan, &Plan::postItemAppended, this, [=]() { endInsertRows(); });
        connect(plan, &Plan::preItemRemoved, this, [=](size_t index) { beginRemoveRows(QModelIndex(), index, index); });
        connect(plan, &Plan::postItemRemoved, this, [=]() { endRemoveRows(); });
    }
    endResetModel();
}
