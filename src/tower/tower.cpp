// Copyright 2022 Flying-Tom

#include <tower/tower.h>

#include <enemy/enemy.h>

Tower::Tower(GameMap *map, QString name, GameValue<qreal> HP, int atkType,
             qreal atkRadius, GameValue<int> blockNumber,
             GameValue<int> aquireCounter)
    : map(map), atkType(atkType), infopanel(this) {
  GameItem::HP = HP;
  GameItem::atkRadius = atkRadius;
  GameItem::blockNumber = blockNumber;
  GameItem::aquireCounter = aquireCounter;
  GameItem::name = name;

  atkArea->setRect(-atkRadius, -atkRadius, atkRadius * 2, atkRadius * 2);
  HPMeter->setBrush(QBrush(QColor(QColor(0, 249, 0))));
}

Tower::~Tower() {
  if (map) {
    map->Destory(pos());
  }
}

void Tower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  GameItem::paint(painter, option, widget);
  if (underAtk == true) {
    painter->setOpacity(0.5);
    if (blinkCounter.getCurValue() > 0) {
      blinkCounter.changeCurValue(-1);
    } else {
      blinkCounter.setCurValue(blinkCounter.getMaxValue());
      underAtk = false;
    }
  } else {
    painter->setOpacity(1);
  }
  painter->drawImage(boundingRect(), image);
}

void Tower::advance(int phase) {
  if (!phase) {
    if (map) {
      if (HP.getCurValue() <= 0) {
        isDead = true;
        delete this;
        return;
      }
      if (aquireCounter.getCurValue() == aquireCounter.getMaxValue()) {
        aquireTarget();
        if (atkTarget.isNull() == false) {
          attack();
        }
        aquireCounter.setCurValue(0);
      } else {
        aquireCounter.changeCurValue(1);
      }
    }
  } else {
    update();
  }
}

void Tower::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
  Q_UNUSED(event);
  infopanel.setPos(pos());
  infopanel.show();
}

int Tower::type() const {
  if (map == nullptr)
    return Type + 114;
  return Type;
}

QImage Tower::getImage() const { return image; }

int Tower::getAtkType() const { return atkType; }

void Tower::aquireTarget() {
  for (QGraphicsItem *item : atkArea->collidingItems()) {
    Enemy *e = Enemy::castItem(item);
    if (e != nullptr && !e->getIsDead()) {
      atkTarget = e;
    }
  }
}

void Tower::attack() {}

Tower *Tower::castItem(QGraphicsItem *gi) {
  if (gi->type() == GameItemType::TOWER) {
    return qgraphicsitem_cast<Tower *>(gi);
  }
  return nullptr;
}