#pragma once
#include <gtest/gtest.h>
#include <interval/plan.h>

TEST(Plan, AddInterval) {
    auto plan = Plan{};
    auto interval1 = Interval{std::chrono::seconds{1}, "1s"};
    auto interval2 = Interval{std::chrono::seconds{2}, "2s"};
    plan.addInterval(interval1);
    plan.addInterval(interval2);

    EXPECT_EQ(plan.getNumberIntervals(), 2);
    EXPECT_EQ(plan.getInterval(0), interval1);
    EXPECT_EQ(plan.getIntervalRef(1), interval2);
}

TEST(Plan, RemoveInterval) {
    auto plan = Plan{};
    auto interval1 = Interval{std::chrono::seconds{1}, "1s"};
    auto interval2 = Interval{std::chrono::seconds{2}, "2s"};
    plan.addInterval(interval1);
    plan.addInterval(interval2);

    plan.removeInterval(0);
    EXPECT_EQ(plan.getNumberIntervals(), 1);
    EXPECT_EQ(plan.getInterval(0), interval2);
}

TEST(Plan, numberRepetions) {
    auto plan = Plan{};
    EXPECT_EQ(plan.getNumberRepetitions(), 1);

    plan.setNumberRepetitions(42);
    EXPECT_EQ(plan.getNumberRepetitions(), 42);
}

TEST(Plan, AddPlan) {
    auto interval1 = Interval{std::chrono::seconds{1}, "1s"};
    auto interval2 = Interval{std::chrono::seconds{2}, "2s"};
    auto interval3 = Interval{std::chrono::seconds{3}, "3s"};
    auto interval4 = Interval{std::chrono::seconds{4}, "4s"};
    auto plan1 = Plan{};
    plan1.addInterval(interval1);
    plan1.addInterval(interval2);

    auto plan2 = Plan{};
    plan2.addInterval(interval3);
    plan2.addInterval(interval4);

    auto plan = Plan{};
    plan.addPlan(plan1);
    plan.addPlan(plan2);

    EXPECT_EQ(plan.getNumberPlans(), 2);
    EXPECT_EQ(plan.getPlan(0), plan1);
    EXPECT_EQ(plan.getPlanRef(1), plan2);
}

TEST(Plan, RemovePlan) {
    auto interval1 = Interval{std::chrono::seconds{1}, "1s"};
    auto interval2 = Interval{std::chrono::seconds{2}, "2s"};
    auto interval3 = Interval{std::chrono::seconds{3}, "3s"};
    auto interval4 = Interval{std::chrono::seconds{4}, "4s"};
    auto plan1 = Plan{};
    plan1.addInterval(interval1);
    plan1.addInterval(interval2);

    auto plan2 = Plan{};
    plan2.addInterval(interval3);
    plan2.addInterval(interval4);

    auto plan = Plan{};
    plan.addPlan(plan1);
    plan.addPlan(plan2);
    plan.removePlan(0);
    EXPECT_EQ(plan.getNumberPlans(), 1);
    EXPECT_EQ(plan.getPlan(0), plan2);
}
