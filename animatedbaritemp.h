#ifndef ANIMATEDBARITEM_H
#define ANIMATEDBARITEM_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QColor>

class AnimatedBarItemp : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit AnimatedBarItemp(qreal x, qreal y, qreal width, const QColor &color, QGraphicsItem *parent = nullptr);
    qreal height() const;
    void setHeight(qreal height);

private:
    qreal m_yBase;
};

#endif // ANIMATEDBARITEM_H
