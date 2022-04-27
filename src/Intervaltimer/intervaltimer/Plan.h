#pragma once
#include "Interval.h"
#include "PlanIterator.h"

#include <QString>
#include <QVariantList>
#include <memory>

class Plan : public std::enable_shared_from_this<Plan> {
public:
    Plan() = default;
    Plan(Plan&&) = default;

    Plan& operator=(std::shared_ptr<Plan> const&);
    Plan& operator=(Plan&&) = default;

    auto operator==(Plan const&) const -> bool;
    auto operator!=(Plan const&) const -> bool;

    static std::shared_ptr<Plan> create();
    static std::shared_ptr<Plan> copy(std::shared_ptr<Plan> const&);

    void setItemAt(size_t const& index, std::shared_ptr<Plan> const& plan);

    void setItemAt(size_t const& index, Interval interval);
    [[nodiscard]] QVariant getItemAt(size_t const& index);
    [[nodiscard]] Interval getIntervalAt(size_t const& index);
    [[nodiscard]] std::shared_ptr<Plan> getPlanAt(size_t const& index) const;
    [[nodiscard]] bool isPlanAt(size_t const& index) const;
    [[nodiscard]] bool isIntervalAt(size_t const& index) const;

    [[nodiscard]] QVariant& getReferenceAt(size_t const& index);
    [[nodiscard]] QVariantList getItems() const;

    [[nodiscard]] uint32_t getNumberRepetitions() const;

    [[nodiscard]] QString getName() const;

    void setParentPlan(std::shared_ptr<Plan> parentPlan);
    [[nodiscard]] std::weak_ptr<Plan> getParentPlan() const;

    [[nodiscard]] uint32_t getRow() const;

    [[nodiscard]] uint32_t getNumberItems() const;

    void setNumberRepetitions(uint32_t const&);
    void appendInterval();
    void appendPlan();
    void setName(QString const&);
    void removeItem(int const&);

    [[nodiscard]] PlanIterator begin() const;
    [[nodiscard]] PlanIterator end() const;

    [[nodiscard]] std::chrono::milliseconds getDuration() const;

protected:
    std::weak_ptr<Plan> parentItem{};
    QString name{""};
    QVariantList items{};
    uint32_t numberRepetitions{1};
};

QDebug operator<<(QDebug debug, const Plan& plan);
Q_DECLARE_METATYPE(std::shared_ptr<Plan>);
