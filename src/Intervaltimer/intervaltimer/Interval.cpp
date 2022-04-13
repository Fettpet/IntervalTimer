#include "Interval.h"
#include <utility>

Interval::Interval(std::chrono::milliseconds duration, QString description)
    : duration(duration)
    , description(std::move(description)) {}

void Interval::setDuration(std::chrono::milliseconds newDuration) { duration = newDuration; }

void Interval::setDescripton(QString newDescription) { description = std::move(newDescription); }
QString Interval::getDescription() const { return description; }

QDebug operator<<(QDebug debug, const Interval& interval) {
    debug.nospace() << interval.getDescription() << " (" << interval.getDuration<std::chrono::seconds>().count()
                    << "s )";
    return debug;
}

auto Interval::operator==(Interval const& lhs) const -> bool {
    return lhs.duration == duration && description == lhs.description;
}
auto Interval::operator!=(Interval const& lhs) const -> bool { return !(*this == lhs); }
