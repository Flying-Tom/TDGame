// Copyright 2022 Flying-Tom

#include <tower/shield.h>

Shield::Shield(GameMap* map)
    : Tower(map, "shield", GameValue<qreal>(100, 100), RANGE, 200,
            GameValue<int>(0, 5), GameValue<int>(0, 175)) {
  image = QImage(":images/shield.png");
  HPMeter->setBrush(QBrush(Qt::yellow));
  setZValue(5);
}

Shield::~Shield() {}

void Shield::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                   QWidget* widget) {
  Tower::paint(painter, option, widget);
  painter->setBrush(QColor(0, 204, 255));
  painter->setOpacity(0.1);
  painter->drawEllipse(atkArea->boundingRect());
  // atkArea->show();
}

void Shield::advance(int phase) {
  if (!phase) {
    if (HP.getCurValue() == 0) {
      delete this;
      return;
    }

    for (QGraphicsItem* item : atkArea->collidingItems()) {
      if (item->type() == Tower::Type &&
          qgraphicsitem_cast<Tower*>(item)->getAtkType() == Tower::RANGE &&
          item != this) {
        if (qgraphicsitem_cast<Tower*>(item)->getName() != "shield" &&
            qgraphicsitem_cast<Tower*>(item)->HP.getCurValue() > 0) {
          double delta = qgraphicsitem_cast<Tower*>(item)->HP.getMaxValue() -
                         qgraphicsitem_cast<Tower*>(item)->HP.getCurValue();
          qgraphicsitem_cast<Tower*>(item)->HP.changeCurValue(delta);
          HP.changeCurValue(-delta);
        }
      }
    }
  }
}
