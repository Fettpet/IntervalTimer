#pragma once

#include "Plan.h"
#include <QAbstractListModel>
#include <QQmlEngine>
#include <QtQml/qqmlregistration.h>
#include <memory>

class PlanModel : public QAbstractItemModel {
    Q_OBJECT
    QML_NAMED_ELEMENT(PlanModel)

    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY changedName);
    Q_PROPERTY(int repetitions READ getRepetitionCount WRITE setRepetitionCount NOTIFY changedRepetitions);
    Q_PROPERTY(bool isRoot READ getIsRoot CONSTANT);
    Q_PROPERTY(bool hasZeroDuration READ getHasZeroDuration NOTIFY changeHasZeroDuration);

    static constexpr int planColumn = 0;
    static constexpr int intervalColumn = 1;

public:
    explicit PlanModel(QObject* parent = nullptr);

    enum { durationRole = Qt::UserRole, descriptionRole, subPlanRole, nameRole, isIntervalRole, isPlanRole };

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

    [[nodiscard]] QString getName() const;
    void setName(QString const&);

    void setRepetitionCount(int const&);
    [[nodiscard]] int getRepetitionCount() const;

    [[nodiscard]] bool getHasZeroDuration() const;

    [[nodiscard]] bool getIsRoot() const;

    Q_INVOKABLE void appendInterval();
    Q_INVOKABLE void appendPlan();
    Q_INVOKABLE void removeItem(int const&);

public slots:
    void reset();

protected:
    [[nodiscard]] static bool containsPlan(QModelIndex const&);
    [[nodiscard]] static bool containsInterval(QModelIndex const&);
    [[nodiscard]] static bool containsPlan(QVariant const&);
    [[nodiscard]] static bool containsInterval(QVariant const&);

    [[nodiscard]] std::shared_ptr<Plan> extractParentPlan(const QModelIndex& parent) const;
    [[nodiscard]] QVariant getDataForPlan(const QModelIndex& index, int role) const;
    [[nodiscard]] QVariant getDataForInterval(const QModelIndex& index, int role) const;

    bool setDataForPlan(const QModelIndex& index, const QVariant& value, int role);
    [[nodiscard]] QVariant getDataForSubPlan(const QModelIndex& index, int role) const;
    bool setDataForInterval(const QModelIndex& index, const QVariant& value, int role);

    [[nodiscard]] bool isDataSetable(const QModelIndex& index, const QVariant& value, int role) const;

signals:
    void changedName();
    void changedRepetitions();
    void changeHasZeroDuration();

private:
    std::shared_ptr<Plan> rootPlan;
};
