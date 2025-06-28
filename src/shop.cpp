// Copyright 2022 Flying-Tom

#include <shop.h>
#include <statistic.h>

const QMap<QString, int> Shop::map = {
    {"guntower", 0},     {"lasertower", 1}, {"repeller", 2}, {"bomb", 3},
    {"missiletower", 4}, {"sawtooth", 5},   {"campfire", 6}, {"shield", 7},
};
const QVector<QString> Shop::name = {
    "guntower",     "lasertower", "repeller", "bomb",
    "missiletower", "sawtooth",   "campfire", "shield",
};
const QVector<int> Shop::cost = {1000, 2000, 500, 500, 5000, 5000, 2000, 1000};
const QVector<int> Shop::cdtime = {30, 40, 50, 3, 3, 5, 20, 20};

Shop::Shop(QString s, qreal left, qreal top, qreal width, qreal height) {
  towername = s;
  counter = 0;

  aleft = left;
  atop = top;
  awidth = width;
  aheight = height;
}

QRectF Shop::boundingRect() const {
  return QRectF(aleft, atop, awidth, aheight);
}

void Shop::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                 QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)

  painter->drawImage(boundingRect(), QImage(":/images/" + towername + ".png"));
  QFont font;
  font.setPointSizeF(15);
  painter->setFont(font);
  painter->setPen(Qt::white);
  painter->drawText(QRectF(awidth + 5, aheight / 2 - 12, awidth, aheight),
                    QString().asprintf("%3d", cost[map[towername]]));

  QBrush brush(QColor(0, 0, 0, 200));
  painter->setBrush(brush);

  if (Shop::cost[Shop::map[towername]] >
      qgraphicsitem_cast<Statistic *>(parentItem())->money.getCurValue()) {
    painter->drawRect(QRectF(0, 0, awidth, aheight));
  } else if (counter < cdtime[map[towername]]) {
    painter->drawRect(QRectF(
        0, 0, awidth, aheight * (1 - qreal(counter) / cdtime[map[towername]])));
  }
}

void Shop::advance(int phase) {
  if (!phase) {
    if (counter < cdtime[map[towername]])
      ++counter;
  } else {
    update();
  }
}

void Shop::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  Q_UNUSED(event)

  if (cost[map[towername]] >
      qgraphicsitem_cast<Statistic *>(parentItem())->money.getCurValue()) {
    event->setAccepted(false);
    return;
  }

  if (counter < cdtime[map[towername]])
    event->setAccepted(false);
  else
    counter = 0;
}

void Shop::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
          .length() < QApplication::startDragDistance())
    return;

  QDrag *drag = new QDrag(event->widget());
  QMimeData *mime = new QMimeData();
  mime->setText(towername);
  drag->setMimeData(mime);
  drag->setPixmap(
      QPixmap(":/images/" + towername + ".png").scaled(awidth, aheight));
  drag->setHotSpot(QPoint(35, 35));
  drag->exec();
}

void Shop::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
  Q_UNUSED(event)
}
