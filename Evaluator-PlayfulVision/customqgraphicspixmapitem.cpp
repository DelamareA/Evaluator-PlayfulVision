#include "mainwindow.h"

CustomQGraphicsPixmapItem::CustomQGraphicsPixmapItem(QPixmap& pixmap, Data* dataPointer, FrameData *frameData, MainWindow* mainWindow, CustomQGraphicsPixmapItem* brother) : QGraphicsPixmapItem(pixmap){
    this->dataPointer = dataPointer;
    this->frameData = frameData;
    this->mainWindow = mainWindow;
    this->brother = brother;
    this->rectItem = new QGraphicsRectItem();
    rectItem->setVisible(false);

    oldest = (brother == 0);
}

QVariant CustomQGraphicsPixmapItem::itemChange(GraphicsItemChange change, const QVariant & value){
    if (change == ItemPositionChange){
        //qDebug() << this->pos().x() + IMAGE_POINTER_SIZE/2 << ";" << this->pos().y() + IMAGE_POINTER_SIZE/2;
        dataPointer->setX(this->pos().x() + IMAGE_POINTER_SIZE/2);
        dataPointer->setY(this->pos().y() + IMAGE_POINTER_SIZE/2);

        mainWindow->updateRectangles();
    }
    else if (change == ItemSelectedChange){
        if (this->isSelected()){
            mainWindow->removeFocusedPixmap(this);
        }
        else {
            mainWindow->setFocusedPixmap(this);
        }
    }
    return QGraphicsItem::itemChange(change, value);
}

void CustomQGraphicsPixmapItem::changePointers(Data* dataPointer, FrameData *frameData){
    this->dataPointer = dataPointer;
    this->frameData = frameData;
}

Data* CustomQGraphicsPixmapItem::getDataPointer(){
    return dataPointer;
}

void CustomQGraphicsPixmapItem::setBrother(CustomQGraphicsPixmapItem* newBrother){
    this->brother = newBrother;
}

CustomQGraphicsPixmapItem* CustomQGraphicsPixmapItem::getBrother(){
    return this->brother;
}

void CustomQGraphicsPixmapItem::updateRectangle(){
    if (oldest){
        if (!this->rectItem->isVisible()){
            this->scene()->addItem(this->rectItem);
            this->rectItem->setVisible(true);
            this->rectItem->setPen(QPen(QColor(255, 0, 0)));
        }

        int x = 0;
        int y = 0;
        int width = 0;
        int height = 0;
        if (brother != 0){
            x = std::min(this->pos().x() + IMAGE_POINTER_SIZE/2, brother->pos().x() + IMAGE_POINTER_SIZE/2);
            y = std::min(this->pos().y() + IMAGE_POINTER_SIZE/2, brother->pos().y() + IMAGE_POINTER_SIZE/2);
            width = abs(brother->pos().x() - this->pos().x());
            height = abs(brother->pos().y() - this->pos().y());
        }
        rectItem->setRect(x, y, width, height);
    }
}

bool CustomQGraphicsPixmapItem::isOldest(){
    return oldest;
}

QRectF CustomQGraphicsPixmapItem::getRect(){
    return rectItem->rect();
}

void CustomQGraphicsPixmapItem::setVisible2(bool b){
    this->setVisible(b);
    this->rectItem->setVisible(b);
}

void CustomQGraphicsPixmapItem::keyReleaseEvent(QKeyEvent * event){
    if (event->key() == Qt::Key_Delete){
        event->accept();

        mainWindow->removeFocusedPixmap(this);
        mainWindow->removePixmap(this);
        frameData->deleteData(dataPointer);
        delete rectItem;

        if (brother != 0){
            brother->mainWindow->removeFocusedPixmap(brother);
            mainWindow->removePixmap(brother);
            delete brother->rectItem;
            delete brother;
        }

        delete this;
    }
    else {
        event->ignore();
    }
}
