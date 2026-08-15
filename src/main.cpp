#include "backend.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    // 1. Create Qt GUI application
    // Manages the application and event loop
    QGuiApplication app(argc, argv);

    // 2. Create QML engine
    // Loads and manages QML files
    QQmlApplicationEngine engine;

    // 3. Create C++ backend object
    Backend backend;

    // 4. Expose C++ object to QML
    // QML can access it using "backend"
    engine.rootContext()->setContextProperty("backend", &backend);

    // 5. Create another C++ backend object
    Backend_Next backendnext;

    // 6. Expose second object to QML
    // QML can access it using "backendnext"
    engine.rootContext()->setContextProperty("backendnext", &backendnext);

    // 7. QML file location
    // qrc:/ refers to Qt Resource System
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));

    // 8. Handle QML loading failure
    // objectCreated is emitted when the QML root object is created
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && objUrl == url) {
                QCoreApplication::exit(-1);
            }
        });

    // 9. Load QML file
    engine.load(url);

    // 10. Start Qt event loop
    return app.exec();
}
