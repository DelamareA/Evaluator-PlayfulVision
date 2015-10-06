#include "mainwindow.h"

WindowTerminal* MainWindow::terminal = NULL;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Evaluator");

    QWidget *centralZone = new QWidget(this);
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    setCentralWidget(centralZone);
    centralZone->setLayout(layoutPrincipal);

    QMenu *newDataMenu = menuBar()->addMenu("&New data");

    QAction *actionLoadNum = new QAction("Load video (&Number)", this);
    newDataMenu->addAction(actionLoadNum);
    connect(actionLoadNum, SIGNAL(triggered(bool)), this, SLOT(slotActionLoadNumTriggered(bool)));
    QAction *actionLoadColor = new QAction("Load video (&Color)", this);
    connect(actionLoadColor, SIGNAL(triggered(bool)), this, SLOT(slotActionLoadColorTriggered(bool)));
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

    inputBar = new QWidget(centralZone);
    QHBoxLayout *layoutInputBar = new QHBoxLayout;
    inputBar->setLayout(layoutInputBar);
    inputBar->setMaximumWidth(310);
    layoutPrincipal->addWidget(inputBar);
    inputBar->setVisible(false);

    QLabel* labelInput = new QLabel("Input value : ", inputBar);
    labelInput->setMaximumWidth(100);
    layoutInputBar->addWidget(labelInput);

    spinInputNumber = new QSpinBox(inputBar);
    spinInputNumber->setMinimum(1);
    spinInputNumber->setMaximumWidth(100);
    connect(spinInputNumber, SIGNAL(valueChanged(int)), this, SLOT(slotSpinInputValueChanged(int)));
    layoutInputBar->addWidget(spinInputNumber);

    comboInputColorTeam = new QComboBox(inputBar);
    comboInputColorTeam->addItem("Team 1");
    comboInputColorTeam->addItem("Team 2");
    comboInputColorTeam->addItem("Referee");
    comboInputColorTeam->setMaximumWidth(100);
    connect(comboInputColorTeam, SIGNAL(currentIndexChanged(int)), this, SLOT(slotComboInputIndexChanged(int)));
    layoutInputBar->addWidget(comboInputColorTeam);

    checkInputColorTemplate = new QCheckBox("Is template ?", inputBar);
    connect(checkInputColorTemplate, SIGNAL(stateChanged(int)), this, SLOT(slotCheckInputStateChanged(int)));
    layoutInputBar->addWidget(checkInputColorTemplate);

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
    connect(buttonSaveAndExit, SIGNAL(clicked ()), this, SLOT(slotSaveAndExit()));

    frameDuration = 1000; // A CHANGER
    currentFrame = 0;
    videoData = 0;
    focusedPixmap = 0;

    pointerPixmap = new QPixmap("ressources/images/pointer.png");
    pointerPixmap2 = new QPixmap("ressources/images/pointer2.png");

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

        inputBar->setVisible(true);

        spinInputNumber->setVisible(mode == NUMBER);
        comboInputColorTeam->setVisible(mode == COLOR);
        checkInputColorTemplate->setVisible(mode == COLOR);

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

            if (mode == NUMBER){
                Data* pointer = currentPixmaps[i]->getDataPointer();
                Data* newPointer = 0;

                newPointer = new NumberData(pointer->toNumber());

                videoData->getFrameData(currentFrame+1)->addData(newPointer);
                currentPixmaps[i]->changePointers(newPointer, videoData->getFrameData(currentFrame+1));
            }
            else if (currentPixmaps[i]->isOldest()){
                QPixmap snapshot = graphicsView->grab();
                QImage* imageCropped = new QImage(snapshot.toImage().copy(currentPixmaps[i]->getRect().toRect()));


                ColorData* pointer = (ColorData*)currentPixmaps[i]->getDataPointer();
                pointer->setImage(imageCropped);

                ColorData* newPointer = 0;
                newPointer = new ColorData(pointer->toColor(), ((ColorData*)(pointer))->getTemplate());

                videoData->getFrameData(currentFrame+1)->addData(newPointer);
                currentPixmaps[i]->changePointers(newPointer, videoData->getFrameData(currentFrame+1));
            }

        }


        currentFrame++;
    }

    setCorrectTimeAndFrame();
}

void MainWindow::slotActionLoadNumTriggered(bool b){
    mode = NUMBER;
    mode2 = false;
    loadVideo();
}

void MainWindow::slotActionLoadColorTriggered(bool b){
    mode = COLOR;
    mode2 = false;
    loadVideo();
}

void MainWindow::slotSaveAndExit(){
    for (int i = 0; i < currentPixmaps.size(); i++){
        if (mode == COLOR && currentPixmaps[i]->isOldest()){
            QPixmap snapshot = graphicsView->grab();
            QImage* imageCropped = new QImage(snapshot.toImage().copy(currentPixmaps[i]->getRect().toRect()));

            ColorData* pointer = (ColorData*)currentPixmaps[i]->getDataPointer();
            pointer->setImage(imageCropped);
        }

    }

    std::vector<TeamTestCase*> team_tc = this->create_team_test_cases_from_data();
    std::vector<NumTestCase*> number_tc = this->create_number_test_cases_from_data();
    if (team_tc.size() > 0){
        TeamTestCase::save_testcases_to_file(team_tc, "Team_test_cases.txt");
    }
    else if (number_tc.size() > 0){
        NumTestCase::save_testcases_to_file(number_tc, "Number_test_cases.txt");
    }
}

void MainWindow::slotSpinInputValueChanged(int i){
    if (focusedPixmap != 0){
        Data* oldData = focusedPixmap->getDataPointer();

        Data* newData = 0;

        if (mode == NUMBER){
            newData = new NumberData(i);

            newData->setX(oldData->getX());
            newData->setY(oldData->getY());

            videoData->getFrameData(currentFrame)->deleteData(oldData);
            videoData->getFrameData(currentFrame)->addData(newData);
            focusedPixmap->changePointers(newData, videoData->getFrameData(currentFrame));

        }
        else {
            qDebug() << "Mode should not be 'Color' when spinInput is visible";
        }
    }

}

void MainWindow::slotComboInputIndexChanged(int i){
    if (focusedPixmap != 0){
        ColorData* oldData = (ColorData *)focusedPixmap->getDataPointer();

        ColorData* newData = 0;

        if (mode == COLOR){
            newData = new ColorData(ColorData::intToColor(i), oldData->getTemplate());

            newData->setX(oldData->getX());
            newData->setY(oldData->getY());

            videoData->getFrameData(currentFrame)->deleteData(oldData);
            videoData->getFrameData(currentFrame)->addData(newData);

            focusedPixmap->changePointers(newData, videoData->getFrameData(currentFrame));
            CustomQGraphicsPixmapItem* brother = focusedPixmap->getBrother();
            if (brother != 0){
                brother->changePointers(newData, videoData->getFrameData(currentFrame));
            }

        }
        else {
            qDebug() << "Mode should not be 'Number' when comboInput is visible";
        }
    }
}

void MainWindow::slotCheckInputStateChanged(int s){
    if (focusedPixmap != 0){
        ColorData* oldData = (ColorData *)focusedPixmap->getDataPointer();

        ColorData* newData = 0;

        if (mode == COLOR){
            newData = new ColorData(oldData->toColor(), (bool)s);

            newData->setX(oldData->getX());
            newData->setY(oldData->getY());

            videoData->getFrameData(currentFrame)->deleteData(oldData);
            videoData->getFrameData(currentFrame)->addData(newData);

            focusedPixmap->changePointers(newData, videoData->getFrameData(currentFrame));
            CustomQGraphicsPixmapItem* brother = focusedPixmap->getBrother();
            if (brother != 0){
                brother->changePointers(newData, videoData->getFrameData(currentFrame));
            }

        }
        else {
            qDebug() << "Mode should not be 'Number' when checkInput is visible";
        }
    }
}

void MainWindow::loadVideo(){
    QString fileName = QFileDialog::getOpenFileName(this, "Open a video", QString(), "Video (*)");
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

}

void MainWindow::mouseClick(unsigned int x, unsigned int y){
    mode2 = !mode2;
    createCustomPixmap(x,y);
}

void MainWindow::createCustomPixmap(unsigned int x, unsigned int y){

    CustomQGraphicsPixmapItem* item = 0;

    if (mode == NUMBER){
        NumberData* dataPointer = new NumberData(spinInputNumber->value());
        item = new CustomQGraphicsPixmapItem(*pointerPixmap, dataPointer, videoData->getFrameData(currentFrame), this, 0);
        videoData->getFrameData(currentFrame)->addData(dataPointer);
    }
    else {
        if (mode2){
            Color c = ColorData::intToColor(comboInputColorTeam->currentIndex());
            ColorData* dataPointer = new ColorData(c, checkInputColorTemplate->isChecked());
            item = new CustomQGraphicsPixmapItem(*pointerPixmap, dataPointer, videoData->getFrameData(currentFrame), this, 0);
            videoData->getFrameData(currentFrame)->addData(dataPointer);
        }
        else {
            ColorData* dataPointer = (ColorData* )currentPixmaps.last()->getDataPointer();
            item = new CustomQGraphicsPixmapItem(*pointerPixmap2, dataPointer, videoData->getFrameData(currentFrame), this, currentPixmaps.last());
            currentPixmaps.last()->setBrother(item);
        }

    }

    item->setPos(x - IMAGE_POINTER_SIZE/2, y - IMAGE_POINTER_SIZE/2);
    graphicsView->scene()->addItem(item);
    item->setFlag(QGraphicsItem::ItemIsFocusable);
    item->setFlag(QGraphicsItem::ItemIsMovable);
    item->setFlag(QGraphicsItem::ItemIsSelectable);
    item->setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    currentPixmaps.append(item);

    updateRectangles();
}

void MainWindow::removeFocusedPixmap(CustomQGraphicsPixmapItem* pixmap){
    if (pixmap == focusedPixmap){
        focusedPixmap = 0;
    }
}

void MainWindow::removePixmap(CustomQGraphicsPixmapItem* pixmap){
    currentPixmaps.removeOne(pixmap);
    mode2 = false;
}

void MainWindow::setFocusedPixmap(CustomQGraphicsPixmapItem* pixmap){
    focusedPixmap = pixmap;

    if (mode == NUMBER){
        spinInputNumber->setValue(focusedPixmap->getDataPointer()->toNumber());
    }
    else {
        comboInputColorTeam->setCurrentIndex(ColorData::colorToInt(focusedPixmap->getDataPointer()->toColor()));
        ColorData* pointer = (ColorData*)focusedPixmap->getDataPointer();
        checkInputColorTemplate->setChecked(pointer->getTemplate());

        qDebug() << "Previous data : " << pointer;
    }
}

void MainWindow::updateRectangles(){
    for (int i = 0; i < currentPixmaps.size(); i++){
        currentPixmaps[i]->updateRectangle();
    }
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

void MainWindow::create_terminal(){
    terminal = new WindowTerminal();
}

void MainWindow::add_message_to_terminal(std::string msg){
    terminal->addText(QString::fromUtf8(msg.c_str()));
}

std::vector<TeamTestCase*> MainWindow::create_team_test_cases_from_data(){
    Time t = 0;
    std::vector<TeamTestCase*> test_cases;
    FrameData* f_data = videoData->getFrameData(t);
    while (f_data != NULL){
        QSetIterator<Data *> it = f_data->iterator();
        while (it.hasNext()){
            Data* data = it.next();
            if (data->isColor()){
                test_cases.push_back(TeamTestCase::build_test_case_from_color_data((ColorData*) data));
            }
        }
    }
    return test_cases;
}

std::vector<NumTestCase*> MainWindow::create_number_test_cases_from_data(){
    Time t = 0;
    std::vector<NumTestCase*> test_cases;
    FrameData* f_data = videoData->getFrameData(t);
    while (f_data != NULL){
        QSetIterator<Data *> it = f_data->iterator();
        while (it.hasNext()){
            Data* data = it.next();
            if (data->isNumber()){
                test_cases.push_back(NumTestCase::build_test_case_from_number_data((NumberData*) data));
            }
        }
    }
    return test_cases;
}
