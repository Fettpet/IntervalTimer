#pragma once
#include "Plan.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QString>

struct PlanFromJson {
    static std::shared_ptr<Plan> transform(QJsonArray const&);
    static std::shared_ptr<Plan> transform(QJsonDocument const&);
    static std::shared_ptr<Plan> transform(QString const&);
};
