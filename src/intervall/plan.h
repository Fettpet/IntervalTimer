#pragma once
#include "intervall.h"
#include <vector>

class Plan;

class Plan {
public:
    Plan();
    Plan(Plan const&) = default;
    Plan(Plan&&) = default;

    Plan& operator=(Plan const&) = default;
    Plan& operator=(Plan&&) = default;

    auto operator==(Plan const&) const -> bool = default;

    void addPlan(Plan const&);
    Plan const& getPlan(size_t const& index) const;
    Plan& getPlanRef(size_t const& index);
    void removePlan(size_t const& index);
    size_t getNumberPlans() const;

    void addIntervall(Intervall const&);
    Intervall const& getIntervall(size_t const& index) const;
    Intervall& getIntervallRef(size_t const& index);
    void removeIntervall(size_t const& index);
    size_t getNumberIntervalls() const;

    uint32_t getNumberRepetitions() const;
    void setNumberRepetitions(uint32_t const&);

protected:
    std::vector<Intervall> intervalls;
    std::vector<Plan> plans;
    uint32_t numberRepetitions{1};
};
