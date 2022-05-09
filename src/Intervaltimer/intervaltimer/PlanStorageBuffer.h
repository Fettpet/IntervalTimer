#pragma once
#include "Plan.h"
#include <QString>

class PlanStorageBuffer {
public:
    PlanStorageBuffer() = default;

    void insert(QString const& name, std::shared_ptr<Plan> const& plan);
    [[nodiscard]] bool contains(QString const& name);
    void remove(QString const& name);
    [[nodiscard]] QString getKey(size_t const& index);
    [[nodiscard]] QList<QString> keys() const;
    [[nodiscard]] std::shared_ptr<Plan> getValue(QString const& key);
    [[nodiscard]] std::shared_ptr<Plan> getValue(size_t const& index);

private:
    QMap<QString, std::shared_ptr<Plan>> data;
};
