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
#include <QComboBox>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsProxyWidget>
#include <QPushButton>
#include <QMenuBar>
#include <QAction>
#include <QMenu>
#include <QCheckBox>
#include <QFileDialog>

#include <math.h>

#include "customqgraphicspixmapitem.h"
#include "customqgraphicsvideoitem.h"
#include "videodata.h"
#include "framedata.h"
#include "numberdata.h"
#include "colordata.h"
#include "constants.h"
#include "windowterminal.h"
#include "test_case.h"
#include "comparator_number.h"
#include "comparator_team.h"
class CustomQGraphicsPixmapItem;


// Main class for this program, all the interface is in there
class MainWindow : public QMainWindow{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

        void mouseClick(unsigned int x, unsigned int y);
        void removeFocusedPixmap(CustomQGraphicsPixmapItem* pixmap);
        void removePixmap(CustomQGraphicsPixmapItem* pixmap);
        void setFocusedPixmap(CustomQGraphicsPixmapItem* pixmap);
        void updateRectangles();

        void create_terminal();
        static void add_message_to_terminal(std::string msg);

        std::vector<TeamTestCase*> create_team_test_cases_from_data();
        std::vector<NumTestCase*> create_number_test_cases_from_data();

    private slots:
        void displayVideoError(QMediaPlayer::Error error);
        void slotMediaStatusChanged(QMediaPlayer::MediaStatus state);
        void slotdurationChanged(qint64 duration);
        void update();
        void slotNextFrame();

        void slotActionLoadNumTriggered(bool);
        void slotActionLoadColorTriggered(bool);
        void slotActionCompareNumTriggered(bool);
        void slotActionCompareColorTriggered(bool);

        void slotSpinInputValueChanged(int);
        void slotComboInputIndexChanged(int);
        void slotCheckInputStateChanged(int);

        void slotSaveAndExit();

    private:
        void setCorrectTimeAndFrame();
        void loadVideo();
        void createCustomPixmap(unsigned int x, unsigned int y);

        void compareNum();
        void compareColor();

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
        bool mode2;

        QLabel* labelVideoTime;
        QLabel* labelVideoFrame;

        QWidget* inputBar;
        QSpinBox* spinInputNumber;
        QComboBox* comboInputColorTeam;
        QCheckBox* checkInputColorTemplate;

        QPixmap* pointerPixmap;
        QPixmap* pointerPixmap2;
        CustomQGraphicsPixmapItem* focusedPixmap;
        QList<CustomQGraphicsPixmapItem*> currentPixmaps;

        static WindowTerminal* terminal;


        // _______________________________
        // DATA
        // _______________________________

        VideoData* videoData;

        // _______________________________
        // USER DATA
        // _______________________________
        unsigned int frameDuration; // in ms
        unsigned int currentFrame;

};


#endif // MAINWINDOW_H
