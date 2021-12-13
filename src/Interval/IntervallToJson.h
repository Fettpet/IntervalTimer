#pragma once
#include "Interval.h"
#include <QJsonObject>

struct IntervallToJson {

    static QJsonObject transform(Interval const&);
};
