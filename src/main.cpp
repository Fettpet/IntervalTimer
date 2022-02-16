#include <Plan.h>
#include <PlanModel.h>
#include <PlanRunner.h>
#include <PlanStorageModel.h>
#include <QGuiApplication>
#include <QLocale>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTranslator>

int main(int argc, char* argv[]) {
    QGuiApplication app(argc, argv);

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

    auto plan = std::make_shared<Plan>();

    PlanModel::create(nullptr, nullptr)->setPlan(plan);

    engine.addImportPath(QStringLiteral("qrc:/"));
    PlanRunner::create(nullptr, nullptr)->setPlan(plan);
    PlanStorageModel::create(nullptr, nullptr)->setPlan(plan);
    QObject::connect(
        PlanStorageModel::create(nullptr, nullptr),
        SIGNAL(planChanged()),
        PlanModel::create(nullptr, nullptr),
        SLOT(reset()));

    const QUrl url(u"qrc:/IntervalApplication/main.qml"_qs);
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
