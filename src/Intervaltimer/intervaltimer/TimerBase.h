#pragma once

#include <QObject>
#include <chrono>

class TimerBase : public QObject {
    Q_OBJECT
public:
    explicit TimerBase(QObject* parent = nullptr);

    virtual void start(std::chrono::milliseconds const&) = 0;
    virtual std::chrono::milliseconds getElapsedTime() const = 0;
    virtual std::chrono::milliseconds getDuration() const = 0;
    virtual void stop() = 0;
signals:
    void timeout();
};
