#include "qfilament.h"

#include <QQuickWindow>

#include <filament/Viewport.h>
#include <utils/EntityManager.h>
#include <QOpenGLContext>

using namespace QNativeInterface;

//#include <QNativeInterFace
//#include <QPlatformHeadrt
//#include <QWGLNativeContext>


// namespace QFilament {
// using namespace filament;

QFilament::QFilament(QQuickWindow *w, const QList<QFilamentItem *> items)
    : m_window(w)
{
    connect(m_window, &QQuickWindow::beforeFrameBegin, this, &QFilament::init, Qt::DirectConnection);
    connect(m_window,
            &QQuickWindow::beforeRenderPassRecording,
            this,
            &QFilament::renderFrame,
            Qt::DirectConnection);
    // Free standing function instead will always be called from the signal thread
    connect(m_window, &QQuickWindow::afterRenderPassRecording, [this](){
        if (m_renderer->beginFrame(m_swapChain)) {
            m_renderer->render(m_view);
            m_renderer->endFrame();
        }
    });

    QObject::connect(this, &QFilament::initialized, &QFilament::init_example);
    QObject::connect(this, &QFilament::render, &QFilament::render_example);

    m_items.reserve(m_items.size());
    m_items.insert(m_items.end(), items.begin(), items.end());
}

void QFilament::init_example()
{
//    qDebug() << "init example";
//    m_renderer->setClearOptions({
//        .clearColor = { 0.0f, 0.13f, 0.0f, 1.0f },
//        .clear = true
//    });

    m_renderer->setClearOptions({{ 1.0f, 0.13f, 0.0f, 1.0f}, true, true});

//    if (m_renderer->beginFrame(m_swapChain)) {
//        m_renderer->render(m_view);
//        m_renderer->endFrame();
//    }

//    if (m_renderer->beginFrame(m_swapChain)) {
//        m_renderer->render(m_view);
//        m_renderer->endFrame();
//    }
    //    m_view->setClearColor({0.1f, 0.125f, 0.25f, 1.0f});
    //    m_view->setPostProcessingEnabled(false);
    //    m_view->setDepthPrepass(fl::View::DepthPrepass::DISABLED);
    //    if (!QQuickBgfx::isBgfxInit())
    //    {
    //        bgfx::renderFrame();
    //        bgfx::init(init);
    //        bgfx::setViewClear(0, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH,
    //        0x303030ff, 1.0f, 0);

    //        //        bgfx::setDebug(BGFX_DEBUG_TEXT);
    //        ddInit();
    //        bgfxExample.init();
    //    }

    //    if (m_renderer->beginFrame(m_swapChain))
    //    {
    //        m_renderer->render(m_view);
    //        m_renderer->endFrame();
    //    }
}

void QFilament::render_example()
{
//    qDebug() << "render example";
    for (const auto item : m_items) {
        if (item->viewId() < 256) {
            const auto w = item->dprWidth();
            const auto h = item->dprHeight();

            m_renderer->setClearOptions({{ 1.0f, 0.13f, 0.0f, 1.0f}, true});

//            if (m_renderer->beginFrame(m_swapChain)) {
//                m_renderer->render(m_view);
//                m_renderer->endFrame();
//            }

            if (m_renderer->beginFrame(m_swapChain)) {
                m_renderer->render(m_view);
                m_renderer->endFrame();
            }
        }
    }
}

//void QFilament::frame()
//{
//    if (m_engine && m_renderer->beginFrame(m_swapChain)) {
//        m_renderer->render(m_view);
//        m_renderer->endFrame();
//    }
//}

void QFilament::renderFrame()
{
    m_window->beginExternalCommands();
    emit render();
    m_window->endExternalCommands();
}

void QFilament::shutdown()
{
    m_items.clear();
}

void QFilament::init()
{
    //    using namespace filament;

//    qDebug() << "init";

    QSGRendererInterface *rif = m_window->rendererInterface();
    const auto dpr = m_window->effectiveDevicePixelRatio();
    auto winHandle = reinterpret_cast<void *>(m_window->winId());

    auto current = QOpenGLContext::currentContext();
    current->doneCurrent();

    auto ctx = new QOpenGLContext();
    ctx->create();

//    auto *wglContext = ctx->nativeInterface<QWGLContext>();
//    auto main_opengl_context = QWGLContext::fromNative(wglContext->nativeContext(), (HWND)m_window->winId());

//    qDebug() << "create engine";

//    if (!wglContext) {
//        qDebug() << "shared context is null";
//    }
#ifdef _WIN32
    m_engine = filament::Engine::create(filament::backend::Backend::OPENGL, nullptr, wglContext->nativeContext());

    if (!m_engine) {
        qDebug() << "fila engine null";
    }

   auto native_window = (void*)((HWND)m_window->winId());

   if (!native_window) {
       qDebug() <<"native window is null";
   }

//    m_engine->createSwapChain(winHandle);
   m_swapChain = m_engine->createSwapChain(400,400, 0);

   if (!m_swapChain) {
       qDebug() <<"m_swapChain is null";
   }

    m_renderer = m_engine->createRenderer();
#endif

#ifdef __linux__
    auto m_engine = filament::Engine::create(filament::backend::Backend::OPENGL, nullptr, ctx);
    filament::SwapChain *swapChain = m_engine->createSwapChain(winHandle);
    filament::Renderer *renderer = m_engine->createRenderer();
#endif

#ifdef __APPLE__
    init.type = bgfx::RendererType::Metal;
    init.platformData.nwh = reinterpret_cast<CAMetalLayer *>(
        reinterpret_cast<NSView *>(windowHandler).layer);
    init.platformData.context = static_cast<id<MTLDevice>>(context);

    auto m_engine = filament::Engine::create(filament::backend::Backend::Metal, nullptr, context);
    filament::SwapChain *swapChain = m_engine->createSwapChain(
        reinterpret_cast<CAMetalLayer *>(reinterpret_cast<NSView *>(windowHandler).layer));
    filament::Renderer *renderer = m_engine->createRenderer();
#endif


    m_camera = m_engine->createCamera(utils::EntityManager::get().create());
    m_view = m_engine->createView();
    m_scene = m_engine->createScene();

    m_view->setViewport(
        {0, 0, static_cast<uint32_t>(400), static_cast<uint32_t>(400)});
    m_view->setCamera(m_camera);
    m_view->setScene(m_scene);
    m_view->setName("main-view");

    m_renderer->setClearOptions({{ 1.0f, 0.13f, 0.0f, 1.0f}, true});

    for (auto item : m_items) {
        item->setFilEngine(m_engine);
        item->setFilView(m_view);
    }

    //    // Set up the render view point
    //    setup_camera();

    emit initialized();
}

//}
