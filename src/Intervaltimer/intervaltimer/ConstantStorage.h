#pragma once

#include <QObject>
#include <QString>
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
    Q_PROPERTY(QString qtVersion READ getQtVersion CONSTANT);

    static ConstantStorage* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);
    ~ConstantStorage() override = default;

    [[nodiscard]] int getProjectVersionPatch() const;
    [[nodiscard]] int getProjectVersionMinor() const;
    [[nodiscard]] int getProjectVersionMajor() const;
    [[nodiscard]] QString getQtVersion() const;
};
