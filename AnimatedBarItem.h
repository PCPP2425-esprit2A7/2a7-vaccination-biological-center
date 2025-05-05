#ifndef ANIMATEDBARITEM_H
#define ANIMATEDBARITEM_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QPropertyAnimation>
#include <QBrush>
#include <QColor>
#include <QPen>

class AnimatedBarItem : public QObject, public QGraphicsRectItem {
    Q_OBJECT
    Q_PROPERTY(qreal barHeight READ barHeight WRITE setBarHeight)

public:
    AnimatedBarItem(qreal x, qreal y, qreal width, const QColor &color, QGraphicsItem *parent = nullptr)
        : QObject(), QGraphicsRectItem(x, y - 1, width, 1, parent) {
        setBrush(QBrush(color));
        setPen(QPen(Qt::NoPen));
        m_xPos = x;
        m_yPos = y;
        m_width = width;
    }

    qreal barHeight() const {
        return rect().height();
    }

    void setBarHeight(qreal height) {
        setRect(m_xPos, m_yPos - height, m_width, height);
    }

private:
    qreal m_xPos;
    qreal m_yPos;
    qreal m_width;
};

#endif // ANIMATEDBARITEM_H
