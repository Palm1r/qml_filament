#include "qsgfilamentnode.h"

#include "qfilament.h"

QSGFilamentNode::QSGFilamentNode(const uint16_t viewId, QQuickItem *item)
{
    m_window = m_item->window();
    connect(m_window, &QQuickWindow::screenChanged, this, [this]() {
        if (m_window->effectiveDevicePixelRatio() != m_dpr)
            m_item->update();
    });
}

QSGTexture *QSGFilamentNode::texture() const
{
    return QSGSimpleTextureNode::texture();
}

void QSGFilamentNode::sync()
{

}
