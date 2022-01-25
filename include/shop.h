#ifndef SHOP_H
#define SHOP_H

#include <common.h>

class Shop : public QGraphicsItem {
public:
    int counter;

    qreal aleft, atop, awidth, aheight;

    QString towername;
    Shop(QString s, qreal left, qreal top, qreal width, qreal height);
    const static QMap<QString, int> map;
    const static QVector<QString> name;
    const static QVector<int> cost;
    const static QVector<int> cdtime;
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void advance(int phase) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // SHOP_H
