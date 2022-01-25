#ifndef LASER_H
#define LASER_H

#include "bullet.h"
#include "enemy/enemy.h"

class Laser : public Bullet {
public:
    Laser(GameItem* parent, qreal atk);
    ~Laser();
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void advance(int phase) override;

protected:
    GameItem* parent;
    int counter;
};

#endif // LASER_H
