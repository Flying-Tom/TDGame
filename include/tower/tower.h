#ifndef TOWER_H
#define TOWER_H

#include <common.h>
#include <enemy/enemy.h>
#include <gameitem.h>
#include <tower/infopanel.h>

class Tower : public GameItem {
    Q_INTERFACES(QGraphicsItem)
public:
    enum towerAtkType {
        MELEE = 0,
        RANGE = 1,
    };
    Tower(Map* map,
        QString name = QString(),
        GameValue<qreal> HP = GameValue<qreal>(),
        int atkType = RANGE,
        qreal atkRadius = 0,
        GameValue<int> blockNumber = GameValue<int>(0, 3),
        GameValue<int> aquireCounter = GameValue<int>(0, 5));
    ~Tower();
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void advance(int phase) override;

public:
    enum { Type = UserType + 3 };
    int type() const override;

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

protected:
    Map* map;
    int atkType;
    QImage image;

public:
    InfoPanel infopanel;
    void aquireTarget() override;
    void attack() override;
    int getAtkType() const;
    QImage getImage() const;
};

#endif // TOWER_H
