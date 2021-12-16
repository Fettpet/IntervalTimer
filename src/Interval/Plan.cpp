#include "Plan.h"
#include <exception>

Plan::Plan(Plan* parent)
    : QObject(parent)
    , parentItem(parent) {}

Plan::Plan(QObject* parent)
    : QObject(parent) {}

void Plan::setItemAt(size_t const& index, Plan* plan) {
    if (index >= items.size()) {
        throw std::range_error{"index out of range"};
    }
    plan->setParent(this);
    items[index] = QVariant::fromValue<Plan*>(plan);
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

void Plan::appendInterval() {
    emit preItemAppended();
    items.push_back(QVariant::fromValue(Interval{}));
    emit postItemAppended();
}
void Plan::appendPlan() {
    emit preItemAppended();
    items.push_back(QVariant::fromValue<Plan*>(new Plan{this}));
    emit postItemAppended();
}

void Plan::setName(const QString& newName) { name = newName; }

QVariant Plan::getItemAt(const size_t& index) {
    if (index >= items.size()) {
        return QVariant();
    }
    return items.at(index);
}

QVariantList Plan::getItems() const { return items; }

uint32_t Plan::getNumberRepetitions() const { return numberRepetitions; }

QString Plan::getName() const { return name; }

Plan* Plan::getParent() const { return parentItem; }
void Plan::setParent(Plan* parent) { parentItem = parent; }

uint32_t Plan::getRow() const {
    if (!parentItem) {
        return 0;
    }
    return parentItem->items.indexOf(QVariant::fromValue<Plan*>(const_cast<Plan*>(this)));
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
