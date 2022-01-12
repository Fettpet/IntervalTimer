#include <Plan.h>
#include <PlanModel.h>
#include <PlanRunner.h>
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
    auto nestedPlan = std::make_shared<Plan>();
    nestedPlan->setName("Inner");
    nestedPlan->setNumberRepetitions(12);
    nestedPlan->appendInterval();
    nestedPlan->appendInterval();
    nestedPlan->setItemAt(0, Interval{std::chrono::seconds{3}, "third"});
    nestedPlan->setItemAt(1, Interval{std::chrono::seconds{4}, "fourth"});

    auto plan = std::make_shared<Plan>();
    plan->setName("Outer");
    plan->setNumberRepetitions(10);
    plan->appendInterval();
    plan->appendInterval();
    plan->appendPlan();
    auto outerFirst = Interval{std::chrono::seconds{1}, "first"};
    auto outerSecond = Interval{std::chrono::seconds{2}, "second"};
    plan->setItemAt(0, outerFirst);
    plan->setItemAt(1, outerSecond);
    plan->setItemAt(2, nestedPlan);

    auto planToModel = std::make_shared<Plan>();
    planToModel->appendPlan();
    planToModel->setName("Wurzel");
    planToModel->setItemAt(0, plan);

    auto model = PlanModel();
    model.setPlan(plan);

    PlanRunner planRunner;
    planRunner.setPlan(plan);
    engine.rootContext()->setContextProperty(QStringLiteral("rootPlanModel"), &model);
    engine.rootContext()->setContextProperty(QStringLiteral("rootPlanRunner"), &planRunner);
    engine.addImportPath(QStringLiteral("qrc:/"));

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
