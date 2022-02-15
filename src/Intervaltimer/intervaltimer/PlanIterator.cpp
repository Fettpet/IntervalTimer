#include "PlanIterator.h"
#include "Plan.h"
#include <exception>

PlanIterator::PlanIterator() {}

PlanIterator::PlanIterator(const std::shared_ptr<Plan>& newPlan)
    : plan(newPlan) {
    setToBegin();
}

PlanIterator& PlanIterator::operator++() {
    gotoNextInterval();
    return *this;
}

PlanIterator PlanIterator::operator++(int) {
    PlanIterator tmp = *this;
    ++(*this);
    return tmp;
}

void PlanIterator::setToBegin() {
    childIterator = nullptr;
    currentIndex = -1;
    currentRepetition = 1;
    gotoNextInterval();
}

void PlanIterator::setToEnd() {
    childIterator = nullptr;
    plan.reset();
    currentIndex = -1;
    currentRepetition = 1;
}

void PlanIterator::gotoNextInterval() {
    while (true) {
        if (currentIndex != -1 && !childIsAtEnd() && currentElementIsPlan()) {
            ++(*childIterator);
            if (childIsAtEnd()) {
                continue;
            }
            return;
        }
        ++currentIndex;
        if (!indexIsValid()) {
            if (currentRepetition < plan->getNumberRepetitions()) {
                currentIndex = -1;
                ++currentRepetition;
                continue;
            }
            setToEnd();
            return;
        }
        if (currentElementIsInterval()) {
            return;
        }
        if (currentElementIsPlan()) {
            childIterator = std::make_shared<PlanIterator>(getCurrentPlan()->begin());
            if (*childIterator == getCurrentPlan()->end()) {
                setToEnd();
            }
            return;
        }
    }
}

PlanIterator::reference PlanIterator::operator*() {
    // if (!currentElementIsInterval()) {
    //     throw std::out_of_range{"Doesn't point to an interval"};
    // }
    return getCurrentInterval();
}

PlanIterator::pointer PlanIterator::operator->() {
    if (plan == nullptr) return nullptr;
    if (plan->getNumberItems() == 0) return nullptr;
    return &(getCurrentInterval());
}

const Interval* PlanIterator::operator->() const {
    if (plan == nullptr) return nullptr;
    if (plan->getNumberItems() == 0) return nullptr;
    return &(getCurrentInterval());
}

bool PlanIterator::currentElementIsPlan() const {
    if (!indexIsValid()) return false;
    return plan->getItemAt(currentIndex).canConvert<std::shared_ptr<Plan>>();
}

bool PlanIterator::currentElementIsInterval() const {
    if (!indexIsValid()) return false;
    return plan->getItemAt(currentIndex).canConvert<Interval>();
}

bool PlanIterator::indexIsValid() const { return currentIndex < plan->getNumberItems(); }

Interval& PlanIterator::getCurrentInterval() {
    QVariant& variant = plan->getReferenceAt(currentIndex);
    if (variant.userType() == qMetaTypeId<Interval>()) {
        return *reinterpret_cast<Interval*>(variant.data());
    }
    if (variant.userType() == qMetaTypeId<std::shared_ptr<Plan>>()) {
        return **childIterator;
    }
    throw std::domain_error{"Variant should contain an Interval"};
}

Interval const& PlanIterator::getCurrentInterval() const {
    QVariant& variant = plan->getReferenceAt(currentIndex);
    if (variant.userType() == qMetaTypeId<Interval>()) {
        return *reinterpret_cast<const Interval*>(variant.constData());
    }
    if (variant.userType() == qMetaTypeId<std::shared_ptr<Plan>>()) {
        return **childIterator;
    }
    throw std::domain_error{"Variant should contain an Interval"};
}

bool PlanIterator::childIsAtEnd() const { return childIterator == nullptr || *childIterator == plan->end(); }

std::shared_ptr<Plan> PlanIterator::getCurrentPlan() {
    QVariant& variant = plan->getReferenceAt(currentIndex);
    if (variant.userType() == qMetaTypeId<std::shared_ptr<Plan>>()) {
        return *reinterpret_cast<std::shared_ptr<Plan>*>(variant.data());
    }
    throw std::domain_error{"Variant should contain a Plan"};
}

bool PlanIterator::operator==(PlanIterator const& lhs) const {
    return currentRepetition == lhs.currentRepetition && currentIndex == lhs.currentIndex && plan == lhs.plan &&
        childIterator == lhs.childIterator;
}

bool PlanIterator::operator!=(PlanIterator const& lhs) const { return !(*this == lhs); }
