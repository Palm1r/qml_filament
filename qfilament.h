#ifndef QFILAMENT_H
#define QFILAMENT_H

#include <QObject>

#include "qfilamentitem.h"
#include <memory>

#include <filament/Camera.h>
#include <filament/Engine.h>
#include <filament/Renderer.h>
#include <filament/Scene.h>
#include <filament/SwapChain.h>
#include <filament/View.h>

class QQmlEngine;
class QQuickWindow;

// namespace QFilament {
//inline void frame(filament::Engine *engine, filament::Renderer *renderer, filament::SwapChain *swapChain)
//{
//    if (engine)
//    {
//        if (renderer->beginFrame(swapChain)) {
//            renderer->render(m_view);
//            renderer->endFrame();
//        }
//    }
//}

class QFilament : public QObject
{
    Q_OBJECT
public:
    explicit QFilament(QQuickWindow *w, const QList<QFilamentItem *> items);

public slots:
    void init_example();
    void render_example();
//    inline void frame();

private slots:
    void renderFrame();
    void shutdown();
    void init();

signals:
    void render();
    void initialized();

private:
    QQuickWindow *m_window{nullptr};
    std::vector<QFilamentItem *> m_items;

    filament::Engine *m_engine;
    filament::SwapChain *m_swapChain;
    filament::Renderer *m_renderer;

    filament::Camera *m_camera;
    filament::View *m_view;
    filament::Scene *m_scene;
};
//}

#endif // QFILAMENT_H
