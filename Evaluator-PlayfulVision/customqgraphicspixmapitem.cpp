#include "customqgraphicspixmapitem.h"

CustomQGraphicsPixmapItem::CustomQGraphicsPixmapItem(QPixmap& pixmap, Data* dataPointer) : QGraphicsPixmapItem(pixmap){
    this->dataPointer = dataPointer;
}

QVariant CustomQGraphicsPixmapItem::itemChange(GraphicsItemChange change, const QVariant & value){
    if (change == ItemPositionChange){
        //qDebug() << this->pos().x() + IMAGE_POINTER_SIZE/2 << ";" << this->pos().y() + IMAGE_POINTER_SIZE/2;
        dataPointer->setX(this->pos().x() + IMAGE_POINTER_SIZE/2);
        dataPointer->setY(this->pos().y() + IMAGE_POINTER_SIZE/2);
    }
    return QGraphicsItem::itemChange(change, value);
}
