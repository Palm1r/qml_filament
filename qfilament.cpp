#include "qfilament.h"

#include <QQuickWindow>

#include <filament/Engine.h>
//namespace QFilament {
//using namespace filament;

QFilament::QFilament(QQuickWindow *w, const QList<QFilamentItem *> items) : m_window(w)
{
    connect(m_window, &QQuickWindow::beforeFrameBegin, this, &QFilament::init, Qt::DirectConnection);
    connect(m_window, &QQuickWindow::beforeRenderPassRecording, this, &QFilament::renderFrame, Qt::DirectConnection);
    //Free standing function instead will always be called from the signal thread
//    connect(m_window, &QQuickWindow::afterRenderPassRecording, frame);

    QObject::connect(this, &QFilament::initialized, &QFilament::init_example);
    QObject::connect(this, &QFilament::render, &QFilament::render_example);

    m_items.reserve(m_items.size());
    m_items.insert(m_items.end(), items.begin(), items.end());
}

void QFilament::init_example()
{
}

void QFilament::render_example()
{
    for(const auto item : m_items)
    {
        if (item->viewId() < 256)
        {
            const auto w = item->dprWidth();
            const auto h = item->dprHeight();
        }
    }
}

void QFilament::renderFrame()
{
    m_window->beginExternalCommands();
    emit render(m_items);
    m_window->endExternalCommands();
}

void QFilament::shutdown()
{
    m_items.clear();
}

void QFilament::init()
{
//    using namespace filament;

    QSGRendererInterface *rif = m_window->rendererInterface();
    const auto dpr = m_window->effectiveDevicePixelRatio();
    auto winHandle = reinterpret_cast<void *>(m_window->winId());
    auto context = static_cast<void *>(rif->getResource(m_window, QSGRendererInterface::DeviceResource));

    auto m_engine = filament::Engine::create();

//    if (!fila_engine) {
//        qDebug() << "fila engine null";
//    }
}

//}


