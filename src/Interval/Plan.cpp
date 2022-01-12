#include "Plan.h"
#include "PlanIterator.h"
#include <exception>

void Plan::setItemAt(size_t const& index, std::shared_ptr<Plan> plan) {
    if (index >= items.size()) {
        throw std::range_error{"index out of range"};
    }
    plan->setParentPlan(this->shared_from_this());
    items[index] = QVariant::fromValue<std::shared_ptr<Plan>>(plan);
}

void Plan::setItemAt(size_t const& index, Interval const& interval) {
    if (index >= items.size()) {
        throw std::range_error{"index out of range"};
    }
    items[index] = QVariant::fromValue(interval);
}

auto Plan::operator==(Plan const& lhs) const -> bool {
    if (name != lhs.name || numberRepetitions != lhs.numberRepetitions || items.size() != lhs.items.size())
        return false;
    for (auto i = 0; i < items.size(); ++i) {
        auto& item = items.at(i);
        auto& lhsItem = lhs.items.at(i);
        if (item.typeId() != lhsItem.typeId()) {
            return false;
        }
        if (item.canConvert<Interval>()) {
            if (item.value<Interval>() != lhsItem.value<Interval>()) {
                return false;
            }
        }
        else if (item.canConvert<Plan*>()) {
            if (*(item.value<Plan*>()) != *(lhsItem.value<Plan*>())) {
                return false;
            }
        }
    }
    return true;
}
auto Plan::operator!=(Plan const& lhs) const -> bool { return !(*this == lhs); }

void Plan::appendInterval() { items.push_back(QVariant::fromValue(Interval{})); }
void Plan::appendPlan() {
    auto newPlan = std::make_shared<Plan>();
    newPlan->setParentPlan(this->shared_from_this());
    items.push_back(QVariant::fromValue<std::shared_ptr<Plan>>(newPlan));
}

void Plan::setName(const QString& newName) { name = newName; }

void Plan::removeItem(const int& index) { items.remove(index); }

PlanIterator Plan::begin() const { return PlanIterator{const_cast<Plan*>(this)->shared_from_this()}; }

PlanIterator Plan::end() const { return PlanIterator{}; }

std::chrono::milliseconds Plan::getDuration() const {
    auto result = std::chrono::milliseconds{0};
    for (auto interval : *this) {
        result += interval.getDuration<std::chrono::milliseconds>();
    }
    return result;
}

QVariant Plan::getItemAt(const size_t& index) {
    if (index >= items.size()) {
        return QVariant();
    }
    return items.at(index);
}

QVariant& Plan::getReferenceAt(const size_t& index) {
    if (index >= items.size()) {
        throw std::out_of_range{"not in range"};
    }
    return items[index];
}

QVariantList Plan::getItems() const { return items; }

uint32_t Plan::getNumberRepetitions() const { return numberRepetitions; }

QString Plan::getName() const { return name; }

std::weak_ptr<Plan> Plan::getParentPlan() const { return parentItem; }
void Plan::setParentPlan(std::shared_ptr<Plan> parent) { parentItem = parent; }

uint32_t Plan::getRow() const {
    if (parentItem.expired()) {
        return 0;
    }
    auto variant = QVariant::fromValue(const_cast<Plan*>(this)->shared_from_this());
    return parentItem.lock()->items.indexOf(variant);
}

uint32_t Plan::getNumberItems() const { return items.size(); }

void Plan::setNumberRepetitions(uint32_t const& repetitions) { numberRepetitions = repetitions; }

QDebug operator<<(QDebug debug, const Plan& plan) {
    debug.nospace() << plan.getName() << " " << plan.getNumberRepetitions();
    for (auto item : plan.getItems()) {
        if (item.canConvert<Interval>()) {
            debug.nospace() << item.value<Interval>();
        }
        if (item.canConvert<Plan*>()) {
            debug.nospace() << *(item.value<Plan*>());
        }
    }

    return debug;
}
