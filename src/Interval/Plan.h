#pragma once
#include "Interval.h"
#include <QString>
#include <QVariantList>
#include <memory>

class Plan : public std::enable_shared_from_this<Plan> {
public:
    auto operator==(Plan const&) const -> bool;

    void setItemAt(size_t const& index, std::shared_ptr<Plan> plan);

    void setItemAt(size_t const& index, Interval const& interval);
    QVariant getItemAt(size_t const& index);
    QVariantList getItems() const;

    uint32_t getNumberRepetitions() const;

    QString getName() const;

    void setParentPlan(std::shared_ptr<Plan>);
    std::weak_ptr<Plan> getParentPlan() const;

    uint32_t getRow() const;

    uint32_t getNumberItems() const;

    void setNumberRepetitions(uint32_t const&);
    void appendInterval();
    void appendPlan();
    void setName(QString const&);
    void removeItem(int const&);

protected:
    std::weak_ptr<Plan> parentItem;
    QString name;
    QVariantList items;
    uint32_t numberRepetitions{1};
};

QDebug operator<<(QDebug debug, const Plan& plan);
Q_DECLARE_METATYPE(std::shared_ptr<Plan>);
