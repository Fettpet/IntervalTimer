#pragma once
#include "Plan.h"
#include <QJsonArray>

struct PlanFromJson {
    static Plan* transform(QJsonArray const&);
};
