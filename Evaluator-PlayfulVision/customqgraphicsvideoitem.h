#ifndef CUSTOMQGRAPHICSVIDEOITEM_H
#define CUSTOMQGRAPHICSVIDEOITEM_H

#include <QGraphicsVideoItem>

class MainWindow;

class CustomQGraphicsVideoItem : public QGraphicsVideoItem{

    public:
        CustomQGraphicsVideoItem(MainWindow* parentWindow);

        void mousePressEvent(QGraphicsSceneMouseEvent *event);

    private:
        MainWindow* parentWindow;
};


#endif // CUSTOMQGRAPHICSVIDEOITEM_H

