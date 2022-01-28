#include "PlanFromJson.h"
#include "IntervalFromJson.h"

std::shared_ptr<Plan> PlanFromJson::transform(const QJsonArray& array) {
    auto result = std::shared_ptr<Plan>(new Plan{});

    result->setName(array.at(0).toString());
    result->setNumberRepetitions(array.at(1).toInt());
    for (auto i = 2; i < array.size(); ++i) {
        if (array.at(i).isObject()) {
            result->appendInterval();
            result->setItemAt(i - 2, IntervalFromJson::transform(array.at(i).toObject()));
        }
        else if (array.at(i).isArray()) {
            result->appendPlan();
            result->setItemAt(i - 2, PlanFromJson::transform(array.at(i).toArray()));
        }
        else {
            qWarning() << "Not supported";
        }
    }
    return result;
}

std::shared_ptr<Plan> PlanFromJson::transform(const QJsonDocument& document) {
    return PlanFromJson::transform(document.array());
}

std::shared_ptr<Plan> PlanFromJson::transform(const QString& str) {
    auto json = QJsonDocument::fromJson(str.toLocal8Bit());
    return PlanFromJson::transform(json);
}
