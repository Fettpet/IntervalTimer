#pragma once
#include "Interval.h"
#include <QObject>
#include <QString>
#include <QVariantList>

class Plan : public QObject {
    Q_OBJECT
public:
    explicit Plan(Plan* parent);
    explicit Plan(QObject* parent = nullptr);

    auto operator==(Plan const&) const -> bool;

    void setItemAt(size_t const& index, Plan* plan);

    void setItemAt(size_t const& index, Interval const& interval);
    QVariant getItemAt(size_t const& index);
    QVariantList getItems() const;

    Q_INVOKABLE uint32_t getNumberRepetitions() const;

    Q_INVOKABLE QString getName() const;

    Plan* getParent() const;
    void setParent(Plan*);

    uint32_t getRow() const;

    uint32_t getNumberItems() const;
signals:
    void preItemAppended();
    void postItemAppended();
    void preItemRemoved(size_t index);
    void postItemRemoved();

public slots:
    Q_INVOKABLE void setNumberRepetitions(uint32_t const&);
    void appendInterval();
    void appendPlan();
    Q_INVOKABLE void setName(QString const&);

protected:
    Plan* parentItem{nullptr};
    QString name;
    QVariantList items;
    uint32_t numberRepetitions{1};
};

QDebug operator<<(QDebug debug, const Plan& plan);
