#include "qfilament.h"

#include <QQuickWindow>

//namespace QFilament {
//using namespace filament;

QFilament::QFilament(QQuickWindow *w, const QList<QFilamentItem *> items) : m_window(w)
{
    connect(m_window, &QQuickWindow::beforeFrameBegin, this, &QFilament::init, Qt::DirectConnection);
    connect(m_window, &QQuickWindow::beforeRenderPassRecording, this, &QFilament::renderFrame, Qt::DirectConnection);
    //Free standing function instead will always be called from the signal thread
//    connect(m_window, &QQuickWindow::afterRenderPassRecording, frame);

    //Connection to initialized signal allows to decouple the bgfx initialization from the qquick_bgfx::QBgfx wrapper
    QObject::connect(this, &QFilament::initialized, &QFilament::init_example);
    //Connection to render signal allows to decouple the rendering code from the qquick_bgfx::QBgfx wrapper
    QObject::connect(this, &QFilament::render, &QFilament::render_example);

    m_items.reserve(m_items.size());
    m_items.insert(m_items.end(), items.begin(), items.end());
}

void QFilament::init_example()
{
//    if (!QQuickBgfx::isBgfxInit())
//    {
//        bgfx::renderFrame();
//        bgfx::init(init);
//        bgfx::setViewClear(0, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f, 0);

//        //        bgfx::setDebug(BGFX_DEBUG_TEXT);
//        ddInit();
//        bgfxExample.init();
//    }
}

void QFilament::render_example()
{
    for(const auto item : m_items)
    {
        if (item->viewId() < 256)
        {
            const auto w = item->dprWidth();
            const auto h = item->dprHeight();

//            bgfxExample.setSize(w, h);
//            bgfxExample.update();

            //            float r{0.0f};
            //            float g{0.0f};
            //            float b{0.0f};
            //            auto c = item->backgroundColor();
            //            c.setHslF(c.hueF(), c.saturationF(), c.lightnessF() * std::clamp(item->mousePosition()[1] / (float)item->height(), 0.0f, 1.0f));
            //            c.getRgbF(&r, &g, &b);

            //            const uint32_t color = uint8_t(r * 255) << 24 | uint8_t(g * 255) << 16 | uint8_t(b * 255) << 8 | 255;

            //            bgfx::setViewRect(item->viewId(), 0, 0, uint16_t(w), uint16_t(h) );
            //            bgfx::touch(item->viewId());


            //            bgfx::frame();
        }
    }
}

void QFilament::renderFrame()
{
//    if (!QQuickBgfx::isBgfxInit())
//        return;

    m_window->beginExternalCommands();
    emit render(m_items);
    m_window->endExternalCommands();
}

void QFilament::shutdown()
{
//    if (QQuickBgfx::isBgfxInit())
//    {
//        bgfx::shutdown();
//    }
    m_items.clear();
}

void QFilament::init()
{
    using namespace filament;

    QSGRendererInterface *rif = m_window->rendererInterface();
    const auto dpr = m_window->effectiveDevicePixelRatio();
    auto winHandle = reinterpret_cast<void *>(m_window->winId());
    auto context = static_cast<void *>(rif->getResource(m_window, QSGRendererInterface::DeviceResource));

    m_engine = Engine::create(filament::backend::Backend::OPENGL,nullptr, context);

//    if (!fila_engine) {
//        qDebug() << "fila engine null";
//    }
}

//}


