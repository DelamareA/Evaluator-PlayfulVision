#ifndef CUSTOMQGRAPHICSPIXMAPITEM_H
#define CUSTOMQGRAPHICSPIXMAPITEM_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QDebug>

#include "constants.h"

#include "data.h"
#include "framedata.h"

class MainWindow;


/* This class is used to represent the image that appears when the user clicks on the window
 *
*/
class CustomQGraphicsPixmapItem : public QGraphicsPixmapItem{

    public:
        CustomQGraphicsPixmapItem(QPixmap& pixmap, Data* dataPointer, FrameData* frameData, MainWindow *mainWindow, CustomQGraphicsPixmapItem *brother);
        QVariant itemChange(GraphicsItemChange change, const QVariant & value);

        void changePointers(Data* dataPointer, FrameData* frameData);
        Data* getDataPointer();
        void setBrother(CustomQGraphicsPixmapItem* newBrother);
        CustomQGraphicsPixmapItem* getBrother();
        QRectF getRect();
        void updateRectangle();
        bool isOldest();
        void setVisible2(bool);

    protected :
        void keyReleaseEvent(QKeyEvent * event);

    private:
        CustomQGraphicsPixmapItem* brother; // used only for colors, represents the pointer on the other side of the rectangle
        Data* dataPointer; // the data the image is linked to
        FrameData* frameData; // the frame of this image
        MainWindow* mainWindow;
        QGraphicsRectItem* rectItem; // the red rectangle
        bool oldest; // indicates if the image is the first one for this rectangle
};

#endif // CUSTOMQGRAPHICSPIXMAPITEM_H

