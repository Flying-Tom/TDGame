#ifndef ROBOTSOLDIER_H
#define ROBOTSOLDIER_H

#include "enemy.h"

class RobotSoldier : public Enemy {
public:
    RobotSoldier(Game* game, QList<QPointF>& path);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void attack() override;

protected:
    qreal atkSpeed;
};

#endif // ROBOTSOLDIER_H
