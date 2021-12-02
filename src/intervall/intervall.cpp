#include "intervall.h"

Intervall::Intervall() {}

Intervall::Intervall(std::chrono::milliseconds const& duration, std::string const& description)
    : duration(duration)
    , description(description) {}

void Intervall::setDuration(std::chrono::milliseconds const& dur) { duration = dur; }

void Intervall::setDescripton(std::string const& descr) { description = descr; }
std::string Intervall::getDescripton() const { return description; }
