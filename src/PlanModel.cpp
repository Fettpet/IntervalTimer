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
    if (parent.isValid()) return 0;

    // FIXME: Implement me!
    return 10;
}

QVariant PlanModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) return QVariant();

    // FIXME: Implement me!
    switch (role) {
    case descriptionRole: return QVariant(QString("Hello World"));
    case durationRole: return QVariant(index.row() + 1);
    }

    return QVariant();
}

bool PlanModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags PlanModel::flags(const QModelIndex& index) const {
    if (!index.isValid()) return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
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
