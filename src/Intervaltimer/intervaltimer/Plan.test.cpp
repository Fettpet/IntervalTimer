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

        plan->setItemAt(0, outerFirst);
        plan->setItemAt(1, outerSecond);
        nestedPlan->setName("Inner");
        nestedPlan->setNumberRepetitions(12);
        nestedPlan->appendInterval();
        nestedPlan->appendInterval();
        nestedPlan->setItemAt(0, innerFirst);
        nestedPlan->setItemAt(1, innerSecond);
        plan->setItemAt(2, nestedPlan);
    }

public:
    std::shared_ptr<Plan> nestedPlan{new Plan{}};
    std::shared_ptr<Plan> plan{new Plan{}};
    Interval outerFirst = Interval{std::chrono::seconds{1}, "first"};
    Interval outerSecond = Interval{std::chrono::seconds{2}, "second"};
    Interval innerFirst = Interval{std::chrono::seconds{3}, "third"};
    Interval innerSecond = Interval{std::chrono::seconds{4}, "fourth"};
};

TEST_F(PlanTesting, equals) {
    EXPECT_TRUE(*plan == *plan);
    EXPECT_FALSE(*plan == *nestedPlan);

    auto secondPlan = *plan;
    EXPECT_TRUE(secondPlan == *plan);

    secondPlan.getPlanAt(2)->setItemAt(0, innerSecond);
    EXPECT_FALSE(secondPlan == *plan);
}

TEST_F(PlanTesting, getRow) {
    EXPECT_EQ(plan->getRow(), 0);
    EXPECT_EQ(nestedPlan->getRow(), 2);
}

TEST_F(PlanTesting, duration) { EXPECT_EQ(plan->getDuration(), std::chrono::seconds{10 * (1 + 2 + 12 * (3 + 4))}); }
TEST_F(PlanTesting, appendInterval) {
    auto intervalItem = plan->getItemAt(0);
    EXPECT_TRUE(intervalItem.canConvert<Interval>());
    EXPECT_FALSE(intervalItem.canConvert<std::shared_ptr<Plan>>());
}

TEST_F(PlanTesting, parentOfInterval) {
    auto interval = plan->getItemAt(0).value<Interval>();
    EXPECT_FALSE(interval.getParent().expired());
    EXPECT_EQ(interval.getParent().lock(), plan);
}

TEST_F(PlanTesting, appendPlan) {
    auto planItem = plan->getItemAt(2);
    EXPECT_FALSE(planItem.canConvert<Interval>());
    EXPECT_TRUE(planItem.canConvert<std::shared_ptr<Plan>>());
}

TEST_F(PlanTesting, setInterval) {
    auto interval = Interval{std::chrono::seconds{2}, "2s"};
    plan->setItemAt(1, interval);

    EXPECT_EQ(plan->getItemAt(1).value<Interval>(), interval);
}

TEST_F(PlanTesting, checkParent) {
    auto nestedPlan = plan->getItemAt(2).value<std::shared_ptr<Plan>>();

    EXPECT_EQ(nestedPlan->getParentPlan().lock(), plan);
}

TEST_F(PlanTesting, setPlan) {
    auto plan = Plan::create();
    auto planItem = Plan::create();
    planItem->setNumberRepetitions(42);
    plan->appendPlan();
    plan->setItemAt(0, planItem);

    EXPECT_EQ(
        plan->getItemAt(0).value<std::shared_ptr<Plan>>()->getNumberRepetitions(), planItem->getNumberRepetitions());
}

TEST_F(PlanTesting, toJson_IntervalsOnly) {
    auto nestedPlan = plan->getItemAt(2).value<std::shared_ptr<Plan>>();
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

TEST_F(PlanTesting, isIntervalAt) {
    EXPECT_TRUE(plan->isIntervalAt(0));
    EXPECT_FALSE(plan->isIntervalAt(2));
}

TEST_F(PlanTesting, isPlanAt) {
    EXPECT_FALSE(plan->isPlanAt(0));
    EXPECT_TRUE(plan->isPlanAt(2));
}

TEST_F(PlanTesting, getIntervalAt) {
    EXPECT_EQ(plan->getIntervalAt(0), outerFirst);

    EXPECT_ANY_THROW((void)plan->getIntervalAt(2));
}

TEST_F(PlanTesting, getPlanAt) {
    EXPECT_EQ(plan->getPlanAt(2), nestedPlan);

    EXPECT_ANY_THROW((void)plan->getPlanAt(1));
}

TEST_F(PlanTesting, operatorCopy) {
    auto copiedPlan = *plan;
    auto secondPlan = *plan;
    copiedPlan = secondPlan;
    EXPECT_EQ(copiedPlan.getName(), QString("Outer"));
    EXPECT_EQ(copiedPlan.getNumberRepetitions(), 10);
    EXPECT_EQ(copiedPlan.getIntervalAt(0), plan->getIntervalAt(0));
    EXPECT_EQ(copiedPlan.getIntervalAt(1), plan->getIntervalAt(1));
    EXPECT_EQ(*copiedPlan.getPlanAt(2), *(plan->getPlanAt(2)));
    EXPECT_EQ(copiedPlan.getNumberItems(), 3);
    EXPECT_EQ(copiedPlan.getPlanAt(2)->getNumberItems(), 2);
}
