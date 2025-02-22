#include "PlanToJson.h"
#include "Interval.h"
#include "IntervalToJson.h"
#include "Plan.h"
#include <QJsonArray>

QJsonArray PlanToJson::transform(const Plan& plan) {
    uint32_t counter{2};
    QJsonArray result;
    result.insert(0, plan.getName());
    result.insert(1, QJsonValue(static_cast<qint64>(plan.getNumberRepetitions())));
    auto itemList = plan.getItems();
    for (auto const& item : itemList) {
        if (item.canConvert<Interval>()) {
            result.insert(counter, IntervalToJson::transform(item.value<Interval>()));
        }
        else if (item.canConvert<std::shared_ptr<Plan>>()) {
            result.insert(counter, PlanToJson::transform(*(item.value<std::shared_ptr<Plan>>())));
        }
        else {
            qWarning() << "no known datatype to transform to json";
        }
        ++counter;
    }
    return result;
}
