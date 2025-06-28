// Copyright 2022 Flying-Tom

#include <shop.h>

#include <statistic.h>

Shop::Shop(Game *game) {
  qDebug() << "Shop init";
  shopItems = {
      {"guntower", 1000, 30}, {"lasertower", 8000, 40},  {"repeller", 500, 50},
      {"bomb", 500, 3},       {"missiletower", 6000, 3}, {"sawtooth", 5000, 5},
      {"campfire", 2000, 20}, {"shield", 1000, 20},
  };
  for (int i = 0; i < shopItems.size(); ++i) {
    shopItemsMap[shopItems[i].name] = shopItems[i];
    orderMap[shopItems[i].name] = i;
  }
  qDebug() << "Shop fnish init";
}

ShopIcon::ShopIcon(Shop *shop, QString s, qreal left, qreal top, qreal width,
                   qreal height)
    : shop(shop), towername(s), aleft(left), atop(top), awidth(width),
      aheight(height) {
  counter = 0;
}

QRectF ShopIcon::boundingRect() const {
  return QRectF(aleft, atop, awidth, aheight);
}

void ShopIcon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)

  painter->drawImage(boundingRect(), QImage(":/images/" + towername + ".png"));
  QFont font;
  font.setPointSizeF(15);
  painter->setFont(font);
  painter->setPen(Qt::white);
  painter->drawText(
      QRectF(awidth + 5, aheight / 2 - 12, awidth, aheight),
      QString().asprintf("%3d", shop->shopItemsMap[towername].cost));

  QBrush brush(QColor(0, 0, 0, 200));
  painter->setBrush(brush);

  if (shop->shopItemsMap[towername].cost >
      qgraphicsitem_cast<Statistic *>(parentItem())->money.getCurValue()) {
    painter->drawRect(QRectF(0, 0, awidth, aheight));
  } else if (counter < shop->shopItemsMap[towername].cdtime) {
    painter->drawRect(QRectF(
        0, 0, awidth,
        aheight * (1 - qreal(counter) / shop->shopItemsMap[towername].cdtime)));
  }
}

void ShopIcon::advance(int phase) {
  if (!phase) {
    if (counter < shop->shopItemsMap[towername].cdtime)
      ++counter;
  } else {
    update();
  }
}

void ShopIcon::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  Q_UNUSED(event)

  if (shop->shopItemsMap[towername].cost >
      qgraphicsitem_cast<Statistic *>(parentItem())->money.getCurValue()) {
    event->setAccepted(false);
    return;
  }

  if (counter < shop->shopItemsMap[towername].cdtime)
    event->setAccepted(false);
  else
    counter = 0;
}

void ShopIcon::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
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

void ShopIcon::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
  Q_UNUSED(event)
}
