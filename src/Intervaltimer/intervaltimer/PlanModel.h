#pragma once

#include "Plan.h"
#include <QAbstractListModel>
#include <QQmlEngine>
#include <QtQml/qqmlregistration.h>
#include <memory>

class PlanModel : public QAbstractItemModel {
    Q_OBJECT
    QML_NAMED_ELEMENT(PlanModel)

    Q_PROPERTY(bool hasZeroDuration READ getHasZeroDuration NOTIFY changeHasZeroDuration);

    static constexpr int planColumn = 0;
    static constexpr int intervalColumn = 1;

public:
    explicit PlanModel(QObject* parent = nullptr);

    enum {
        durationRole = Qt::UserRole,
        descriptionRole,
        subPlanRole,
        nameRole,
        repetitionCountRole,
        isIntervalRole,
        isPlanRole
    };

    // Basic functionality:
    [[nodiscard]] int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    [[nodiscard]] int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    [[nodiscard]] QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;

    [[nodiscard]] QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

    [[nodiscard]] Qt::ItemFlags flags(const QModelIndex& index) const override;

    [[nodiscard]] QModelIndex parent(const QModelIndex& index) const override;

    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

    [[nodiscard]] std::weak_ptr<Plan> getPlan() const;
    void setPlan(std::shared_ptr<Plan> const&);

    [[nodiscard]] bool getHasZeroDuration() const;

    Q_INVOKABLE void appendInterval(const QModelIndex& parent = QModelIndex());
    Q_INVOKABLE void appendPlan(const QModelIndex& parent = QModelIndex());
    Q_INVOKABLE void removeItem(const QModelIndex& parent = QModelIndex());

public slots:
    void reset();

protected:
    void removePlan(const QModelIndex& parent);
    void removeInterval(const QModelIndex& parent);

    [[nodiscard]] static bool containsPlan(QModelIndex const&);
    [[nodiscard]] static bool containsInterval(QModelIndex const&);
    [[nodiscard]] static bool containsPlan(QVariant const&);
    [[nodiscard]] static bool containsInterval(QVariant const&);

    [[nodiscard]] std::shared_ptr<Plan> extractParentPlan(const QModelIndex& parent) const;
    [[nodiscard]] QVariant getDataForPlan(const QModelIndex& index, int role) const;
    [[nodiscard]] QVariant getDataForInterval(const QModelIndex& index, int role) const;

    [[nodiscard]] bool setDataForPlan(const QModelIndex& index, const QVariant& value, int role);
    [[nodiscard]] QVariant getDataForSubPlan(const QModelIndex& index, int role) const;
    [[nodiscard]] bool setDataForInterval(const QModelIndex& index, const QVariant& value, int role);

    [[nodiscard]] bool isDataSetable(const QModelIndex& index, const QVariant& value, int role) const;

signals:
    void changeHasZeroDuration();

private:
    std::shared_ptr<Plan> rootPlan;
};
