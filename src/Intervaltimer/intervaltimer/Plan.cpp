#include "Plan.h"
#include "PlanIterator.h"
#include <exception>

void Plan::setItemAt(size_t const& index, std::shared_ptr<Plan> const& plan) {
    if (index >= items.size()) {
        throw std::range_error{"index out of range"};
    }
    plan->setParentPlan(this->shared_from_this());
    items[index] = QVariant::fromValue<std::shared_ptr<Plan>>(plan);
}

void Plan::setItemAt(size_t const& index, Interval interval) {
    if (index >= items.size()) {
        throw std::range_error{"index out of range"};
    }
    interval.setParent(this->shared_from_this());
    items[index] = QVariant::fromValue(interval);
}

Plan::Plan(const Plan& lhs) { *this = lhs; }

Plan& Plan::operator=(const std::shared_ptr<Plan>& lhs) {
    auto copylhs = copy(lhs);
    name = copylhs->name;
    numberRepetitions = copylhs->numberRepetitions;
    parentItem = copylhs->parentItem;
    items = copylhs->items;
    return *this;
}

auto Plan::operator==(Plan const& lhs) const -> bool {
    if (name != lhs.name || numberRepetitions != lhs.numberRepetitions || items.size() != lhs.items.size())
        return false;
    for (auto i = 0; i < items.size(); ++i) {
        auto const& item = items.at(i);
        auto const& lhsItem = lhs.items.at(i);
        if (item.typeId() != lhsItem.typeId()) {
            return false;
        }
        if (item.canConvert<Interval>()) {
            if (item.value<Interval>() != lhsItem.value<Interval>()) {
                return false;
            }
        }
        else if (item.canConvert<std::shared_ptr<Plan>>()) {
            if (*(item.value<std::shared_ptr<Plan>>()) != *(lhsItem.value<std::shared_ptr<Plan>>())) {
                return false;
            }
        }
        else {
            throw std::invalid_argument("is neighter a plan nor an interval");
        }
    }
    return true;
}
auto Plan::operator!=(Plan const& lhs) const -> bool { return !(*this == lhs); }

std::shared_ptr<Plan> Plan::create() { return std::make_shared<Plan>(Plan{}); }

std::shared_ptr<Plan> Plan::copy(std::shared_ptr<Plan> const& lhs) {
    auto result = create();
    result->name = lhs->name;
    result->numberRepetitions = lhs->numberRepetitions;

    for (auto i = 0; i < lhs->items.size(); ++i) {
        if (lhs->isIntervalAt(i)) {
            Interval copy = lhs->items[i].value<Interval>();
            copy.setParent(result);
            result->items.append(QVariant::fromValue(copy));
            continue;
        }
        if (lhs->isPlanAt(i)) {
            auto copyPlan = copy(lhs->getPlanAt(i));
            copyPlan->setParentPlan(result);
            auto variant = QVariant::fromValue(copyPlan);
            result->items.append(variant);
            continue;
        }
        throw std::invalid_argument("Item is neighter a Plan nor an Interval");
    }
    return result;
}

void Plan::appendInterval() {
    auto interval = Interval{};
    interval.setParent(this->shared_from_this());
    items.push_back(QVariant::fromValue(interval));
}
void Plan::appendPlan() {
    auto newPlan = create();
    newPlan->setParentPlan(this->shared_from_this());
    items.push_back(QVariant::fromValue<std::shared_ptr<Plan>>(newPlan));
}

void Plan::setName(const QString& newName) { name = newName; }

void Plan::removeItem(const int& index) { items.remove(index); }

PlanIterator Plan::begin() const { return PlanIterator{const_cast<Plan*>(this)->shared_from_this()}; }

PlanIterator Plan::end() const { return PlanIterator{}; }

std::chrono::milliseconds Plan::getDuration() const {
    auto result = std::chrono::milliseconds{0};
    for (auto const& interval : *this) {
        result += interval.getDuration<std::chrono::milliseconds>();
    }
    return result;
}

QVariant Plan::getItemAt(const size_t& index) {
    if (index >= items.size()) {
        return {};
    }
    return items.at(index);
}

Interval Plan::getIntervalAt(const size_t& index) {
    if (!isIntervalAt(index)) {
        throw std::invalid_argument("Item isn't an Interval");
    }
    return items.at(index).value<Interval>();
}

std::shared_ptr<Plan> Plan::getPlanAt(const size_t& index) const {

    if (!isPlanAt(index)) {
        throw std::invalid_argument("Item isn't an Plan");
    }
    QVariant const& variant = items[index];
    return *reinterpret_cast<const std::shared_ptr<Plan>*>(variant.constData());
}

bool Plan::isPlanAt(const size_t& index) const {
    QVariant const& variant = items[index];
    return variant.userType() == qMetaTypeId<std::shared_ptr<Plan>>();
}

bool Plan::isIntervalAt(const size_t& index) const { return items.at(index).canConvert<Interval>(); }

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
void Plan::setParentPlan(std::shared_ptr<Plan> parent) { parentItem = std::move(parent); }

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
    for (auto const& item : plan.getItems()) {
        if (item.canConvert<Interval>()) {
            debug.nospace() << item.value<Interval>();
        }
        if (item.canConvert<std::shared_ptr<Plan>>()) {
            debug.nospace() << *(item.value<std::shared_ptr<Plan>>());
        }
    }

    return debug;
}
