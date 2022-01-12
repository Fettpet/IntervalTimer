#include "IntervalToJson.h"

QJsonObject IntervalToJson::transform(Interval const& interval) {
    QJsonObject result{
        qMakePair(
            QString("durationMilliseconds"),
            QJsonValue(static_cast<qint64>(interval.getDuration<std::chrono::milliseconds>().count()))),
        qMakePair(QString("description"), QJsonValue(interval.getDescription()))};
    return result;
}
