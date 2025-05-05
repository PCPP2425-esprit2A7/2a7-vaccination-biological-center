#include "animatedbaritem.h"
#include <QPen>


AnimatedBarItem::AnimatedBarItem(qreal x, qreal y, qreal width, const QColor &color, QGraphicsItem *parent)
    : QObject(), QGraphicsRectItem(parent), m_yBase(y) {
    setRect(x, y, width, 0);
    setBrush(QBrush(color));
    setPen(QPen(Qt::black));
}

qreal AnimatedBarItem::height() const {
    return rect().height();
}

void AnimatedBarItem::setHeight(qreal height) {
    QRectF r = rect();
    r.setHeight(height);
    r.moveTop(m_yBase - height);
    setRect(r);
}
