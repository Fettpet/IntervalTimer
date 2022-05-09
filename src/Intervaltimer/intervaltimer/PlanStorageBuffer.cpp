#include "PlanStorageBuffer.h"

void PlanStorageBuffer::insert(const QString& name, std::shared_ptr<Plan> const& plan) { data.insert(name, plan); }

bool PlanStorageBuffer::contains(QString const& name) { return data.contains(name); }
void PlanStorageBuffer::remove(QString const& name) { data.remove(name); }
QString PlanStorageBuffer::getKey(size_t const& index) {
    Q_ASSERT(index < data.size());
    auto it = data.keyBegin();
    for (auto i = 0; i < index; ++i) {
        ++it;
    }
    return *it;
}

QList<QString> PlanStorageBuffer::keys() const { return data.keys(); }

std::shared_ptr<Plan> PlanStorageBuffer::getValue(const QString& key) { return data.value(key); }
std::shared_ptr<Plan> PlanStorageBuffer::getValue(size_t const& index) {
    Q_ASSERT(index < data.size());
    auto it = data.begin();
    for (auto i = 0; i < index; ++i) {
        ++it;
    }
    return it.value();
}
