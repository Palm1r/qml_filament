#ifndef QSGFILAMENTNODE_H
#define QSGFILAMENTNODE_H

#include <QSGSimpleTextureNode>
#include <QtQuick/QSGTextureProvider>

class QSGFilamentNode : public QSGTextureProvider, public QSGSimpleTextureNode
{
    Q_OBJECT
public:
    QSGFilamentNode(const uint16_t viewId, QQuickItem *item);

    QSGTexture *texture() const override;
    void sync();

private:
    QQuickItem *m_item;
    QQuickWindow *m_window;
    QSizeF m_size;
    qreal m_dpr;

//    bgfx::FrameBufferHandle m_offscreenFB{bgfx::kInvalidHandle};
//    bgfx::TextureHandle m_backBuffer{bgfx::kInvalidHandle};
//    bgfx::TextureHandle m_depthBuffer{bgfx::kInvalidHandle};

    uint16_t m_viewId{0};
    uint64_t m_frameCount{0};
    void *m_texture{nullptr};
};

#endif // QSGFILAMENTNODE_H
