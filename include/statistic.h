#ifndef STATISTIC_H
#define STATISTIC_H

#include <common.h>

class Statistic : public QGraphicsObject {
    Q_OBJECT
public:
    Statistic(Game* game);
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void advance(int phase) override;

public:
    Game* game;
    GameValue<int> life;
    GameValue<int> money;
    GameValue<int> moneyAddCounter;
    int FPS;
    static int frameCount;
    QImage shopBackground;
    QImage lifeIcon;
    QImage coinIcon;
};

#endif // STATISTIC_H
