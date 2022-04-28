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
        model->setPlan(planForModel);
        rootIndex = model->index(0, 0);
    }

public:
    std::shared_ptr<Plan> nestedPlan{Plan::create()};
    std::shared_ptr<Plan> plan{Plan::create()};
    std::shared_ptr<Plan> planForModel{Plan::create()};
    QModelIndex rootIndex;
    PlanModel* model;
};

TEST_F(PlanModelTesting, InnerName) {
    QModelIndex index = model->index(2, 0, rootIndex);
    auto name = model->data(index, PlanModel::nameRole);
    EXPECT_EQ(name.toString(), QString("Inner"));
}

TEST_F(PlanModelTesting, ParentOfPlan) {
    QModelIndex innerIndex = model->index(2, 0, rootIndex);
    QModelIndex parentIndex = model->parent(innerIndex);
    auto name = model->data(parentIndex, PlanModel::nameRole);
    EXPECT_EQ(name.toString(), "Outer");
}

TEST_F(PlanModelTesting, ParentOfInterval) {
    QModelIndex innerIndex = model->index(1, 0, rootIndex);
    QModelIndex parentIndex = model->parent(innerIndex);
    auto name = model->data(parentIndex, PlanModel::nameRole);
    EXPECT_EQ(name.toString(), "Outer");
}

TEST_F(PlanModelTesting, PlanRepetitionCount) {
    QModelIndex index = model->index(2, 0, rootIndex);
    auto name = model->data(index, PlanModel::repetitionCountRole);
    EXPECT_EQ(name.toUInt(), 12);
}

TEST_F(PlanModelTesting, numberColumns) { //
    EXPECT_EQ(model->columnCount(), 2);
}

TEST_F(PlanModelTesting, rowCountRoot) { //
    EXPECT_EQ(model->rowCount(rootIndex), plan->getNumberItems());
}

TEST_F(PlanModelTesting, rowCountInner) { //
    QModelIndex index = model->index(2, 0, rootIndex);
    EXPECT_EQ(model->rowCount(index), nestedPlan->getNumberItems());
}

TEST_F(PlanModelTesting, indexRootInterval) {
    QModelIndex index = model->index(0, 0, rootIndex);
    EXPECT_EQ(index.row(), 0);
    constexpr int IntervalColumn = 1;
    EXPECT_EQ(index.column(), IntervalColumn);
    EXPECT_EQ(index.internalPointer(), static_cast<void*>(plan.get()));
}

TEST_F(PlanModelTesting, indexRootSubplan) {
    QModelIndex index = model->index(2, 0, rootIndex);
    EXPECT_EQ(index.row(), 2);
    constexpr int PlanColumn = 0;
    EXPECT_EQ(index.column(), PlanColumn);
    EXPECT_EQ(index.internalPointer(), static_cast<void*>(nestedPlan.get()));
}
