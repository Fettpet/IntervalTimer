#pragma once
#include "Interval.h"
#include <QString>
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

    QString getName() const;

signals:
    void preItemAppended();
    void postItemAppended();
    void preItemRemoved(size_t index);
    void postItemRemoved();

public slots:
    void setNumberRepetitions(uint32_t const&);
    void appendInterval();
    void appendPlan();
    void setName(QString const&);

protected:
    QString name;
    QVariantList items;
    uint32_t numberRepetitions{1};
};
