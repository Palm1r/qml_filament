#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>

#include "qfilament.h"
#include "qfilamentitem.h"

int main(int argc, char *argv[])
{
//    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

    QGuiApplication app(argc, argv);

#ifdef __APPLE__
    QQuickWindow::setGraphicsApi(QSGRendererInterface::MetalRhi);
#endif

#ifdef _WIN32
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGLRhi);
#endif

#ifdef __linux__
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);
#endif

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:/main.qml"));
    view.show();

    const auto qfilament = QFilament(static_cast<QQuickWindow *>(&view),
                                     view.rootObject()->findChildren<QFilamentItem *>());

    return app.exec();
}
