#include "PlanModel.h"
#include <QGuiApplication>
#include <QLocale>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTranslator>
#include <interval/plan.h>

int main(int argc, char* argv[]) {
    QGuiApplication app(argc, argv);

    qmlRegisterType<PlanModel>("interval", 1, 0, "PlanModel");
    qmlRegisterType<Plan>("interval", 1, 0, "Plan");

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString& locale : uiLanguages) {
        const QString baseName = "Intervaltimer_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    QQmlApplicationEngine engine;
    Plan plan{};
    engine.rootContext()->setContextProperty(QStringLiteral("rootPlan"), &plan);

    const QUrl url(u"qrc:/Intervaltimer/qml/main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl) QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
