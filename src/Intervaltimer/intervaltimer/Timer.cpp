#include "Timer.h"

Timer::Timer(QObject* parent)
    : TimerBase{parent} {
    thread->start(QThread::LowPriority);

    QObject::connect(timer.get(), &QTimer::timeout, this, [&]() { emit timeout(); });
}

Timer::~Timer() {
    thread->exit();
    timer.reset();
    // needed to avoid an exception
    while (!thread->isFinished()) {
    }
}

void Timer::start(const std::chrono::milliseconds& duration) { timer->start(duration); }

std::chrono::milliseconds Timer::getElapsedTime() const {
    return timer->intervalAsDuration() - timer->remainingTimeAsDuration();
}

std::chrono::milliseconds Timer::getDuration() const { return timer->intervalAsDuration(); }

void Timer::stop() { timer->stop(); }
