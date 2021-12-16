#include <Plan.h>
#include <PlanFromJson.h>
#include <PlanToJson.h>
#include <QJsonArray>
#include <QSignalSpy>
#include <gtest/gtest.h>

struct PlanTesting : ::testing::Test {
protected:
    void SetUp() override {
        plan->setName("Outer");
        plan->setNumberRepetitions(10);
        plan->appendInterval();
        plan->appendInterval();
        plan->appendPlan();
        auto outerFirst = Interval{std::chrono::seconds{1}, "first"};
        auto outerSecond = Interval{std::chrono::seconds{2}, "second"};
        plan->setItemAt(0, outerFirst);
        plan->setItemAt(1, outerSecond);
        nestedPlan->setName("Inner");
        nestedPlan->setNumberRepetitions(12);
        nestedPlan->appendInterval();
        nestedPlan->appendInterval();
        nestedPlan->setItemAt(0, Interval{std::chrono::seconds{3}, "third"});
        nestedPlan->setItemAt(1, Interval{std::chrono::seconds{4}, "fourth"});
        plan->setItemAt(2, nestedPlan);
    }

public:
    Plan* nestedPlan = new Plan{};
    Plan* plan = new Plan{};
};

TEST_F(PlanTesting, getRow) {
    EXPECT_EQ(plan->getRow(), 0);
    EXPECT_EQ(nestedPlan->getRow(), 2);
}

TEST_F(PlanTesting, appendInterval) {
    auto intervalItem = plan->getItemAt(0);
    EXPECT_TRUE(intervalItem.canConvert<Interval>());
    EXPECT_FALSE(intervalItem.canConvert<Plan*>());
}

TEST_F(PlanTesting, appendPlan) {
    auto planItem = plan->getItemAt(2);
    EXPECT_FALSE(planItem.canConvert<Interval>());
    EXPECT_TRUE(planItem.canConvert<Plan*>());
}

TEST_F(PlanTesting, setInterval) {
    auto interval = Interval{std::chrono::seconds{2}, "2s"};
    plan->setItemAt(1, interval);

    EXPECT_EQ(plan->getItemAt(1).value<Interval>(), interval);
}

TEST_F(PlanTesting, checkParent) {
    auto nestedPlan = plan->getItemAt(2).value<Plan*>();

    EXPECT_EQ(nestedPlan->getParent(), plan);
}

TEST_F(PlanTesting, setPlan) {
    auto plan = new Plan{};
    auto planItem = new Plan{};
    planItem->setNumberRepetitions(42);
    plan->appendPlan();
    plan->setItemAt(0, planItem);

    EXPECT_EQ(plan->getItemAt(0).value<Plan*>()->getNumberRepetitions(), planItem->getNumberRepetitions());
}

TEST_F(PlanTesting, CheckSignalsAppendInterval) {
    auto plan = new Plan{};
    auto preSpy = QSignalSpy(plan, &Plan::preItemAppended);
    auto postSpy = QSignalSpy(plan, &Plan::postItemAppended);

    plan->appendInterval();

    EXPECT_EQ(preSpy.count(), 1);
    EXPECT_EQ(postSpy.count(), 1);
}

TEST_F(PlanTesting, CheckSignalsAppendPlan) {
    auto plan = new Plan{};
    auto preSpy = QSignalSpy(plan, &Plan::preItemAppended);
    auto postSpy = QSignalSpy(plan, &Plan::postItemAppended);

    plan->appendPlan();

    EXPECT_EQ(preSpy.count(), 1);
    EXPECT_EQ(postSpy.count(), 1);
}

TEST_F(PlanTesting, toJson_IntervalsOnly) {
    auto nestedPlan = plan->getItemAt(2).value<Plan*>();
    auto json = PlanToJson::transform(*nestedPlan);
    EXPECT_EQ(json.at(2).toObject()["description"].toString(), QString("third"));
    EXPECT_EQ(json.at(3).toObject()["description"].toString(), QString("fourth"));
}

TEST_F(PlanTesting, toJson_Name) {
    auto plan = Plan{};
    plan.setName("42");
    auto json = PlanToJson::transform(plan);
    EXPECT_EQ(json.at(0).toString(), QString("42"));
}

TEST_F(PlanTesting, toJson_NumberRepetions) {
    auto plan = Plan{};
    plan.setNumberRepetitions(42);
    auto json = PlanToJson::transform(plan);
    EXPECT_EQ(json.at(1).toInt(), 42);
}

TEST_F(PlanTesting, toJson_nestedPlan) {
    auto json = PlanToJson::transform(*plan);
    EXPECT_EQ(json.at(4).toArray().at(2).toObject()["description"].toString(), QString("third"));
    EXPECT_EQ(json.at(4).toArray().at(3).toObject()["description"].toString(), QString("fourth"));
}

TEST_F(PlanTesting, fromJson_nestedPlan) {
    auto json = PlanToJson::transform(*plan);

    auto transformedPlan = PlanFromJson::transform(json);

    EXPECT_EQ(*transformedPlan, *plan);
}

TEST_F(PlanTesting, numberRepetions) {
    auto plan = Plan{};
    EXPECT_EQ(plan.getNumberRepetitions(), 1);

    plan.setNumberRepetitions(42);
    EXPECT_EQ(plan.getNumberRepetitions(), 42);
}
