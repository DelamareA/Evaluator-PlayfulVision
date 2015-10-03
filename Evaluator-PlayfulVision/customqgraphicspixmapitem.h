#ifndef CUSTOMQGRAPHICSPIXMAPITEM_H
#define CUSTOMQGRAPHICSPIXMAPITEM_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QDebug>

#include "constants.h"

#include "data.h"
#include "framedata.h"

class MainWindow;

class CustomQGraphicsPixmapItem : public QGraphicsPixmapItem{

    public:
        CustomQGraphicsPixmapItem(QPixmap& pixmap, Data* dataPointer, FrameData* frameData, MainWindow *mainWindow, CustomQGraphicsPixmapItem *brother);
        QVariant itemChange(GraphicsItemChange change, const QVariant & value);

        void changePointers(Data* dataPointer, FrameData* frameData);
        Data* getDataPointer();
        void setBrother(CustomQGraphicsPixmapItem* newBrother);
        CustomQGraphicsPixmapItem* getBrother();
        void updateRectangle();

    protected :
        void keyReleaseEvent(QKeyEvent * event);

    private:
        CustomQGraphicsPixmapItem* brother;
        Data* dataPointer;
        FrameData* frameData;
        MainWindow* mainWindow;
        QGraphicsRectItem* rectItem;
};

#endif // CUSTOMQGRAPHICSPIXMAPITEM_H

