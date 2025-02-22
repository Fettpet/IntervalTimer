#pragma once
#include <QQmlEngine>
#include <QtQml/qqmlregistration.h>

#include "Plan.h"
#include "PlanIterator.h"
#include <QObject>
#include <QThread>

#include <memory>

#include "Timer.h"
#include "TimerBase.h"

class PlanRunner : public QObject {

    Q_OBJECT
    QML_SINGLETON
    QML_NAMED_ELEMENT(PlanRunner)

    Q_PROPERTY(QString intervalDescription READ getDescriptionOfInterval NOTIFY changedDescriptionOfInterval);
    Q_PROPERTY(int intervalDurationCompleteTime READ getIntervalDuration NOTIFY changedIntervalDurationCompleteTime);
    Q_PROPERTY(int intervalDurationRunningTime READ getIntervalElapsedTime NOTIFY changedIntervalDurationRunningTime);
    Q_PROPERTY(int refreshingTimeForInterval READ getRefreshingTimeInterval WRITE setRefreshingTimeInterval NOTIFY
                   changedRefreshingTimeForInterval);
    Q_PROPERTY(int planDurationCompleteTime READ getPlanDurationCompleteTime CONSTANT)
    Q_PROPERTY(int planDurationRunningTime READ getPlanDurationRunningTime NOTIFY changedPlanDurationRunningTime)
    Q_PROPERTY(int refreshingTimeForPlan READ getRefreshingTimePlan WRITE setRefreshingTimePlan NOTIFY
                   changedRefreshingTimeForPlan);

    PlanRunner() = default;
    static PlanRunner* instance;

public:
    static PlanRunner* create(QQmlEngine*, QJSEngine* engine);

    [[nodiscard]] int getPlanDurationCompleteTime() const;
    [[nodiscard]] int getPlanDurationRunningTime() const;

    [[nodiscard]] QString getDescriptionOfInterval() const;

    [[nodiscard]] int getIntervalDuration() const;
    [[nodiscard]] int getIntervalElapsedTime() const;

    [[nodiscard]] std::weak_ptr<Plan> getPlan() const;
    void setPlan(std::shared_ptr<Plan> newPlan);

    [[nodiscard]] int getRefreshingTimeInterval() const;
    void setRefreshingTimeInterval(int const& newTimeMilliseconds);

    [[nodiscard]] int getRefreshingTimePlan() const;
    void setRefreshingTimePlan(int const& newTimeMilliseconds);

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();
    // Q_INVOKABLE void pause();

    void setIntervalTimer(std::shared_ptr<TimerBase> newTimer);
    void setIntervalRefeshingTimer(std::shared_ptr<TimerBase> newTimer);

    void setPlanTimer(std::shared_ptr<TimerBase> newTimer);
    void setPlanRefeshingTimer(std::shared_ptr<TimerBase> newTimer);

protected:
    bool isRunning{false};
    std::shared_ptr<Plan> plan{nullptr};
    PlanIterator iterator{};
    std::shared_ptr<TimerBase> intervalTimer{new Timer{}};
    std::shared_ptr<TimerBase> planRefreshingTimer{new Timer{}};
    std::shared_ptr<TimerBase> planTimer{new Timer{}};
    std::shared_ptr<TimerBase> intervalRefreshingTimer{new Timer{}};
    std::chrono::milliseconds refreshingTimeForRunningInterval{100};
    std::chrono::milliseconds refreshingTimeForRunningPlan{100};
    std::chrono::milliseconds totalDurationOfAllPlans{};

private:
    void startInterval();
    [[nodiscard]] bool intervalIsValid() const;
private slots:
    void changedInterval();
    void changedIntervalRunningTime();
    void changedPlanRunningTime();

signals:
    void changedPlanDurationRunningTime();
    void changedDescriptionOfInterval();
    void finished();
    void changedIntervalDurationCompleteTime();
    void changedIntervalDurationRunningTime();
    void startRunning();
    void changedRefreshingTimeForPlan();
    void changedRefreshingTimeForInterval();
    // void changedCurrentDurationOfIntervalMilliseconds();
    // void changedCurrentDurationOfAllPlansMilliseconds();
    // void changedPlan();
};
