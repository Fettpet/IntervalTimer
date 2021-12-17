#pragma once

#include "Plan.h"
#include <QAbstractListModel>
#include <QtQml/qqmlregistration.h>
#include <memory>

class PlanModel : public QAbstractItemModel {
    Q_OBJECT
    QML_ELEMENT
    //   Q_PROPERTY(Plan* rootPlan READ getPlan WRITE setPlan);
    constexpr int planColumn = 0;
    constexpr int intervalColumn = 1;

public:
    explicit PlanModel(QObject* parent = nullptr);
    //~PlanModel();
    enum { durationRole = Qt::UserRole, descriptionRole, subPlanRole, nameRole, isIntervalRole, isPlanRole };
    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // bool setHeaderData(
    //     int section, Qt::Orientation orientation, const QVariant& value, int role = Qt::EditRole) override;

    // Basic functionality:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    QModelIndex parent(const QModelIndex& index) const override;
    // // Add data:
    // bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

    // // Remove data:
    // bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

    virtual QHash<int, QByteArray> roleNames() const override;

    std::weak_ptr<Plan> getPlan() const;
    void setPlan(std::shared_ptr<Plan>);

protected:
    static bool containsPlan(QModelIndex const&);
    static bool containsInterval(QModelIndex const&);
    static bool containsPlan(QVariant const&);
    static bool containsInterval(QVariant const&);

private:
    std::shared_ptr<Plan> rootPlan;
};
