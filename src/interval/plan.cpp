#include "plan.h"

Plan::Plan() {}

void Plan::addPlan(Plan const& plan) { plans.push_back(plan); }
Plan const& Plan::getPlan(size_t const& index) const { return plans.at(index); }
Plan& Plan::getPlanRef(size_t const& index) { return plans.at(index); }
void Plan::removePlan(size_t const& index) { plans.erase(plans.begin() + index); }
size_t Plan::getNumberPlans() const { return plans.size(); }

void Plan::addInterval(Interval const& interval) { intervals.push_back(interval); }
Interval const& Plan::getInterval(size_t const& index) const { return intervals.at(index); }
Interval& Plan::getIntervalRef(size_t const& index) { return intervals.at(index); }
void Plan::removeInterval(size_t const& index) { intervals.erase(intervals.begin() + index); }
size_t Plan::getNumberIntervals() const { return intervals.size(); }

uint32_t Plan::getNumberRepetitions() const { return numberRepetitions; }
void Plan::setNumberRepetitions(uint32_t const& repetitions) { numberRepetitions = repetitions; }
