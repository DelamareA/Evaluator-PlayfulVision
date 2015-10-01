#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsVideoItem>
#include <QLabel>
#include <QSpinBox>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsProxyWidget>
#include <QPushButton>
#include <QMenuBar>
#include <QAction>
#include <QMenu>
#include <QFileDialog>

#include "customqgraphicspixmapitem.h"
#include "customqgraphicsvideoitem.h"
#include "numberdata.h"
#include "constants.h"

class MainWindow : public QMainWindow{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

        void mouseClick(unsigned int x, unsigned int y);

    private slots:
        void displayVideoError(QMediaPlayer::Error error);
        void slotMediaStatusChanged(QMediaPlayer::MediaStatus state);
        void update();
        void slotNextFrame();

        void slotActionLoadNumTriggered(bool);
        void slotActionLoadColorTriggered(bool);

    private:
        void setCorrectTimeAndFrame();
        void loadVideo();

    private:
        // _______________________________
        // VIDEO
        // _______________________________
        QMediaPlayer* player;
        QGraphicsView* graphicsView;
        QGraphicsVideoItem *videoItem;

        // _______________________________
        // INTERFACE
        // _______________________________
        Mode mode;

        QLabel* labelVideoTime;
        QLabel* labelVideoFrame;

        QPixmap* pointerPixmap;


        // _______________________________
        // DATA
        // _______________________________

        // _______________________________
        // USER DATA
        // _______________________________
        unsigned int frameDuration; // in ms
        unsigned int currentFrame;

};


#endif // MAINWINDOW_H
