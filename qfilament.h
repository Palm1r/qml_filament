#ifndef QFILAMENT_H
#define QFILAMENT_H

#include <QObject>

#include "qfilamentitem.h"
#include <memory>

//#include <filament/SwapChain.h>

class QQmlEngine;
class QQuickWindow;

//namespace QFilament {

class QFilament : public QObject
{
    Q_OBJECT
public:
    explicit QFilament(QQuickWindow *w, const QList<QFilamentItem *> items);

public slots:
    void init_example();
    void render_example();

private slots:
    void renderFrame();
    void shutdown();
    void init();

signals:
    void render(const std::vector<QFilamentItem *> &);
    void initialized();

private:
    QQuickWindow *m_window{nullptr};
    std::vector<QFilamentItem *> m_items;
};
//}

#endif // QFILAMENT_H
