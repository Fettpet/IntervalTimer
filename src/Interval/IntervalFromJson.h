#pragma once
#include "Interval.h"
#include <QJsonObject>

struct IntervalFromJson {
    static Interval transform(QJsonObject const&);
};
