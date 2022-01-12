#include "Interval.h"

Interval::Interval() {}

Interval::Interval(std::chrono::milliseconds const& duration, QString const& description)
    : duration(duration)
    , description(description) {}

void Interval::setDuration(std::chrono::milliseconds const& dur) { duration = dur; }

void Interval::setDescripton(QString const& descr) { description = descr; }
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
