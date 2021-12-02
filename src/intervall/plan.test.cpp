#pragma once
#include <gtest/gtest.h>
#include <intervall/plan.h>

TEST(Plan, AddIntervall) {
    auto plan = Plan{};
    auto intervall1 = Intervall{std::chrono::seconds{1}, "1s"};
    auto intervall2 = Intervall{std::chrono::seconds{2}, "2s"};
    plan.addIntervall(intervall1);
    plan.addIntervall(intervall2);

    EXPECT_EQ(plan.getNumberIntervalls(), 2);
    EXPECT_EQ(plan.getIntervall(0), intervall1);
    EXPECT_EQ(plan.getIntervallRef(1), intervall2);
}

TEST(Plan, RemoveIntervall) {
    auto plan = Plan{};
    auto intervall1 = Intervall{std::chrono::seconds{1}, "1s"};
    auto intervall2 = Intervall{std::chrono::seconds{2}, "2s"};
    plan.addIntervall(intervall1);
    plan.addIntervall(intervall2);

    plan.removeIntervall(0);
    EXPECT_EQ(plan.getNumberIntervalls(), 1);
    EXPECT_EQ(plan.getIntervall(0), intervall2);
}

TEST(Plan, numberRepetions) {
    auto plan = Plan{};
    EXPECT_EQ(plan.getNumberRepetitions(), 1);

    plan.setNumberRepetitions(42);
    EXPECT_EQ(plan.getNumberRepetitions(), 42);
}

TEST(Plan, AddPlan) {
    auto intervall1 = Intervall{std::chrono::seconds{1}, "1s"};
    auto intervall2 = Intervall{std::chrono::seconds{2}, "2s"};
    auto intervall3 = Intervall{std::chrono::seconds{3}, "3s"};
    auto intervall4 = Intervall{std::chrono::seconds{4}, "4s"};
    auto plan1 = Plan{};
    plan1.addIntervall(intervall1);
    plan1.addIntervall(intervall2);

    auto plan2 = Plan{};
    plan2.addIntervall(intervall3);
    plan2.addIntervall(intervall4);

    auto plan = Plan{};
    plan.addPlan(plan1);
    plan.addPlan(plan2);

    EXPECT_EQ(plan.getNumberPlans(), 2);
    EXPECT_EQ(plan.getPlan(0), plan1);
    EXPECT_EQ(plan.getPlanRef(1), plan2);
}

TEST(Plan, RemovePlan) {
    auto intervall1 = Intervall{std::chrono::seconds{1}, "1s"};
    auto intervall2 = Intervall{std::chrono::seconds{2}, "2s"};
    auto intervall3 = Intervall{std::chrono::seconds{3}, "3s"};
    auto intervall4 = Intervall{std::chrono::seconds{4}, "4s"};
    auto plan1 = Plan{};
    plan1.addIntervall(intervall1);
    plan1.addIntervall(intervall2);

    auto plan2 = Plan{};
    plan2.addIntervall(intervall3);
    plan2.addIntervall(intervall4);

    auto plan = Plan{};
    plan.addPlan(plan1);
    plan.addPlan(plan2);
    plan.removePlan(0);
    EXPECT_EQ(plan.getNumberPlans(), 1);
    EXPECT_EQ(plan.getPlan(0), plan2);
}
