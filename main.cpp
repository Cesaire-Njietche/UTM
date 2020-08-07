#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "dronemanager.h"
#include "dronemodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<droneModel>("Kea", 1, 0, "DroneModel");

    droneManager _dm;

    //_dm.fetchDB();

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("DM", &_dm);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    /*QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);*/
    engine.load(url);

    return app.exec();
}
