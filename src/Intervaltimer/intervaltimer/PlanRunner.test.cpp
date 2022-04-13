#include <Interval.h>
#include <Plan.h>
#include <PlanIterator.h>
#include <PlanRunner.h>
#include <TimerBase.h>
#include <gtest/gtest.h>

#include <QCoreApplication>
#include <QSignalSpy>
#include <QThread>
#include <QTimer>
#include <QtTest/QtTest>
#include <memory>

struct TestTimer : public TimerBase {
    TestTimer()
        : TimerBase(nullptr) {}

public:
    void start(const std::chrono::milliseconds& dur) override { duration = dur; }
    void emitTimeout() { emit timeout(); }

    [[nodiscard]] std::chrono::milliseconds getElapsedTime() const override { return elapsedTime; }
    void setElapsedTime(std::chrono::milliseconds time) { elapsedTime = time; }
    [[nodiscard]] std::chrono::milliseconds getDuration() const override { return duration; }
    void stop() override { elapsedTime = std::chrono::milliseconds{0}; }

    std::chrono::milliseconds elapsedTime, duration;
};

struct PlanRunnerTesting : ::testing::Test, public QObject {
protected:
    void SetUp() override {
        nestedPlan->setName("Inner");
        nestedPlan->setNumberRepetitions(12);
        nestedPlan->appendInterval();
        nestedPlan->appendInterval();
        nestedPlan->setItemAt(0, Interval{std::chrono::seconds{2}, "second"});
        nestedPlan->setItemAt(1, Interval{std::chrono::seconds{3}, "third"});

        plan->setName("Outer");
        plan->setNumberRepetitions(10);
        plan->appendInterval();
        plan->appendPlan();
        plan->appendInterval();
        plan->setItemAt(0, Interval{std::chrono::milliseconds{100}, "first"});
        plan->setItemAt(1, nestedPlan);
        plan->setItemAt(2, Interval{std::chrono::seconds{4}, "fourth"});

        planForModel->appendPlan();
        planForModel->setName("Root");
        planForModel->setItemAt(0, plan);

        runner->setPlan(planForModel);

        runner->setIntervalRefeshingTimer(intervalRefreshingTimer);
        runner->setIntervalTimer(intervalTimer);
        runner->setPlanTimer(planTimer);
        runner->setPlanRefeshingTimer(planRefreshingTimer);
        runner->start();
    }

public:
    std::shared_ptr<Plan> nestedPlan{new Plan{}};
    std::shared_ptr<Plan> plan{new Plan{}};
    std::shared_ptr<Plan> planForModel{new Plan{}};
    std::shared_ptr<TestTimer> intervalTimer{new TestTimer{}}, intervalRefreshingTimer{new TestTimer{}};
    std::shared_ptr<TestTimer> planTimer{new TestTimer{}}, planRefreshingTimer{new TestTimer{}};
    PlanRunner* runner{PlanRunner::create(nullptr, nullptr)};
    int args = 0;
};

TEST_F(PlanRunnerTesting, start) { EXPECT_EQ(runner->getDescriptionOfInterval().toStdString(), "first"); }

TEST_F(PlanRunnerTesting, getIntervalDuration) { EXPECT_EQ(runner->getIntervalDuration(), 100); }

TEST_F(PlanRunnerTesting, getIntervalElapsedTime) {
    intervalTimer->setElapsedTime(std::chrono::milliseconds{42});
    EXPECT_EQ(runner->getIntervalElapsedTime(), 42);
}

TEST_F(PlanRunnerTesting, emitChangedIntervalDurationRunningTime) {
    QSignalSpy spy(runner, SIGNAL(changedIntervalDurationRunningTime()));
    intervalRefreshingTimer->emitTimeout();
    EXPECT_EQ(spy.count(), 1);
}

TEST_F(PlanRunnerTesting, intervalIsFinished) {
    QSignalSpy spyIntervalCompleteTime(runner, SIGNAL(changedIntervalDurationCompleteTime()));
    QSignalSpy spyIntervalDescription(runner, SIGNAL(changedDescriptionOfInterval()));
    QSignalSpy spyIntervalRunningTime(runner, SIGNAL(changedIntervalDurationRunningTime()));
    intervalTimer->emitTimeout();
    EXPECT_EQ(spyIntervalCompleteTime.count(), 1);
    EXPECT_EQ(spyIntervalDescription.count(), 1);
    EXPECT_EQ(spyIntervalRunningTime.count(), 1);
    EXPECT_EQ(runner->getDescriptionOfInterval().toStdString(), "second");
}

TEST_F(PlanRunnerTesting, getPlanDurationCompleteTime) {
    EXPECT_EQ(runner->getPlanDurationCompleteTime(), plan->getDuration().count());
}

TEST_F(PlanRunnerTesting, getPlanDurationRunningTime) {
    planTimer->setElapsedTime(std::chrono::milliseconds{42});
    EXPECT_EQ(runner->getPlanDurationRunningTime(), 42);
}

TEST_F(PlanRunnerTesting, changedPlanRunningTime) {
    QSignalSpy spy(runner, SIGNAL(changedPlanDurationRunningTime()));
    planRefreshingTimer->emitTimeout();
    EXPECT_EQ(spy.count(), 1);
}

TEST_F(PlanRunnerTesting, Restart) {
    EXPECT_EQ(runner->getDescriptionOfInterval().toStdString(), "first");
    intervalTimer->emitTimeout();
    EXPECT_EQ(runner->getDescriptionOfInterval().toStdString(), "second");
    runner->stop();
    runner->start();
    EXPECT_EQ(runner->getDescriptionOfInterval().toStdString(), "first");
    intervalTimer->emitTimeout();
    EXPECT_EQ(runner->getDescriptionOfInterval().toStdString(), "second");
}

TEST_F(PlanRunnerTesting, emptyPlan) {
    auto plan = std::make_shared<Plan>();
    runner->setPlan(plan);
    runner->start();
    EXPECT_EQ(runner->getIntervalDuration(), -1);
}
