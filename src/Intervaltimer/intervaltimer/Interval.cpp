#include "Interval.h"
#include "Plan.h"
#include <utility>

Interval::Interval(std::chrono::milliseconds duration, QString description)
    : duration(duration)
    , description(std::move(description)) {}

Interval::Interval(std::chrono::milliseconds duration, QString description, std::weak_ptr<Plan> parent)
    : duration(duration)
    , description(std::move(description))
    , parent(std::move(parent)) {}

void Interval::setDuration(std::chrono::milliseconds newDuration) { duration = newDuration; }

void Interval::setDescripton(QString newDescription) { description = std::move(newDescription); }
QString Interval::getDescription() const { return description; }

void Interval::setParent(std::weak_ptr<Plan> newParent) { parent = std::move(newParent); }
std::weak_ptr<Plan> Interval::getParent() const { return parent; }

QDebug operator<<(QDebug debug, const Interval& interval) {
    debug.nospace() << interval.getDescription() << " (" << interval.getDuration<std::chrono::seconds>().count()
                    << "s )";
    return debug;
}

auto Interval::operator==(Interval const& lhs) const -> bool {
    return lhs.duration == duration && description == lhs.description;
}
auto Interval::operator!=(Interval const& lhs) const -> bool { return !(*this == lhs); }
