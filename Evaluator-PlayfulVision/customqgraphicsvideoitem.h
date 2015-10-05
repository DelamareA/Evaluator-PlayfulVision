#ifndef CUSTOMQGRAPHICSVIDEOITEM_H
#define CUSTOMQGRAPHICSVIDEOITEM_H

#include <QGraphicsVideoItem>

class MainWindow;

// Class used for generating actions when the user clicks on the video
class CustomQGraphicsVideoItem : public QGraphicsVideoItem{

    public:
        CustomQGraphicsVideoItem(MainWindow* parentWindow);

        void mousePressEvent(QGraphicsSceneMouseEvent *event);

    private:
        MainWindow* parentWindow;
};


#endif // CUSTOMQGRAPHICSVIDEOITEM_H

