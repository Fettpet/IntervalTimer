#include <Interval.h>
#include <Plan.h>
#include <PlanIterator.h>
#include <PlanRunner.h>
#include <QCoreApplication>
#include <QSignalSpy>
#include <QThread>
#include <QTimer>
#include <QtTest/QtTest>
#include <gtest/gtest.h>
#include <memory>

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
    }

public:
    std::shared_ptr<Plan> nestedPlan{new Plan{}};
    std::shared_ptr<Plan> plan{new Plan{}};
    std::shared_ptr<Plan> planForModel{new Plan{}};
    std::shared_ptr<QTimer> timer{std::make_shared<QTimer>()};
    PlanRunner* runner{new PlanRunner{}};
    int args = 0;
    std::unique_ptr<QCoreApplication> app = std::make_unique<QCoreApplication>(args, nullptr);
};

TEST_F(PlanRunnerTesting, start) {
    runner->start();
    EXPECT_EQ(runner->getDescriptionOfInterval().toStdString(), "first");
}
