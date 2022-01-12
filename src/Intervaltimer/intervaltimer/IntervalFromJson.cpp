#include "IntervalFromJson.h"

Interval IntervalFromJson::transform(const QJsonObject& json) {
    Interval result;
    result.setDuration(std::chrono::milliseconds{json["durationMilliseconds"].toInteger()});
    result.setDescripton(json["description"].toString());
    return result;
}
