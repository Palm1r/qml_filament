#include "qfilamentitem.h"

#include "qfilament.h"
#include "qsgfilamentnode.h"

QFilamentItem::QFilamentItem()
{
    setAcceptedMouseButtons(Qt::AllButtons);
    setFlag(QQuickItem::ItemAcceptsInputMethod);
    setFlag(QQuickItem::ItemHasContents);
}

QFilamentItem::~QFilamentItem()
{

}

void QFilamentItem::setViewId(uint16_t viewId)
{
    if (viewId == m_viewId)
        return;

    m_viewId = viewId;
    emit viewIdChanged();

    update();
}

void QFilamentItem::setBackgroundColor(QColor color)
{
    if (color == m_backgroundColor)
        return;

    m_backgroundColor = color;
    emit backgroundColorChanged();

    update();
}

QSGNode *QFilamentItem::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QSGFilamentNode *node = static_cast<QSGFilamentNode *>(oldNode);
    const auto size = boundingRect().size().toSize();
    if (/*!QFilament::isFilamentInit() ||*/ (!node && (size.width() <= 0 || size.height() <= 0)))
    {
        return node;
    }

    if (!node)
    {
        m_node = std::make_unique<QSGFilamentNode>(m_viewId, this);
    }

    if (m_node->rect().size().toSize() != size && !size.isEmpty())
    {
        m_node->setRect(boundingRect());
        m_node->sync();
        m_node->setTextureCoordinatesTransform(QSGSimpleTextureNode::NoTransform);
        m_node->setFiltering(QSGTexture::Linear);
        m_dprWidth = width() * window()->devicePixelRatio();
        m_dprHeight = height() * window()->devicePixelRatio();
    }
    update();

    return m_node.get();
}

void QFilamentItem::geometryChange(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickItem::geometryChange(newGeometry, oldGeometry);

    if (newGeometry.size() != oldGeometry.size())
        update();
}

void QFilamentItem::mouseMoveEvent(QMouseEvent *event)
{
    QQuickItem::mouseMoveEvent(event);
    m_mousePos = {event->position().toPoint().x(), event->position().toPoint().y()};
}

void QFilamentItem::mousePressEvent(QMouseEvent *event)
{
    if (!(event->button() & acceptedMouseButtons()))
    {
        QQuickItem::mousePressEvent(event);
        return;
    }
    m_mousePos = {event->position().toPoint().x(), event->position().toPoint().y()};
    event->setAccepted(true);
}

void QFilamentItem::mouseReleaseEvent(QMouseEvent *event)
{
    if (!(event->button() & acceptedMouseButtons()))
    {
        QQuickItem::mouseReleaseEvent(event);
        return;
    }
    m_mousePos = {event->position().toPoint().x(), event->position().toPoint().y()};
    event->setAccepted(true);
}

void QFilamentItem::invalidateSceneGraph()
{
    m_node->deleteLater();
    m_node.reset();
}

void QFilamentItem::releaseResources()
{
    m_node->deleteLater();
    m_node.reset();
}
