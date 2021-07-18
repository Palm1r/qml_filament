#ifndef QFILAMENTITEM_H
#define QFILAMENTITEM_H

#include <QQuickItem>
#include <filament/Engine.h>
#include <filament/View.h>

class QSGFilamentNode;

using MousePosition = std::array<int, 2>;

class QFilamentItem : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int viewId READ viewId WRITE setViewId NOTIFY viewIdChanged)

    QML_NAMED_ELEMENT(FilamentItem)
public:
    QFilamentItem();
    ~QFilamentItem();

    uint16_t viewId() const { return m_viewId; }
    void setViewId(uint16_t viewId);

    MousePosition mousePosition() { return m_mousePos; }

    uint16_t dprWidth() const { return m_dprWidth; }
    uint16_t dprHeight() const { return m_dprHeight; }

    void setFilEngine(filament::Engine *newFilEngine);

    void setFilView(filament::View *newFilView);

signals:
    void viewIdChanged();
    void backgroundColorChanged();

protected:
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;
    void geometryChange(const QRectF &newGeometry, const QRectF &oldGeometry) override;

private slots:
    void invalidateSceneGraph();

private:
    void releaseResources() override;

    std::unique_ptr<QSGFilamentNode> m_node;
    uint16_t m_viewId{0};
    QColor m_backgroundColor;
    MousePosition m_mousePos{0, 0};
    uint16_t m_dprWidth{0u};
    uint16_t m_dprHeight{0u};
    filament::Engine* m_filEngine;
    filament::View* m_filView;
};

#endif // QFILAMENTITEM_H
