#ifndef CONSTANTSTORAGE_H
#define CONSTANTSTORAGE_H

#include <QObject>
#include <QtQml/QQmlEngine>

class ConstantStorage : public QObject {
    Q_OBJECT
    QML_SINGLETON
    QML_NAMED_ELEMENT(ConstantStorage)

    ConstantStorage() = default;
    static ConstantStorage* instance;

public:
    Q_PROPERTY(int projectVersionMajor READ getProjectVersionMajor CONSTANT);
    Q_PROPERTY(int projectVersionMinor READ getProjectVersionMinor CONSTANT);
    Q_PROPERTY(int projectVersionPatch READ getProjectVersionPatch CONSTANT);

    static ConstantStorage* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);
    ~ConstantStorage() override = default;

    [[nodiscard]] int getProjectVersionPatch() const;
    [[nodiscard]] int getProjectVersionMinor() const;
    [[nodiscard]] int getProjectVersionMajor() const;
};

#endif // CONSTANTSTORAGE_H
