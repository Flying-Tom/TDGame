#ifndef SHAMAN_H
#define SHAMAN_H

#include "enemy.h"

class Shaman : public Enemy {
public:
    Shaman(Game* game, QList<QPointF>& path);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QPainterPath shape() const override;
    void aquireTarget() override;
    void attack() override;
};

#endif // SHAMAN_H
