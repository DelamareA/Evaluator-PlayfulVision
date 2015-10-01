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
    //connect(buttonNext, SIGNAL(clicked ()), this, SLOT(slotNextFrame()));

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
        graphicsView->setFixedWidth(videoItem->nativeSize().width() + 2);
        graphicsView->setFixedHeight(videoItem->nativeSize().height() + 2);
        videoItem->setSize(videoItem->nativeSize());

        currentFrame = 0;
        setCorrectTimeAndFrame();
    }
}

void MainWindow::slotNextFrame(){
    //player->duration()
    player->setPosition(player->position() + frameDuration);
    currentFrame++;
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

void MainWindow::loadVideo(){
    QString fileName = QFileDialog::getOpenFileName(this, "Open a video", QString(), "Video (*.mp4, *.wmv)");
    if (!fileName.isNull()){
       player->setMedia(QUrl::fromLocalFile(fileName));
       player->pause();
    }
}

void MainWindow::update(){
    qDebug() << videoItem->nativeSize().width() << "kapue";
    //videoItem->setSize(videoItem->nativeSize());
}

void MainWindow::mouseClick(unsigned int x, unsigned int y){
    qDebug() << "(" << x << "," << y << ")";

    CustomQGraphicsPixmapItem* item = new CustomQGraphicsPixmapItem(*pointerPixmap, new NumberData());
    item->setPos(x - IMAGE_POINTER_SIZE/2, y - IMAGE_POINTER_SIZE/2);
    graphicsView->scene()->addItem(item);
    item->setFlag(QGraphicsItem::ItemIsMovable);
    item->setFlag(QGraphicsItem::ItemIsSelectable);
    item->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
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
