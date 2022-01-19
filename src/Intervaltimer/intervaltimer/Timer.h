#pragma once

#include "TimerBase.h"
#include <QObject>
#include <QThread>
#include <QTimer>

class Timer : public TimerBase {
    Q_OBJECT
public:
    explicit Timer(QObject* parent = nullptr);
    ~Timer();

    virtual void start(const std::chrono::milliseconds&) override;

protected:
    std::shared_ptr<QTimer> timer{new QTimer{}};
    std::unique_ptr<QThread> thread{new QThread{}};

signals:
    void timeout();
};
