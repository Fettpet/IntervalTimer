#pragma once
#include "Plan.h"
#include <QJsonObject>

struct PlanToJson {

    static QJsonArray transform(Plan const&);
};
