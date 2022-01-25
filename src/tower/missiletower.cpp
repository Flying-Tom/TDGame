#include <tower/missiletower.h>

MissileTower::MissileTower(Map* map)
    : Tower(map,
        "missiletower",
        GameValue<qreal>(5, 5),
        RANGE,
        2048,
        GameValue<int>(0, 5),
        GameValue<int>(0, 175))
{
    image = QImage(":images/missiletower.png");
}

MissileTower::~MissileTower() { }

void MissileTower::aquireTarget()
{
    QList<QGraphicsItem*> colliding_items = atkArea->collidingItems();
    QList<QGraphicsItem*> enemy_list = QList<QGraphicsItem*>();

    foreach (QGraphicsItem* item, colliding_items) {
        if (item->type() == Enemy::Type and ((Enemy*)item)->getIsDead() == false) {
            enemy_list.append(item);
        }
    }

    if (enemy_list.empty()) {
        return;
    } else {
        int index = QRandomGenerator::global()->bounded(0, enemy_list.size());
        atkTarget = (Enemy*)enemy_list[index];
        attack();
    }
}

void MissileTower::attack()
{
    Missile* bullet = new Missile(atkTarget, 50);
    bullet->setPos(pos());
    scene()->addItem(bullet);
}
