#include "Interval.h"

Interval::Interval() {}

Interval::Interval(std::chrono::milliseconds const& duration, std::string const& description)
    : duration(duration)
    , description(description) {}

void Interval::setDuration(std::chrono::milliseconds const& dur) { duration = dur; }

void Interval::setDescripton(std::string const& descr) { description = descr; }
std::string Interval::getDescripton() const { return description; }

QDebug operator<<(QDebug debug, const Interval& interval) {
    debug.nospace() << "Duration: " << interval.getDuration<std::chrono::seconds>().count() << "s ("
                    << QString::fromStdString(interval.getDescripton());
    return debug;
}
