#include <DatabaseProvider.h>
#include <Interval.h>
#include <Plan.h>
#include <PlanStorageModel.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <gtest/gtest.h>
#include <memory>

struct PlanStorageModelTesting : ::testing::Test {
protected:
    void SetUp() override {
        database = std::make_shared<QSqlDatabase>();
        provider.setDatabasePath(":memory:");
        provider.setDatabase(database);
        provider.initialize();
        provider.storePlan("Test1", *(createPlan("Test1")));
        provider.storePlan("Test2", *(createPlan("Test2")));
        provider.storePlan("Test3", *(createPlan("Test3")));
        model = PlanStorageModel::create(nullptr, nullptr);
        model->setDatabaseProvider(&provider);
    }

    static std::shared_ptr<Plan> createPlan(QString const& name) {
        std::shared_ptr<Plan> nestedPlan{new Plan{}};
        std::shared_ptr<Plan> plan{new Plan{}};
        std::shared_ptr<Plan> planForModel{new Plan{}};

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
    std::shared_ptr<QSqlDatabase> database;
    DatabaseProvider provider;
    PlanStorageModel* model{nullptr};
};

TEST_F(PlanStorageModelTesting, countInit) { //
    EXPECT_EQ(model->rowCount(), 3);
}

TEST_F(PlanStorageModelTesting, countAfterAppendPlan) { //
    auto plan = createPlan("Test4");
    model->setPlan(plan);
    model->appendPlan("Test4");
    EXPECT_EQ(model->rowCount(), 4);
}

TEST_F(PlanStorageModelTesting, containsPlan) { //
    auto plan = createPlan("Test");
    model->setPlan(plan);
    model->appendPlan("Test4");
    EXPECT_TRUE(model->containsPlan("Test4"));
    EXPECT_FALSE(model->containsPlan("Test6"));
}

TEST_F(PlanStorageModelTesting, countAfterRemovePlan) { //
    model->removePlan("Test1");
    EXPECT_EQ(model->rowCount(), 2);
}

TEST_F(PlanStorageModelTesting, countAfterRemovePlanFailed) { //
    model->removePlan("NotFound");
    EXPECT_EQ(model->rowCount(), 3);
}

TEST_F(PlanStorageModelTesting, countDatabase) { //
    QSqlQuery query(*database);
    query.prepare("SELECT COUNT(name) FROM plans;");
    EXPECT_TRUE(query.exec());
    EXPECT_TRUE(query.first());
    auto record = query.record();
    EXPECT_EQ(record.value(0), 3);
}

TEST_F(PlanStorageModelTesting, countDatabaseAfterAppendPlan) { //
    auto plan = createPlan("Test4");
    model->setPlan(plan);
    model->appendPlan("Test4");
    QSqlQuery query(*database);
    query.prepare("SELECT COUNT(name) FROM plans;");
    EXPECT_TRUE(query.exec());
    EXPECT_TRUE(query.first());
    auto record = query.record();
    EXPECT_EQ(record.value(0), 4);
}

TEST_F(PlanStorageModelTesting, countDatabaseAfterRemovePlan) { //
    model->removePlan("Test1");
    QSqlQuery query(*database);
    query.prepare("SELECT COUNT(name) FROM plans;");
    EXPECT_TRUE(query.exec());
    EXPECT_TRUE(query.first());
    auto record = query.record();
    EXPECT_EQ(record.value(0), 2);
}
