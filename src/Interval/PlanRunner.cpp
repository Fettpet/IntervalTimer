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

int PlanRunner::getPlanDurationCompleteTime() const { return plan->getDuration().count(); }

int PlanRunner::getPlanDurationRunningTime() const {
    return getPlanDurationCompleteTime() - planTimer->remainingTimeAsDuration().count();
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

int PlanRunner::getRefreshingTimePlan() const { return refreshingTimeForRunningPlan.count(); }

void PlanRunner::setRefreshingTimePlan(const int& newTime) {
    refreshingTimeForRunningPlan = std::chrono::milliseconds{newTime};
}

void PlanRunner::start() {
    stop();

    connect(intervalTimer.get(), SIGNAL(timeout()), this, SLOT(changedInterval()));
    connect(intervalRefreshingTimer.get(), SIGNAL(timeout()), this, SLOT(changedIntervalRunningTime()));
    connect(planRefreshingTimer.get(), SIGNAL(timeout()), this, SLOT(changedPlanRunningTime()));
    planRefreshingTimer->start(refreshingTimeForRunningPlan);
    planTimer->start(getPlanDurationCompleteTime());
    isRunning = true;
    iterator = plan->begin();
    startInterval();
}

void PlanRunner::stop() {
    disconnect();
    planRefreshingTimer->stop();
    intervalTimer->stop();
    intervalRefreshingTimer->stop();
    isRunning = false;
}

void PlanRunner::startInterval() {
    intervalTimer->start(iterator->getDuration<std::chrono::milliseconds>());
    intervalRefreshingTimer->start(refreshingTimeForRunningInterval);
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

void PlanRunner::changedPlanRunningTime() { emit changedPlanDurationRunningTime(); }

void PlanRunner::setIntervalTimer(std::shared_ptr<QTimer> newTimer) { intervalTimer = std::move(newTimer); }
