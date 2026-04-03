#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "bridge.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    BackendBridge bridge;
    engine.rootContext()->setContextProperty("bridge", &bridge);

    engine.loadFromModule("gui_for_cypher", "Main");

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
