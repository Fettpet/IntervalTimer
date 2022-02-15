#include <Interval.h>
#include <Plan.h>
#include <PlanIterator.h>
#include <gtest/gtest.h>
#include <memory>

struct PlanIteratorTesting : ::testing::Test {
protected:
    void SetUp() override {
        nestedPlan->setName("Inner");
        nestedPlan->setNumberRepetitions(2);
        nestedPlan->appendInterval();
        nestedPlan->appendInterval();
        nestedPlan->setItemAt(0, Interval{std::chrono::seconds{2}, "second"});
        nestedPlan->setItemAt(1, Interval{std::chrono::seconds{3}, "third"});

        plan->setName("Outer");
        plan->setNumberRepetitions(1);
        plan->appendInterval();
        plan->appendPlan();
        plan->appendInterval();
        plan->setItemAt(0, Interval{std::chrono::seconds{1}, "first"});
        plan->setItemAt(1, nestedPlan);
        plan->setItemAt(2, Interval{std::chrono::seconds{4}, "fourth"});

        planForModel->appendPlan();
        planForModel->setName("Root");
        planForModel->setItemAt(0, plan);
    }

public:
    std::shared_ptr<Plan> nestedPlan{new Plan{}};
    std::shared_ptr<Plan> plan{new Plan{}};
    std::shared_ptr<Plan> planForModel{new Plan{}};
};

TEST_F(PlanIteratorTesting, emptyPlan) {
    std::shared_ptr<Plan> planForModel{new Plan{}};
    std::shared_ptr<Plan> emptyPlan{new Plan{}};
    planForModel->appendPlan();
    planForModel->setName("Root");
    planForModel->setItemAt(0, emptyPlan);
    auto iterator = PlanIterator{planForModel};
    EXPECT_EQ(iterator, planForModel->end());
}

TEST_F(PlanIteratorTesting, Initalize) {
    auto iterator = PlanIterator{planForModel};
    EXPECT_EQ((*iterator).getDescription(), "first");
}

TEST_F(PlanIteratorTesting, preincrement) {
    auto iterator = PlanIterator{planForModel};
    ++iterator;
    EXPECT_EQ((*iterator).getDescription(), "second");
    ++iterator;
    EXPECT_EQ((*iterator).getDescription(), "third");
    ++iterator;
    EXPECT_EQ((*iterator).getDescription(), "second");
    ++iterator;
    EXPECT_EQ((*iterator).getDescription(), "third");
    ++iterator;
    EXPECT_EQ((*iterator).getDescription(), "fourth");
}

TEST_F(PlanIteratorTesting, postincrement) {
    auto iterator = PlanIterator{planForModel};
    iterator++;
    EXPECT_EQ((*iterator).getDescription(), "second");
    iterator++;
    EXPECT_EQ((*iterator).getDescription(), "third");
    iterator++;
    EXPECT_EQ((*iterator).getDescription(), "second");
    ++iterator;
    EXPECT_EQ((*iterator).getDescription(), "third");
    ++iterator;
    EXPECT_EQ((*iterator).getDescription(), "fourth");
}

TEST_F(PlanIteratorTesting, Access) {
    auto iterator = PlanIterator{planForModel};
    for (auto i = 0; i < 4; ++i) {
        EXPECT_EQ((*iterator).getDescription(), iterator->getDescription());
        ++iterator;
    }
}

TEST_F(PlanIteratorTesting, simpleBeginEnd) {
    QVector<QString> elements = {"second", "third", "second", "third"};
    auto counter = 0;
    for (auto it = nestedPlan->begin(); it != nestedPlan->end(); ++it) {
        EXPECT_EQ(elements[counter++], it->getDescription());
    }
}

TEST_F(PlanIteratorTesting, beginEnd) {
    QVector<QString> elements = {"first", "second", "third", "second", "third", "fourth"};
    auto counter = 0;
    for (auto interval : *plan) {
        EXPECT_EQ(elements[counter++], interval.getDescription());
    }
}
