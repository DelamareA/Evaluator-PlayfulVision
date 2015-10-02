#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Redstone");

    QWidget *centralZone = new QWidget(this);
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    setCentralWidget(centralZone);
    centralZone->setLayout(layoutPrincipal);

    QMenu *newDataMenu = menuBar()->addMenu("&New data");

    QAction *actionLoadNum = new QAction("Load video (&Number)", this);
    newDataMenu->addAction(actionLoadNum);
    connect(actionLoadNum, SIGNAL(triggered(bool)), this, SLOT(slotActionLoadNumTriggered(bool)));
    QAction *actionLoadColor = new QAction("Load video (&Color)", this);
    newDataMenu->addAction(actionLoadColor);

    QMenu *compareDataMenu = menuBar()->addMenu("&Compare data");

    QAction *actionCompareNum = new QAction("Compare data (&Number)", this);
    compareDataMenu->addAction(actionCompareNum);
    QAction *actionCompareColor = new QAction("Compare data (&Color)", this);
    compareDataMenu->addAction(actionCompareColor);


    player = new QMediaPlayer(this);
    connect(player, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(displayVideoError(QMediaPlayer::Error)));
    connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(slotMediaStatusChanged(QMediaPlayer::MediaStatus)));
    connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(slotdurationChanged(qint64)));

    graphicsView = new QGraphicsView(new QGraphicsScene(this), this);
    layoutPrincipal->addWidget(graphicsView);

    videoItem = new CustomQGraphicsVideoItem(this);
    player->setVideoOutput(videoItem);
    graphicsView->scene()->addItem(videoItem);
    graphicsView->show();

    //player->setMedia(QUrl::fromLocalFile("C:/Users/Arnaud/Documents/EPFL/5/Projet/TestApp/build-TestApp-Desktop_Qt_5_5_0_MinGW_32bit-Debug/ressources/videos/kapoue.wmv"));
    //player->pause();

    QWidget* actionBar = new QWidget(centralZone);
    QHBoxLayout *layoutActionBar = new QHBoxLayout;
    actionBar->setLayout(layoutActionBar);
    layoutPrincipal->addWidget(actionBar);

    QPushButton* buttonPrevious = new QPushButton("Previous frame", actionBar);
    layoutActionBar->addWidget(buttonPrevious);
    //connect(buttonPrevious, SIGNAL(clicked ()), this, SLOT(slotSaveAndExit()));

    QPushButton* buttonNext = new QPushButton("Next frame", actionBar);
    layoutActionBar->addWidget(buttonNext);
    connect(buttonNext, SIGNAL(clicked ()), this, SLOT(slotNextFrame()));

    labelVideoTime = new QLabel("00 : 00 / 00 : 00", actionBar);
    layoutActionBar->addWidget(labelVideoTime);

    labelVideoFrame = new QLabel("Frame 0 / 0", actionBar);
    layoutActionBar->addWidget(labelVideoFrame);

    QPushButton* buttonSave = new QPushButton("Save current data", actionBar);
    layoutActionBar->addWidget(buttonSave);

    QPushButton* buttonSaveAndExit = new QPushButton("Save current data and exit to menu", actionBar);
    layoutActionBar->addWidget(buttonSaveAndExit);

    frameDuration = 1000; // A CHANGER
    currentFrame = 0;
    videoData = 0;

    pointerPixmap = new QPixmap("ressources/images/pointer.png");

}

MainWindow::~MainWindow() { // A CHANGER
    delete this->centralWidget();
}

void MainWindow::displayVideoError(QMediaPlayer::Error error){
    qDebug() << error;
}

void MainWindow::slotMediaStatusChanged(QMediaPlayer::MediaStatus state){
    qDebug() << state;
    if (state == QMediaPlayer::LoadedMedia || state == QMediaPlayer::BufferedMedia){
        QSize size;

        size.setWidth(videoItem->nativeSize().width());
        size.setHeight(videoItem->nativeSize().height());
        if (size.width() > MIN_WIDTH || size.height() > MIN_HEIGHT){
            double ratioWidth = size.width() / (double) MIN_WIDTH;
            double ratioHeight = size.height() / (double) MIN_HEIGHT;
            if (ratioWidth > ratioHeight){
                size.setWidth(MIN_WIDTH);
                size.setHeight(size.height() / ratioWidth);
            }
            else {
                size.setWidth(size.width() / ratioHeight);
                size.setHeight(MIN_HEIGHT);
            }
        }
        graphicsView->setFixedWidth(size.width() + 2);
        graphicsView->setFixedHeight(size.height() + 2);
        videoItem->setSize(size);

        currentFrame = 0;
        setCorrectTimeAndFrame();
    }
}

void MainWindow::slotdurationChanged(qint64 duration){
    qDebug() << duration;
}

void MainWindow::slotNextFrame(){
    if (player->position() + frameDuration > player->duration()){
        slotSaveAndExit();
        currentFrame = 0;
    }
    else {
        player->setPosition(player->position() + frameDuration);
        videoData->addFrameData(currentFrame+1, new FrameData(videoData->getFrameData(currentFrame)));

        for (int i = 0; i < currentPixmaps.size(); i++){
            Data* pointer = currentPixmaps[i]->getDataPointer();
            Data* newPointer = 0;
            if (mode == NUMBER){
                newPointer = new NumberData(pointer->toNumber());
            }
            else {
                newPointer = new ColorData(pointer->toColor());
            }
            videoData->getFrameData(currentFrame+1)->addData(newPointer);
            currentPixmaps[i]->changePointers(newPointer, videoData->getFrameData(currentFrame+1));
        }


        currentFrame++;
    }

    setCorrectTimeAndFrame();
}

void MainWindow::slotActionLoadNumTriggered(bool b){
    mode = NUMBER;
    loadVideo();
}

void MainWindow::slotActionLoadColorTriggered(bool b){
    mode = COLOR;
    loadVideo();
}

void MainWindow::slotSaveAndExit(){
    graphicsView->setVisible(false);
}

void MainWindow::loadVideo(){
    QString fileName = QFileDialog::getOpenFileName(this, "Open a video", QString(), "Video (*.webm; *.wmv; *.mp4)");
    if (!fileName.isNull()){

       player->setMedia(QUrl::fromLocalFile(fileName));
       player->pause();
       graphicsView->setVisible(true);

       if (videoData != 0){
           delete videoData;
       }

       videoData = new VideoData();
       videoData->addFrameData(currentFrame, new FrameData());
    }
}

void MainWindow::update(){
    qDebug() << videoItem->nativeSize().width() << "kapue";
    //videoItem->setSize(videoItem->nativeSize());
}

void MainWindow::mouseClick(unsigned int x, unsigned int y){
    qDebug() << "(" << x << "," << y << ")";
    createCustomPixmap(x,y);
}

void MainWindow::createCustomPixmap(unsigned int x, unsigned int y){
    Data* dataPointer = 0;

    if (mode == NUMBER){
        dataPointer = new NumberData();
    }
    else {
        dataPointer = new ColorData();
    }
    videoData->getFrameData(currentFrame)->addData(dataPointer);
    CustomQGraphicsPixmapItem* item = new CustomQGraphicsPixmapItem(*pointerPixmap, dataPointer, videoData->getFrameData(currentFrame));
    item->setPos(x - IMAGE_POINTER_SIZE/2, y - IMAGE_POINTER_SIZE/2);
    graphicsView->scene()->addItem(item);
    item->setFlag(QGraphicsItem::ItemIsFocusable);
    item->setFlag(QGraphicsItem::ItemIsMovable);
    item->setFlag(QGraphicsItem::ItemIsSelectable);
    item->setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    currentPixmaps.append(item);
}

void MainWindow::setCorrectTimeAndFrame(){
    QString stringDurationMinutes = QString::number((player->duration()/1000)/60);
    if (stringDurationMinutes.size() == 1){
        stringDurationMinutes = "0" + stringDurationMinutes;
    }
    QString stringDurationSeconds = QString::number((player->duration()/1000)%60);
    if (stringDurationSeconds.size() == 1){
        stringDurationSeconds = "0" + stringDurationSeconds;
    }

    QString stringTimeMinutes = QString::number((currentFrame * frameDuration/1000)/60);
    if (stringTimeMinutes.size() == 1){
        stringTimeMinutes = "0" + stringTimeMinutes;
    }
    QString stringTimeSeconds = QString::number((currentFrame * frameDuration/1000)%60);
    if (stringTimeSeconds.size() == 1){
        stringTimeSeconds = "0" + stringTimeSeconds;
    }
    labelVideoTime->setText(stringTimeMinutes + " : " + stringTimeSeconds + " / " + stringDurationMinutes + " : " + stringDurationSeconds);

    labelVideoFrame->setText("Frame " +  QString::number(currentFrame) + " / " + QString::number(player->duration()/frameDuration));
}
