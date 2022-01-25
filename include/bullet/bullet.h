#ifndef BULLET_H
#define BULLET_H

#include <common.h>
#include <enemy/enemy.h>
#include <map.h>

class Bullet : public QObject, public QGraphicsItem {
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    Bullet();
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void advance(int phase) override;
    enum { Type = UserType + 4 };
    int type() const override;
    virtual void moveForward();

protected:
    QImage image;
    qreal atk;
    qreal speed;
};

#endif // BULLET_H
