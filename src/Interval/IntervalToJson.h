#pragma once
#include "Interval.h"
#include <QJsonObject>

struct IntervalToJson {

    static QJsonObject transform(Interval const&);
};
