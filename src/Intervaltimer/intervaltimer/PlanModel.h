#pragma once

#include "Plan.h"
#include <QAbstractListModel>
#include <QQmlEngine>
#include <QtQml/qqmlregistration.h>
#include <memory>

class PlanModel : public QAbstractItemModel {
    Q_OBJECT
    QML_SINGLETON
    QML_NAMED_ELEMENT(PlanModel)

    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY changedName);
    Q_PROPERTY(int repetitions READ getRepetitionCount WRITE setRepetitionCount NOTIFY changedRepetitions);
    static constexpr int planColumn = 0;
    static constexpr int intervalColumn = 1;

    explicit PlanModel(QObject* parent = nullptr);
    static PlanModel* instance;

public:
    static PlanModel* create(QQmlEngine*, QJSEngine* engine);

    enum { durationRole = Qt::UserRole, descriptionRole, subPlanRole, nameRole, isIntervalRole, isPlanRole };

    // Basic functionality:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    QModelIndex parent(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    std::weak_ptr<Plan> getPlan() const;
    void setPlan(std::shared_ptr<Plan>);

    QString getName() const;
    void setName(QString const&);

    void setRepetitionCount(int const&);
    int getRepetitionCount() const;

    Q_INVOKABLE void appendInterval();
    Q_INVOKABLE void appendPlan();
    Q_INVOKABLE void removeItem(int const&);

    Q_INVOKABLE void savePlanToFile(QString const& filename);
    Q_INVOKABLE void loadPlanFromFile(QString const& filename);

public slots:
    void reset();

protected:
    static bool containsPlan(QModelIndex const&);
    static bool containsInterval(QModelIndex const&);
    static bool containsPlan(QVariant const&);
    static bool containsInterval(QVariant const&);

    bool isDataSetable(const QModelIndex& index, const QVariant& value, int role) const;

signals:
    void changedName();
    void changedRepetitions();

private:
    std::shared_ptr<Plan> rootPlan;
};
