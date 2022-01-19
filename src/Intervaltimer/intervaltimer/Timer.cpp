#include "Timer.h"

Timer::Timer(QObject* parent)
    : TimerBase{parent} {
    thread->start(QThread::LowPriority);

    QObject::connect(timer.get(), &QTimer::timeout, [&]() { emit timeout(); });
}

Timer::~Timer() {
    thread->exit();
    timer.reset();
    // needed to avoid an exception
    while (!thread->isFinished()) {
    }
}

void Timer::start(const std::chrono::milliseconds& duration) { timer->start(duration); }
