#pragma once
#include "Plan.h"
#include <QJsonArray>

struct PlanFromJson {
    static std::shared_ptr<Plan> transform(QJsonArray const&);
};
