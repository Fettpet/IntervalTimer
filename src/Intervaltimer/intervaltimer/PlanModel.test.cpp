#include <Interval.h>
#include <Plan.h>
#include <PlanModel.h>
#include <QSignalSpy>
#include <gtest/gtest.h>

struct PlanModelTesting : ::testing::Test {
protected:
    void SetUp() override {
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
        planForModel->setName("Root");
        planForModel->setItemAt(0, plan);

        model = new PlanModel();
        model->setPlan(plan);
    }

public:
    std::shared_ptr<Plan> nestedPlan{new Plan{}};
    std::shared_ptr<Plan> plan{new Plan{}};
    std::shared_ptr<Plan> planForModel{new Plan{}};
    PlanModel* model;
};

TEST_F(PlanModelTesting, numberColumns) { //
    EXPECT_EQ(model->columnCount(), 2);
}

TEST_F(PlanModelTesting, rowCountRoot) { //
    EXPECT_EQ(model->rowCount(), plan->getNumberItems());
}

TEST_F(PlanModelTesting, rowCountInner) { //
    QModelIndex index = model->index(2, 0);
    EXPECT_EQ(model->rowCount(index), nestedPlan->getNumberItems());
}

TEST_F(PlanModelTesting, indexRootInterval) {
    QModelIndex index = model->index(0, 0);
    EXPECT_EQ(index.row(), 0);
    constexpr int IntervalColumn = 1;
    EXPECT_EQ(index.column(), IntervalColumn);
    EXPECT_EQ(index.internalPointer(), static_cast<void*>(plan.get()));
}

TEST_F(PlanModelTesting, indexRootSubplan) {
    QModelIndex index = model->index(2, 0);
    EXPECT_EQ(index.row(), 2);
    constexpr int PlanColumn = 0;
    EXPECT_EQ(index.column(), PlanColumn);
    EXPECT_EQ(index.internalPointer(), static_cast<void*>(nestedPlan.get()));
}

TEST_F(PlanModelTesting, isRoot) { //
    model->setPlan(planForModel);
    EXPECT_TRUE(model->getIsRoot());
    model->setPlan(nestedPlan);
    EXPECT_FALSE(model->getIsRoot());
}
