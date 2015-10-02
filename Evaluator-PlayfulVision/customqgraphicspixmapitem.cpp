#include "mainwindow.h"

CustomQGraphicsPixmapItem::CustomQGraphicsPixmapItem(QPixmap& pixmap, Data* dataPointer, FrameData *frameData, MainWindow* mainWindow) : QGraphicsPixmapItem(pixmap){
    this->dataPointer = dataPointer;
    this->frameData = frameData;
    this->mainWindow = mainWindow;
}

QVariant CustomQGraphicsPixmapItem::itemChange(GraphicsItemChange change, const QVariant & value){
    if (change == ItemPositionChange){
        //qDebug() << this->pos().x() + IMAGE_POINTER_SIZE/2 << ";" << this->pos().y() + IMAGE_POINTER_SIZE/2;
        dataPointer->setX(this->pos().x() + IMAGE_POINTER_SIZE/2);
        dataPointer->setY(this->pos().y() + IMAGE_POINTER_SIZE/2);
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

void CustomQGraphicsPixmapItem::keyReleaseEvent(QKeyEvent * event){
    if (event->key() == Qt::Key_Delete){
        event->accept();

        mainWindow->removeFocusedPixmap(this);
        frameData->deleteData(dataPointer);
        delete this;
    }
    else {
        event->ignore();
    }
}
