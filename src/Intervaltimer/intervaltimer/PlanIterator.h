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
    PlanIterator(PlanIterator const&) = default;
    PlanIterator(PlanIterator &&) = default;
    PlanIterator(std::shared_ptr<Plan> const&);

    PlanIterator& operator=(PlanIterator const&) = default;
    PlanIterator& operator=(PlanIterator&&) = default;

    [[nodiscard]] reference operator*();
    [[nodiscard]] pointer operator->();
    [[nodiscard]] Interval const* operator->() const;

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
    [[nodiscard]] Interval& getCurrentInterval();
    [[nodiscard]] Interval const& getCurrentInterval() const;
    [[nodiscard]] bool childIsAtEnd() const;
    [[nodiscard]] std::shared_ptr<Plan> getCurrentPlan();

private:
    std::shared_ptr<Plan> plan{nullptr};
    std::shared_ptr<PlanIterator> childIterator{nullptr};
    int32_t currentRepetition{1}, currentIndex{-1};
};
