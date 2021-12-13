#pragma once
#include "Interval.h"
#include <QString>
#include <QVariantList>

class Plan : public QObject {
    Q_OBJECT
public:
    Plan(QObject* parent = nullptr);

    auto operator==(Plan const&) const -> bool;

    void setItemAt(size_t const& index, Plan* plan);

    void setItemAt(size_t const& index, Interval const& interval);
    QVariant getItemAt(size_t const& index);
    QVariantList getItems() const;

    Q_INVOKABLE uint32_t getNumberRepetitions() const;

    Q_INVOKABLE QString getName() const;

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
    QString name;
    QVariantList items;
    uint32_t numberRepetitions{1};
};

QDebug operator<<(QDebug debug, const Plan& plan);
