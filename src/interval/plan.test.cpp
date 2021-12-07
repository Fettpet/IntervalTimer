#include <QSignalSpy>
#include <gtest/gtest.h>
#include <interval/plan.h>

struct PlanTesting : ::testing::Test {
protected:
    void SetUp() override {
        plan->appendInterval();
        plan->appendPlan();
    }

public:
    Plan* plan = new Plan{};
};

TEST_F(PlanTesting, appendInterval) {
    auto intervalItem = plan->getItemAt(0);
    EXPECT_TRUE(intervalItem.canConvert<Interval>());
    EXPECT_FALSE(intervalItem.canConvert<Plan*>());
}

TEST_F(PlanTesting, appendPlan) {
    auto planItem = plan->getItemAt(1);
    EXPECT_FALSE(planItem.canConvert<Interval>());
    EXPECT_TRUE(planItem.canConvert<Plan*>());
}

TEST_F(PlanTesting, setInterval) {
    auto interval = Interval{std::chrono::seconds{2}, "2s"};
    plan->setItemAt(1, interval);

    EXPECT_EQ(plan->getItemAt(1).value<Interval>(), interval);
}

TEST_F(PlanTesting, setPlan) {
    auto planItem = new Plan{};
    planItem->setNumberRepetitions(42);
    plan->setItemAt(0, planItem);

    EXPECT_EQ(plan->getItemAt(0).value<Plan*>()->getNumberRepetitions(), planItem->getNumberRepetitions());
}

TEST_F(PlanTesting, CheckSignalsAppendInterval) {
    auto preSpy = QSignalSpy(plan, &Plan::preItemAppended);
    auto postSpy = QSignalSpy(plan, &Plan::postItemAppended);

    plan->appendInterval();

    EXPECT_EQ(preSpy.count(), 1);
    EXPECT_EQ(postSpy.count(), 1);
}

TEST_F(PlanTesting, CheckSignalsAppendPlan) {
    auto preSpy = QSignalSpy(plan, &Plan::preItemAppended);
    auto postSpy = QSignalSpy(plan, &Plan::postItemAppended);

    plan->appendPlan();

    EXPECT_EQ(preSpy.count(), 1);
    EXPECT_EQ(postSpy.count(), 1);
}

TEST(Plan, numberRepetions) {
    auto plan = Plan{};
    EXPECT_EQ(plan.getNumberRepetitions(), 1);

    plan.setNumberRepetitions(42);
    EXPECT_EQ(plan.getNumberRepetitions(), 42);
}
