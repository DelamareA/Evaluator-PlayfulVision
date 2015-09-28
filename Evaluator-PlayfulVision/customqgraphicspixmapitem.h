#ifndef CUSTOMQGRAPHICSPIXMAPITEM_H
#define CUSTOMQGRAPHICSPIXMAPITEM_H

#include <QGraphicsPixmapItem>
#include <QDebug>

#include "constants.h"

#include "data.h"

class CustomQGraphicsPixmapItem : public QGraphicsPixmapItem{

    public:
        CustomQGraphicsPixmapItem(QPixmap& pixmap, Data* dataPointer);
        QVariant itemChange(GraphicsItemChange change, const QVariant & value);

    private:
        Data* dataPointer;
};

#endif // CUSTOMQGRAPHICSPIXMAPITEM_H
