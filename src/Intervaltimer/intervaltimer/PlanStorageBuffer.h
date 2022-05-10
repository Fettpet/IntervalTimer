#pragma once
#include "Plan.h"
#include <QString>

class PlanStorageBuffer {
public:
    PlanStorageBuffer() = default;

    virtual void insert(QString const& name, std::shared_ptr<Plan> const& plan);
    [[nodiscard]] virtual bool contains(QString const& name);
    void virtual remove(QString const& name);
    [[nodiscard]] virtual QString getKey(size_t const& index);
    [[nodiscard]] virtual QList<QString> keys() const;
    [[nodiscard]] virtual std::shared_ptr<Plan> getValue(QString const& key);
    [[nodiscard]] virtual std::shared_ptr<Plan> getValue(size_t const& index);

private:
    QMap<QString, std::shared_ptr<Plan>> data;
};
