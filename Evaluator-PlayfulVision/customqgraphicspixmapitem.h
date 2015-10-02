#ifndef CUSTOMQGRAPHICSPIXMAPITEM_H
#define CUSTOMQGRAPHICSPIXMAPITEM_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QDebug>

#include "constants.h"

#include "data.h"
#include "framedata.h"

class CustomQGraphicsPixmapItem : public QGraphicsPixmapItem{

    public:
        CustomQGraphicsPixmapItem(QPixmap& pixmap, Data* dataPointer, FrameData* frameData);
        QVariant itemChange(GraphicsItemChange change, const QVariant & value);

        void changePointers(Data* dataPointer, FrameData* frameData);
        Data* getDataPointer();

    protected :
        void keyReleaseEvent(QKeyEvent * event);

    private:
        Data* dataPointer;
        FrameData* frameData;
};

#endif // CUSTOMQGRAPHICSPIXMAPITEM_H
