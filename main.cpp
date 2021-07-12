#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>

#include "qfilamentitem.h"
#include "qfilament.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

#ifdef __APPLE__
    QQuickWindow::setGraphicsApi(QSGRendererInterface::MetalRhi);
#endif

#ifdef _WIN32
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);
#endif

#ifdef __linux__
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);
#endif

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:/main.qml"));
    view.show();

    const auto qfilament = QFilament(static_cast<QQuickWindow*>(&view), view.rootObject()->findChildren<QFilamentItem*>());

    return app.exec();
}
