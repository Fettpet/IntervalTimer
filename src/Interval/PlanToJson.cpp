#include "PlanToJson.h"
#include "Interval.h"
#include "IntervallToJson.h"
#include "Plan.h"
#include <QJsonArray>

QJsonArray PlanToJson::transform(const Plan& plan) {
    uint32_t counter{2};
    QJsonArray result;
    result.insert(0, plan.getName());
    result.insert(1, QJsonValue(static_cast<int>(plan.getNumberRepetitions())));
    auto itemList = plan.getItems();
    for (auto item : itemList) {
        if (item.canConvert<Interval>()) {
            result.insert(counter, IntervallToJson::transform(item.value<Interval>()));
        }
        else if (item.canConvert<Plan*>()) {
            result.insert(counter, PlanToJson::transform(*(item.value<Plan*>())));
        }
        else {
            qWarning() << "no known datatype to transform to json";
        }
        ++counter;
    }
    return result;
}
