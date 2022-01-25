#ifndef MISSILE_H
#define MISSILE_H

#include "bullet.h"

class Missile : public Bullet {
public:
    Missile(QPointer<GameItem> atkTarget, qreal atk);
    ~Missile();
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void advance(int phase) override;
    void moveForward() override;
    void bombing();

private:
    QPointer<GameItem> atkTarget;
    qreal atkAngle;

    QGraphicsEllipseItem* bombArea;
    bool isBombing;
    qreal bombRadius;
    QMovie movie;
};

#endif // MISSILE_H
