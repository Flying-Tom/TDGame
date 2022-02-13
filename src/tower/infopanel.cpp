// Copyright 2022 Flying-Tom

#include <tower/infopanel.h>

InfoPanel::InfoPanel(GameItem* parent) : parent(parent) { return; }

InfoPanel::~InfoPanel() {}

QRectF InfoPanel::boundingRect() const { return QRectF(0, 0, 150, 150); }

void InfoPanel::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                      QWidget* widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)

  painter->setBrush(QBrush(QColor(96, 96, 96, 120)));
  painter->drawRect(boundingRect());
  painter->drawImage(QRect(10, 100, 30, 30), QImage(":/images/cross.png"));

  QFont font;
  font.setPointSizeF(10);
  painter->setFont(font);
  painter->setPen(Qt::white);
  painter->drawText(QRect(40, 10, 130, 30), QString("Info Panel"));
  painter->drawText(QRect(10, 35, 130, 30),
                    QString("Name:") + parent->getName());
  painter->drawText(QRect(10, 55, 100, 30),
                    QString("HP:") + QString::number(parent->HP.getCurValue()));
  painter->drawText(QRect(50, 105, 80, 30), QString("Destroy it"));
}

void InfoPanel::advance(int phase) {
  if (!phase) {
    return;
  }
}

void InfoPanel::mousePressEvent(QGraphicsSceneMouseEvent* event) {
  if (event->button() == Qt::RightButton) {
    hide();
    return;
  } else if (event->button() == Qt::LeftButton) {
    if (QRectF(50, 105, 80, 30).contains(event->pos())) {
      delete parent;
      return;
    }
  }
  event->ignore();
}
