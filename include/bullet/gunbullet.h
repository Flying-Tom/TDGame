#ifndef GUNBULLET_H
#define GUNBULLET_H

#include "bullet.h"
#include "enemy/enemy.h"

class GunBullet : public Bullet {
public:
    GunBullet(qreal atk);
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void advance(int phase) override;
    void moveForward() override;
};

#endif // GUNBULLET_H
