#pragma once
#include <QDebug>
#include <QMetaType>
#include <chrono>
#include <string>

struct Interval {
public:
    Interval();
    Interval(std::chrono::milliseconds const&, std::string const&);
    Interval(Interval const&) = default;
    Interval(Interval&&) = default;

    Interval& operator=(Interval const&) = default;
    Interval& operator=(Interval&&) = default;

    auto operator==(Interval const&) const -> bool = default;
    void setDuration(std::chrono::milliseconds const& dur);

    template<typename Duration>
    Duration getDuration() const {
        return std::chrono::duration_cast<Duration>(duration);
    }

    void setDescripton(std::string const&);
    std::string getDescripton() const;

protected:
    std::chrono::milliseconds duration{0};
    std::string description;
};

QDebug operator<<(QDebug debug, const Interval& interval);

Q_DECLARE_METATYPE(Interval);
