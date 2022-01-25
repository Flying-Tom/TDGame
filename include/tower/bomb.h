#ifndef BOMB_H
#define BOMB_H

#include "tower.h"

class Bomb : public Tower {
public:
    Bomb(Map* map);
    ~Bomb();
    void advance(int phase) override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void bombing();

protected:
    QMovie movie;
};

#endif // BOMB_H
