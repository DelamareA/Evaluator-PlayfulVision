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
    connect(actionCompareNum, SIGNAL(triggered(bool)), this, SLOT(slotActionCompareNumTriggered(bool)));
    QAction *actionCompareColor = new QAction("Compare data (&Color)", this);
    compareDataMenu->addAction(actionCompareColor);
    connect(actionCompareColor, SIGNAL(triggered(bool)), this, SLOT(slotActionCompareColorTriggered(bool)));


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
            currentPixmaps[i]->setVisible2(false);
        }
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
        for (int i = 0; i < currentPixmaps.size(); i++){
            currentPixmaps[i]->setVisible2(true);
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

void MainWindow::slotActionCompareNumTriggered(bool b){
    littleWindowNumber = new QWidget();
    QVBoxLayout *layoutLittleWindow = new QVBoxLayout;
    littleWindowNumber->setLayout(layoutLittleWindow);
    littleWindowNumber->setWindowTitle("Number data comparison");

    QWidget* widgetManual = new QWidget(littleWindowNumber);
    layoutLittleWindow->addWidget(widgetManual);
    QHBoxLayout* layoutManual = new QHBoxLayout;
    widgetManual->setLayout(layoutManual);

    labelManual = new QLabel("No file selected", widgetManual);
    layoutManual->addWidget(labelManual);
    QPushButton* buttonManual = new QPushButton("Select manual data", widgetManual);
    connect(buttonManual, SIGNAL(clicked ()), this, SLOT(slotManualFileSelection()));
    layoutManual->addWidget(buttonManual);

    QWidget* widgetAutomatic = new QWidget(littleWindowNumber);
    layoutLittleWindow->addWidget(widgetAutomatic);
    QHBoxLayout* layoutAutomatic = new QHBoxLayout;
    widgetAutomatic->setLayout(layoutAutomatic);

    labelAutomatic = new QLabel("No file selected", widgetAutomatic);
    layoutAutomatic->addWidget(labelAutomatic);
    QPushButton* buttonAutomatic = new QPushButton("Select automatic data", widgetAutomatic);
    connect(buttonAutomatic, SIGNAL(clicked ()), this, SLOT(slotAutomaticFileSelection()));
    layoutAutomatic->addWidget(buttonAutomatic);

    QPushButton* buttonCompare = new QPushButton("Compare data !", littleWindowNumber);
    buttonCompare->setMaximumWidth(200);
    connect(buttonCompare, SIGNAL(clicked ()), this, SLOT(compareNum()));
    layoutLittleWindow->addWidget(buttonCompare);

    littleWindowNumber->setVisible(true);
}

void MainWindow::slotActionCompareColorTriggered(bool b){
    littleWindowColor = new QWidget();
    QVBoxLayout *layoutLittleWindow = new QVBoxLayout;
    littleWindowColor->setLayout(layoutLittleWindow);
    littleWindowColor->setWindowTitle("Color data comparison");

    QWidget* widgetManual = new QWidget(littleWindowColor);
    layoutLittleWindow->addWidget(widgetManual);
    QHBoxLayout* layoutManual = new QHBoxLayout;
    widgetManual->setLayout(layoutManual);

    labelManual = new QLabel("No file selected", widgetManual);
    layoutManual->addWidget(labelManual);
    QPushButton* buttonManual = new QPushButton("Select manual data", widgetManual);
    connect(buttonManual, SIGNAL(clicked ()), this, SLOT(slotManualFileSelection()));
    layoutManual->addWidget(buttonManual);

    QWidget* widgetAutomatic = new QWidget(littleWindowColor);
    layoutLittleWindow->addWidget(widgetAutomatic);
    QHBoxLayout* layoutAutomatic = new QHBoxLayout;
    widgetAutomatic->setLayout(layoutAutomatic);

    labelAutomatic = new QLabel("No file selected", widgetAutomatic);
    layoutAutomatic->addWidget(labelAutomatic);
    QPushButton* buttonAutomatic = new QPushButton("Select automatic data", widgetAutomatic);
    connect(buttonAutomatic, SIGNAL(clicked ()), this, SLOT(slotAutomaticFileSelection()));
    layoutAutomatic->addWidget(buttonAutomatic);

    QPushButton* buttonCompare = new QPushButton("Compare data !", littleWindowColor);
    buttonCompare->setMaximumWidth(200);
    connect(buttonCompare, SIGNAL(clicked ()), this, SLOT(compareColor()));
    layoutLittleWindow->addWidget(buttonCompare);

    littleWindowColor->setVisible(true);
}

void MainWindow::slotManualFileSelection(){
    QString fileName = QFileDialog::getOpenFileName(this, "Open a txt", QString(), "Text (*.txt)");
    if (!fileName.isNull()){
        labelManual->setText(fileName);
    }
}

void MainWindow::slotAutomaticFileSelection(){
    QString fileName = QFileDialog::getOpenFileName(this, "Open a txt", QString(), "Text (*.txt)");
    if (!fileName.isNull()){
        labelAutomatic->setText(fileName);
    }
}


void MainWindow::compareNum(){
    QString manualFile = labelManual->text();
    QString automaticFile = labelAutomatic->text();
    delete littleWindowNumber;
    littleWindowNumber = 0;

    // MET TON CODE ICI POUR LES NOMBRES
}

void MainWindow::compareColor(){
    QString manualFile = labelManual->text();
    QString automaticFile = labelAutomatic->text();
    delete littleWindowColor;
    littleWindowColor = 0;

    // MET TON CODE ICI POUR LES COULEURS
}

void MainWindow::slotSaveAndExit(){
    for (int i = 0; i < currentPixmaps.size(); i++){
        currentPixmaps[i]->setVisible2(false);
    }
    for (int i = 0; i < currentPixmaps.size(); i++){
        if (mode == COLOR && currentPixmaps[i]->isOldest()){
            QPixmap snapshot = graphicsView->grab();
            QImage* imageCropped = new QImage(snapshot.toImage().copy(currentPixmaps[i]->getRect().toRect()));

            ColorData* pointer = (ColorData*)currentPixmaps[i]->getDataPointer();
            pointer->setImage(imageCropped);
        }

    }
    for (int i = 0; i < currentPixmaps.size(); i++){
        currentPixmaps[i]->setVisible2(true);
    }

    std::vector<TeamTestCase*> team_tc = this->create_team_test_cases_from_data();
    std::vector<NumTestCase*> number_tc = this->create_number_test_cases_from_data();
    if (team_tc.size() > 0){
        TeamTestCase::save_testcases_to_file(team_tc, "Team_test_cases.txt");
    }
    else{
        qDebug() << "Empty vector ecountered while saving, no data ?";
    }

    if (number_tc.size() > 0){
        NumTestCase::save_testcases_to_file(number_tc, "Number_test_cases.txt");
    }
    else{
        qDebug() << "Empty vector ecountered while saving, no data ?";
    }
    qDebug() << "Preparing to run tests";
    ComparatorTeam ct("Team_test_cases.txt");
    ct.run_test_cases();
    qDebug() << "Team test done";
    ComparatorNumber cn("Number_test_cases.txt");
    cn.run_test_cases();
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
    if (f_data == NULL){
        qDebug() << "Null pointer on frame data while attemping to save. Abort.";
        return test_cases;
    }
    while (f_data != NULL){
        QSetIterator<Data *> it = f_data->iterator();
        while (it.hasNext()){
            Data* data = it.next();
            if (data == NULL){
                qDebug() << "Null pointer on data while attemping to save. Abort.";
                return test_cases;
            }
            if (data->isColor()){
                test_cases.push_back(TeamTestCase::build_test_case_from_color_data((ColorData*) data));
            }
        }
        t = t+1;
        f_data = videoData->getFrameData(t);
    }
    return test_cases;
}

std::vector<NumTestCase*> MainWindow::create_number_test_cases_from_data(){
    Time t = 0;
    std::vector<NumTestCase*> test_cases;
    FrameData* f_data = videoData->getFrameData(t);
    if (f_data == NULL){
        qDebug() << "Null pointer on frame data while attemping to save. Abort.";
        return test_cases;
    }
    while (f_data != NULL){
        QSetIterator<Data *> it = f_data->iterator();
        while (it.hasNext()){
            Data* data = it.next();
            if (data == NULL){
                qDebug() << "Null pointer on data while attemping to save. Abort.";
                return test_cases;
            }
            if (data->isNumber()){
                test_cases.push_back(NumTestCase::build_test_case_from_number_data((NumberData*) data));
            }
        }
        t = t+1;
        f_data = videoData->getFrameData(t);
    }
    return test_cases;
}
