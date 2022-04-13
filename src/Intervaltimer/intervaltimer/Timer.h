#pragma once

#include "TimerBase.h"
#include <QObject>
#include <QThread>
#include <QTimer>

class Timer : public TimerBase {
    Q_OBJECT
public:
    explicit Timer(QObject* parent = nullptr);
    ~Timer() override;

    void start(const std::chrono::milliseconds& duration) override;
    [[nodiscard]] std::chrono::milliseconds getElapsedTime() const override;
    [[nodiscard]] std::chrono::milliseconds getDuration() const override;
    void stop() override;

private:
    std::shared_ptr<QTimer> timer{new QTimer{}};
    std::unique_ptr<QThread> thread{new QThread{}};
};
