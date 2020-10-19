#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <filament/FilamentAPI.h>
#include <filament/Engine.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);


    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

//    filament::Engine *f_engine = filament::Engine::create();
//    f_engine->destroy(&f_engine);

    return app.exec();
//    return 0;
}
