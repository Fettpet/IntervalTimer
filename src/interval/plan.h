#pragma once
#include "interval.h"
#include <QVariantList>

class Plan : public QObject {
    Q_OBJECT
public:
    Plan(QObject* parent = nullptr);

    auto operator==(Plan const&) const -> bool = default;

    void setItemAt(size_t const& index, Plan* plan);

    void setItemAt(size_t const& index, Interval const& interval);
    QVariant getItemAt(size_t const& index);
    QVariantList getItems();

    uint32_t getNumberRepetitions() const;

signals:
    void preItemAppended();
    void postItemAppended();

public slots:
    void setNumberRepetitions(uint32_t const&);
    void appendInterval();
    void appendPlan();

protected:
    QVariantList items;
    uint32_t numberRepetitions{1};
};
