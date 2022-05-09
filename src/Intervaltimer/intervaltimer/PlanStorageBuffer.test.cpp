#include <Plan.h>
#include <PlanStorageBuffer.h>

#include <gtest/gtest.h>
#include <memory>

struct PlanStorageBufferTesting : ::testing::Test {
protected:
    void SetUp() override {
        buffer.insert("Test", createPlan("Test"));
        buffer.insert("Test2", createPlan("Test2"));
        buffer.insert("Test3", createPlan("Test3"));
    }

    static std::shared_ptr<Plan> createPlan(QString const& name) {
        auto nestedPlan = Plan::create();
        auto plan = Plan::create();
        auto planForModel = Plan::create();

        nestedPlan->setName("Inner");
        nestedPlan->setNumberRepetitions(12);
        nestedPlan->appendInterval();
        nestedPlan->appendInterval();
        nestedPlan->setItemAt(0, Interval{std::chrono::seconds{3}, "third"});
        nestedPlan->setItemAt(1, Interval{std::chrono::seconds{4}, "fourth"});

        plan->setName("Outer");
        plan->setNumberRepetitions(10);
        plan->appendInterval();
        plan->appendInterval();
        plan->appendPlan();
        plan->setItemAt(0, Interval{std::chrono::seconds{1}, "first"});
        plan->setItemAt(1, Interval{std::chrono::seconds{2}, "second"});
        plan->setItemAt(2, nestedPlan);

        planForModel->appendPlan();
        planForModel->setName(name);
        planForModel->setItemAt(0, plan);
        return planForModel;
    }

public:
    PlanStorageBuffer buffer;
};

TEST_F(PlanStorageBufferTesting, Contains) {
    EXPECT_TRUE(buffer.contains("Test"));
    EXPECT_FALSE(buffer.contains("hi"));
}

TEST_F(PlanStorageBufferTesting, insert) {
    auto plan = createPlan("hi");
    buffer.insert("hi", plan);
    EXPECT_TRUE(buffer.contains("hi"));
}

TEST_F(PlanStorageBufferTesting, override) {
    auto plan = createPlan("hi");
    buffer.insert("Test", plan);
    EXPECT_TRUE(buffer.contains("Test"));
    auto planLoaded = buffer.getValue(0);
    EXPECT_EQ(planLoaded->getName(), plan->getName());
}

TEST_F(PlanStorageBufferTesting, remove) {
    buffer.remove("Test");
    EXPECT_FALSE(buffer.contains("Test"));
    EXPECT_TRUE(buffer.contains("Test2"));
    EXPECT_TRUE(buffer.contains("Test3"));
}

TEST_F(PlanStorageBufferTesting, getKey) {
    auto key = buffer.getKey(0);
    EXPECT_EQ(key, "Test");
    key = buffer.getKey(1);
    EXPECT_EQ(key, "Test2");
    key = buffer.getKey(2);
    EXPECT_EQ(key, "Test3");
}

TEST_F(PlanStorageBufferTesting, getValue) {
    auto value = buffer.getValue(0);
    EXPECT_EQ(*value, *createPlan("Test"));
}
