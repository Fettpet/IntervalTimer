#pragma once
#include "Plan.h"
#include <QJsonArray>
#include <QJsonObject>

struct PlanToJson {

    static QJsonArray transform(Plan const&);
};
