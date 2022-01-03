#pragma once
#include <QDebug>
#include <QMetaType>
#include <QString>
#include <chrono>

struct Interval {
public:
    Interval();
    Interval(std::chrono::milliseconds const&, QString const&);
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

    void setDescripton(QString const&);
    QString getDescripton() const;

protected:
    std::chrono::milliseconds duration{0};
    QString description;
};

QDebug operator<<(QDebug debug, const Interval& interval);

Q_DECLARE_METATYPE(Interval);
