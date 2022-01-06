#include "PlanRunner.h"

PlanRunner::PlanRunner(QObject* object)
    : QObject(object) {

    timerThread->start(QThread::LowPriority);
}

PlanRunner::~PlanRunner() {
    timerThread->exit();
    // needed to avoid an exception
    while (!timerThread->isFinished()) {
    }
}

QString PlanRunner::getDescriptionOfInterval() const {
    Q_ASSERT(iterator != PlanIterator{});
    return iterator->getDescription();
}

int PlanRunner::getIntervalDurationCompleteTime() const {
    Q_ASSERT(iterator != PlanIterator{});
    return iterator->getDuration<std::chrono::milliseconds>().count();
}

int PlanRunner::getIntervalDurationRunningTime() const {
    return getIntervalDurationCompleteTime() - intervalTimer->remainingTimeAsDuration().count();
}

std::weak_ptr<Plan> PlanRunner::getPlan() const { return plan; }

void PlanRunner::setPlan(std::shared_ptr<Plan> newPlan) { plan = newPlan; }

int PlanRunner::getRefreshingTimeInterval() const { return refreshingTimeForRunningInterval.count(); }

void PlanRunner::setRefreshingTimeInterval(const int& newTime) {
    refreshingTimeForRunningInterval = std::chrono::milliseconds{newTime};
}

void PlanRunner::start() {
    stop();

    connect(intervalTimer.get(), SIGNAL(timeout()), this, SLOT(changedInterval()));
    connect(intervalRunningTimer.get(), SIGNAL(timeout()), this, SLOT(changedIntervalRunningTime()));

    isRunning = true;
    iterator = plan->begin();
    startInterval();
}

void PlanRunner::stop() {
    disconnect();
    intervalTimer->stop();
    intervalRunningTimer->stop();
    isRunning = false;
}

void PlanRunner::startInterval() {
    intervalTimer->start(iterator->getDuration<std::chrono::milliseconds>());
    intervalRunningTimer->start(refreshingTimeForRunningInterval);
}

void PlanRunner::changedInterval() {
    ++iterator;
    if (iterator == plan->end()) {
        stop();
        emit finished();
        return;
    }
    startInterval();
    emit changedDescriptionOfInterval();
    emit changedIntervalDurationCompleteTime();
    emit changedIntervalDurationRunningTime();
}

void PlanRunner::changedIntervalRunningTime() { emit changedIntervalDurationRunningTime(); }

void PlanRunner::setIntervalTimer(std::shared_ptr<QTimer> newTimer) { intervalTimer = std::move(newTimer); }
