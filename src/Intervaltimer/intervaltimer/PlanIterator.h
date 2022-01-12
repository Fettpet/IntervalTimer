#pragma once
#include "Interval.h"
#include <cstddef>
#include <iterator>

struct Plan;

struct PlanIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::size_t;
    using value_type = Interval;
    using pointer = value_type*;
    using reference = value_type&;

public:
    PlanIterator();
    PlanIterator(std::shared_ptr<Plan> const&);

    reference operator*();
    pointer operator->();
    Interval const* operator->() const;

    PlanIterator& operator++();

    PlanIterator operator++(int);

    bool operator==(PlanIterator const&) const;
    bool operator!=(PlanIterator const&) const;

private:
    void setToBegin();
    void setToEnd();
    void gotoNextInterval();
    [[nodiscard]] bool currentElementIsInterval() const;
    [[nodiscard]] bool currentElementIsPlan() const;
    [[nodiscard]] bool indexIsValid() const;
    Interval& getCurrentInterval();
    Interval const& getCurrentInterval() const;
    bool childIsAtEnd() const;
    std::shared_ptr<Plan> getCurrentPlan();

private:
    std::shared_ptr<Plan> plan{nullptr};
    std::shared_ptr<PlanIterator> childIterator{nullptr};
    int32_t currentRepetition{1}, currentIndex{-1};
};
