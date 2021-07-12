#ifndef QFILAMENT_H
#define QFILAMENT_H

#include <QObject>

#include "qfilamentitem.h"
#include <memory>

//#include <filament/SwapChain.h>
#include <filament/Engine.h>
#include <filament/Renderer.h>
#include <filament/SwapChain.h>
#include <filament/Scene.h>
#include <filament/View.h>
#include <filament/Viewport.h>
#include <filament/Camera.h>
#include <filament/TransformManager.h>
#include <filament/Texture.h>
#include <filament/RenderTarget.h>
#include <filameshio/MeshReader.h>
#include <filament/FilamentAPI.h>

class QQmlEngine;
class QQuickWindow;

//namespace QFilament {

//inline bool isFilamentInit()
//{
////    return bgfx::getInternalData()->context;
//}

//inline void frame()
//{
////    if (isFilamentInit())
////    {
////        bgfx::frame();
////    }
//}

class QFilament : public QObject
{
    Q_OBJECT
public:
    explicit QFilament(QQuickWindow *w, const QList<QFilamentItem *> items);

public slots:
    void init_example(/*const bgfx::Init &init*/);
    void render_example();

private slots:
    void renderFrame();
    void shutdown();
    void init();

signals:
    void render(const std::vector<QFilamentItem *> &);
    void initialized(/*bgfx::Init &*/);

private:
    QQuickWindow *m_window{nullptr};
    std::vector<QFilamentItem *> m_items;
//    std::unique_ptr<filament::SwapChain> m_swap_chain;

    filament::Engine* m_engine;
//    bgfx::Init m_bgfxInit;
//    ExampleCubes bgfxExample;
//    std::  <filament::SwapChain> m_swap_chain;
};
//}

#endif // QFILAMENT_H
