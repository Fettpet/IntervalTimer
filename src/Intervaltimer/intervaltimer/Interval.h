#pragma once
#include <QDebug>
#include <QMetaType>
#include <QString>
#include <chrono>
#include <memory>

struct Plan;

struct Interval {
public:
    Interval() = default;
    Interval(std::chrono::milliseconds, QString);
    Interval(std::chrono::milliseconds, QString, std::weak_ptr<Plan>);
    Interval(Interval const&) = default;
    Interval(Interval&&) = default;

    Interval& operator=(Interval const&) = default;
    Interval& operator=(Interval&&) = default;

    auto operator==(Interval const&) const -> bool;
    auto operator!=(Interval const&) const -> bool;

    void setDuration(std::chrono::milliseconds);

    template<typename Duration>
    [[nodiscard]] Duration getDuration() const {
        return std::chrono::duration_cast<Duration>(duration);
    }

    void setDescripton(QString);
    [[nodiscard]] QString getDescription() const;

    void setParent(std::weak_ptr<Plan>);
    [[nodiscard]] std::weak_ptr<Plan> getParent() const;

protected:
    std::chrono::milliseconds duration{0};
    QString description{};
    std::weak_ptr<Plan> parent{};
};

QDebug operator<<(QDebug debug, const Interval& interval);

Q_DECLARE_METATYPE(Interval);
