#include <DatabaseProvider.h>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <gtest/gtest.h>
#include <memory>

struct DatabaseProviderTest : public ::testing::Test {

    void SetUp() override {

        database = std::make_shared<QSqlDatabase>();
        provider.setDatabasePath(":memory:");
        provider.setDatabase(database);
        provider.initialize();

        plan->setName("Ou'ter");
        plan->setNumberRepetitions(10);
        plan->appendInterval();
        plan->appendInterval();
        plan->appendPlan();
        auto outerFirst = Interval{std::chrono::seconds{1}, "first"};
        auto outerSecond = Interval{std::chrono::seconds{2}, "second"};
        plan->setItemAt(0, outerFirst);
        plan->setItemAt(1, outerSecond);
        std::shared_ptr<Plan> nestedPlan{Plan::create()};
        nestedPlan->setName("Inner");
        nestedPlan->setNumberRepetitions(12);
        nestedPlan->appendInterval();
        nestedPlan->appendInterval();
        nestedPlan->setItemAt(0, Interval{std::chrono::seconds{3}, "third"});
        nestedPlan->setItemAt(1, Interval{std::chrono::seconds{4}, "fourth"});
        plan->setItemAt(2, nestedPlan);
    }

    std::shared_ptr<Plan> plan{Plan::create()};

    std::shared_ptr<QSqlDatabase> database;
    DatabaseProvider provider;
};

TEST_F(DatabaseProviderTest, Initialize) {
    auto tables = database->tables();
    EXPECT_EQ(tables, QStringList{"Plans"});
}

TEST_F(DatabaseProviderTest, storePlan) {
    provider.storePlan("Test", plan);
    auto query = QSqlQuery(QString("Select * from Plans;"), *database);
    EXPECT_TRUE(query.exec());
    EXPECT_TRUE(query.first());
    EXPECT_TRUE(query.isValid());
    auto record = query.record();
    auto name = record.value("name");
    EXPECT_EQ(name.toString().toStdString(), "Test");
    EXPECT_FALSE(query.next());
}

TEST_F(DatabaseProviderTest, containsPlan) {
    provider.storePlan("Test", plan);
    EXPECT_TRUE(provider.containsPlan("Test"));
    EXPECT_FALSE(provider.containsPlan("Test2"));
}

TEST_F(DatabaseProviderTest, updatePlan) {
    provider.storePlan("Test", plan);
    auto newPlan = provider.loadPlan("Test");
    EXPECT_EQ(newPlan->getName(), "Ou'ter");
    newPlan->setName("Updated");
    provider.storePlan("Test", newPlan);
    auto updatedPlan = provider.loadPlan("Test");
    EXPECT_EQ(updatedPlan->getName(), "Updated");
}

TEST_F(DatabaseProviderTest, insertAndLoad) {
    provider.storePlan("Test", plan);
    auto newPlan = provider.loadPlan("Test");
    EXPECT_NE(newPlan, plan);
    EXPECT_EQ(*newPlan, *plan);
}

TEST_F(DatabaseProviderTest, LoadCheckOuterPlan) {
    std::shared_ptr<Plan> planPtr{Plan::create()};
    provider.storePlan("Test", plan);
    planPtr = provider.loadPlan("Test");
    auto nbItems = planPtr->getNumberItems();
    planPtr->appendInterval();
    planPtr->appendInterval();
    provider.storePlan("Test2", planPtr);
    EXPECT_EQ(nbItems + 2, planPtr->getNumberItems());
    (planPtr) = provider.loadPlan("Test");

    EXPECT_EQ(nbItems, planPtr->getNumberItems());
}

TEST_F(DatabaseProviderTest, LoadCheckInnerPlan) {
    provider.storePlan("Test", plan);
    auto innerPlanPtr = *reinterpret_cast<std::shared_ptr<Plan>*>(plan->getItemAt(2).data());
    auto nbItemsInnerPlan = innerPlanPtr->getNumberItems();
    innerPlanPtr->appendInterval();
    std::shared_ptr<Plan> planPtr{Plan::create()};
    (planPtr) = provider.loadPlan("Test");
    auto loadedPlanPtr = *reinterpret_cast<std::shared_ptr<Plan>*>(planPtr->getItemAt(2).data());

    EXPECT_EQ(nbItemsInnerPlan, loadedPlanPtr->getNumberItems());
}
