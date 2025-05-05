#include "animatedbaritemp.h"
#include <QPen>
#include <QBrush>

AnimatedBarItemp::AnimatedBarItemp(qreal x, qreal y, qreal width, const QColor &color, QGraphicsItem *parent)
    : QObject(nullptr),  // QObject parent doit être nullptr ou un QObject*
    QGraphicsRectItem(parent),  // QGraphicsItem parent
    m_yBase(y)
{
    setRect(x, y, width, 0);
    setBrush(QBrush(color));
    setPen(QPen(Qt::black));
}

qreal AnimatedBarItemp::height() const
{
    return rect().height();
}

void AnimatedBarItemp::setHeight(qreal height)
{
    QRectF r = rect();
    r.setHeight(height);
    r.moveTop(m_yBase - height);
    setRect(r);
}
