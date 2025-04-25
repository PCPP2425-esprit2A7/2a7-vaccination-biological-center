#ifndef ANIMATEDBARITEM_H
#define ANIMATEDBARITEM_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QBrush>  // Ajout de cet include

class AnimatedBarItem : public QObject, public QGraphicsRectItem {
    Q_OBJECT
    Q_PROPERTY(qreal height READ height WRITE setHeight)
public:
    AnimatedBarItem(qreal x, qreal y, qreal width, const QColor &color, QGraphicsItem *parent = nullptr);
    qreal height() const;
    void setHeight(qreal height);

private:
    qreal m_yBase;
};

#endif // ANIMATEDBARITEM_H
