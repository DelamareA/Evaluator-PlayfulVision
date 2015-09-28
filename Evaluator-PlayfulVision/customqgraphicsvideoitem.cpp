#include "mainwindow.h"

CustomQGraphicsVideoItem::CustomQGraphicsVideoItem(MainWindow* parentWindow) : QGraphicsVideoItem(){
    this->parentWindow = parentWindow;
}

void CustomQGraphicsVideoItem::mousePressEvent(QGraphicsSceneMouseEvent * event){
    parentWindow->mouseClick(event->pos().x(), event->pos().y());
}
