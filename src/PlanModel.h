#pragma once

#include <QAbstractListModel>
#include <interval/plan.h>

class PlanModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(Plan* plan READ getPlan WRITE setPlan);

public:
    explicit PlanModel(QObject* parent = nullptr);

    enum { durationRole = Qt::UserRole, descriptionRole };
    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // bool setHeaderData(
    //     int section, Qt::Orientation orientation, const QVariant& value, int role = Qt::EditRole) override;

    // Basic functionality:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // // Add data:
    // bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

    // // Remove data:
    // bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

    virtual QHash<int, QByteArray> roleNames() const override;

    Plan* getPlan() const;
    void setPlan(Plan*);

private:
    Plan* plan{nullptr};
};
