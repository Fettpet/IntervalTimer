#include "plan.h"

Plan::Plan() {}

void Plan::addPlan(Plan const& plan) { plans.push_back(plan); }
Plan const& Plan::getPlan(size_t const& index) const { return plans.at(index); }
Plan& Plan::getPlanRef(size_t const& index) { return plans.at(index); }
void Plan::removePlan(size_t const& index) { plans.erase(plans.begin() + index); }
size_t Plan::getNumberPlans() const { return plans.size(); }

void Plan::addIntervall(Intervall const& intervall) { intervalls.push_back(intervall); }
Intervall const& Plan::getIntervall(size_t const& index) const { return intervalls.at(index); }
Intervall& Plan::getIntervallRef(size_t const& index) { return intervalls.at(index); }
void Plan::removeIntervall(size_t const& index) { intervalls.erase(intervalls.begin() + index); }
size_t Plan::getNumberIntervalls() const { return intervalls.size(); }

uint32_t Plan::getNumberRepetitions() const { return numberRepetitions; }
void Plan::setNumberRepetitions(uint32_t const& repetitions) { numberRepetitions = repetitions; }
