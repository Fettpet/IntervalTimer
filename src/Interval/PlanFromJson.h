#pragma once
#include "Plan.h"
#include <QJsonArray>
#include <QJsonDocument>

struct PlanFromJson {
    static std::shared_ptr<Plan> transform(QJsonArray const&);
    static std::shared_ptr<Plan> transform(QJsonDocument const&);
};
