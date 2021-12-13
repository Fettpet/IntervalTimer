#include "Plan.h"
#include <exception>

Plan::Plan(QObject* parent)
    : QObject(parent) {}

void Plan::setItemAt(size_t const& index, Plan* plan) {
    if (index >= items.size()) {
        throw std::range_error{"index out of range"};
    }
    items[index] = QVariant::fromValue<Plan*>(plan);
}

void Plan::setItemAt(size_t const& index, Interval const& interval) {
    if (index >= items.size()) {
        throw std::range_error{"index out of range"};
    }
    items[index] = QVariant::fromValue(interval);
}

void Plan::appendInterval() {
    emit preItemAppended();
    items.push_back(QVariant::fromValue(Interval{}));
    emit postItemAppended();
}
void Plan::appendPlan() {
    emit preItemAppended();
    items.push_back(QVariant::fromValue<Plan*>(new Plan{}));
    emit postItemAppended();
}

void Plan::setName(const QString& newName) { name = newName; }

QVariant Plan::getItemAt(const size_t& index) { return items.at(index); }

QVariantList Plan::getItems() const { return items; }

uint32_t Plan::getNumberRepetitions() const { return numberRepetitions; }

QString Plan::getName() const { return name; }
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
