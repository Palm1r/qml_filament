#ifndef QSGFILAMENTNODE_H
#define QSGFILAMENTNODE_H

#include <QSGSimpleTextureNode>
#include <QtQuick/QSGTextureProvider>

#include <filament/RenderTarget.h>
#include <filament/Texture.h>
#include <filament/View.h>

class QSGFilamentNode : public QSGTextureProvider, public QSGSimpleTextureNode
{
    Q_OBJECT
public:
    QSGFilamentNode(const uint16_t viewId, QQuickItem *item, filament::Engine* engine);

    QSGTexture *texture() const override;
    void sync();

    filament::View* m_filaView;
private:
    QQuickItem *m_item;
    QQuickWindow *m_window;
    QSizeF m_size;
    qreal m_dpr;

    filament::Texture *tex_col;
    filament::Texture *tex_depth;
    filament::RenderTarget *render_target;
    filament::Engine* m_engine;

    uint16_t m_viewId{0};
    uint64_t m_frameCount{0};
    void *m_texture{nullptr};
};

#endif // QSGFILAMENTNODE_H
