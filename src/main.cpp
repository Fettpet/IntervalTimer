#include <Plan.h>
#include <PlanModel.h>
#include <PlanRunner.h>
#include <PlanStorageModel.h>
#include <QGuiApplication>
#include <QLocale>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTranslator>

QUrl getMainQML() {
    return QUrl(u"qrc:/IntervalApplication/mainAndroid.qml"_qs);
    /*
    if (QSysInfo::productType() == "android") {
return QUrl(u"qrc:/IntervalApplication/mainAndroid.qml"_qs);
    }
    if (QSysInfo::productType() == "windows" || QSysInfo::productType() == "winrt" ||
        QSysInfo::kernelType() == "linux") {
        return QUrl(u"qrc:/IntervalApplication/mainDesctop.qml"_qs);
    }

    return QUrl{};
*/
}

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

    auto rootPlanModel = PlanModel();
    rootPlanModel.setPlan(plan);

    engine.addImportPath(QStringLiteral("qrc:/"));
    engine.setInitialProperties({{"rootPlanModel", QVariant::fromValue(&rootPlanModel)}});
    PlanRunner::create(nullptr, nullptr)->setPlan(plan);
    PlanStorageModel::create(nullptr, nullptr)->setPlan(plan);
    QObject::connect(PlanStorageModel::create(nullptr, nullptr), SIGNAL(planChanged()), &rootPlanModel, SLOT(reset()));

    auto url = getMainQML();
    qDebug() << url;
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
