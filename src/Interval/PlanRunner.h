#pragma once

#include "Plan.h"
#include "PlanIterator.h"
#include <QObject>
#include <QThread>
#include <QtQml/qqmlregistration.h>
#include <memory>

#include <QTimer>

class PlanRunner : public QObject {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString intervalDescription READ getDescriptionOfInterval NOTIFY changedDescriptionOfInterval);
    Q_PROPERTY(int intervalDurationCompleteTime READ getIntervalDurationCompleteTime NOTIFY
                   changedIntervalDurationCompleteTime);
    Q_PROPERTY(
        int intervalDurationRunningTime READ getIntervalDurationRunningTime NOTIFY changedIntervalDurationRunningTime);
    Q_PROPERTY(int refreshingTimeForInterval READ getRefreshingTimeInterval WRITE setRefreshingTimeInterval);
    // Q_PROPERTY(int totalDurationOfAllPlansMilliseconds READ getTotalDurationOfAllPlansMilliseconds)
    // Q_PROPERTY(int currentDurationOfAllPlansMilliseconds READ getCurrentDurationOfAllPlansMilliseconds NOTIFY
    //                changedCurrentDurationOfAllPlansMilliseconds)
    // Q_PROPERTY(int refreshingTimeForTotalPlanMilliseconds READ getRefreshingTimeForTotalPlanMilliseconds WRITE
    //                setRefreshingTimeForTotalPlanMilliseconds);

public:
    PlanRunner(QObject* = nullptr);
    ~PlanRunner();

    QString getDescriptionOfInterval() const;

    int getIntervalDurationCompleteTime() const;

    int getIntervalDurationRunningTime() const;

    std::weak_ptr<Plan> getPlan() const;
    void setPlan(std::shared_ptr<Plan>);

    int getRefreshingTimeInterval() const;
    void setRefreshingTimeInterval(int const&);

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();
    // Q_INVOKABLE void pause();

    void setIntervalTimer(std::shared_ptr<QTimer> newTimer);

protected:
    bool isRunning{false};
    std::shared_ptr<Plan> plan{nullptr};
    PlanIterator iterator{};
    std::shared_ptr<QTimer> intervalTimer{new QTimer{}};
    std::shared_ptr<QTimer> intervalRunningTimer{new QTimer{}};
    std::unique_ptr<QThread> timerThread{new QThread{}};
    std::chrono::milliseconds refreshingTimeForRunningInterval{500};

private:
    void startInterval();

private slots:
    void changedInterval();
    void changedIntervalRunningTime();

signals:
    void changedDescriptionOfInterval();
    void finished();
    void changedIntervalDurationCompleteTime();
    void changedIntervalDurationRunningTime();
    // void changedCurrentDurationOfIntervalMilliseconds();
    // void changedCurrentDurationOfAllPlansMilliseconds();
    // void changedPlan();
};
