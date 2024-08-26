#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(s21::Controller *Controller, QWidget *parent)
    : Controller(Controller), QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    settingConfig();
    win = glView::getInstance(Controller, ui->openGLWidget);
    win->resize(792, 792);
    win->setOptions(Options);
    choiceDirectory = QApplication::applicationDirPath();
    fileList = new QFileSystemModel(this);
    fileList->setFilter(QDir::AllEntries | QDir::NoDot);
    ui->listView->setModel(fileList);
    ui->listView->setRootIndex(
        fileList->setRootPath(choiceDirectory.section("/", 0, -4)));
    connect(ui->pushButtonColorDot, SIGNAL(clicked()), SLOT(setColor()));
    connect(ui->pushButtonColorLine, SIGNAL(clicked()), SLOT(setColor()));
    connect(ui->pushButtonColorBack, SIGNAL(clicked()), SLOT(setColor()));
    connect(ui->radioButtoCentralProection, SIGNAL(clicked()),
            SLOT(proectionChanged()));
    connect(ui->radioButtonParallelProection, SIGNAL(clicked()),
            SLOT(proectionChanged()));
    connect(ui->radioButtonDotCircle, SIGNAL(clicked()), SLOT(dotTypeChanged()));
    connect(ui->radioButtonDotSquare, SIGNAL(clicked()), SLOT(dotTypeChanged()));
    connect(ui->radioButtonDotNothing, SIGNAL(clicked()), SLOT(dotTypeChanged()));
    connect(ui->radioButtonLineSolid, SIGNAL(clicked()), SLOT(lineTypeChanged()));
    connect(ui->radioButtonLineDotted, SIGNAL(clicked()),
            SLOT(lineTypeChanged()));
    connect(ui->radioButtonLineNothing, SIGNAL(clicked()),
            SLOT(lineTypeChanged()));
    connect(ui->radioButtonRotationX, SIGNAL(clicked()),
            SLOT(radioButtonValue()));
    connect(ui->radioButtonRotationY, SIGNAL(clicked()),
            SLOT(radioButtonValue()));
    connect(ui->radioButtonRotationZ, SIGNAL(clicked()),
            SLOT(radioButtonValue()));
    connect(ui->radioButtonMoveX, SIGNAL(clicked()), SLOT(radioButtonValue()));
    connect(ui->radioButtonMoveY, SIGNAL(clicked()), SLOT(radioButtonValue()));
    connect(ui->radioButtonMoveZ, SIGNAL(clicked()), SLOT(radioButtonValue()));
    connect(ui->radioButtonZoomeLine, SIGNAL(clicked()),
            SLOT(radioButtonValue()));
    connect(ui->radioButtonZoomeDot, SIGNAL(clicked()), SLOT(radioButtonValue()));
    connect(ui->radioButtonZoomeModel, SIGNAL(clicked()),
            SLOT(radioButtonValue()));

    imagesCounter = 0;
    timer = new QTimer();
    images = new QImage[50];
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerFinish()));
}

MainWindow::~MainWindow() {
    delete fileList;
    delete win;
    delete timer;
    delete[] images;
    delete ui;
}

void MainWindow::settingConfig() {
    Options.GetSettings();
    if (Options.vertex_type == 0) {
        ui->radioButtonDotCircle->setChecked(1);
    } else if (Options.vertex_type == 1) {
        ui->radioButtonDotSquare->setChecked(1);
    } else if (Options.vertex_type == 2) {
        ui->radioButtonDotNothing->setChecked(1);
    }
    if (Options.line_type == 0) {
        ui->radioButtonLineSolid->setChecked(1);
    } else if (Options.line_type == 1) {
        ui->radioButtonLineDotted->setChecked(1);
    } else if (Options.line_type == 2) {
        ui->radioButtonLineNothing->setChecked(1);
    }
    if (Options.projection_orth) {
        ui->radioButtoCentralProection->setChecked(1);
    } else {
        ui->radioButtonParallelProection->setChecked(1);
    }
    ui->labelColorLine->setStyleSheet(
        QString("background-color: %1").arg(Options.line_color.name()));
    ui->labelColorDot->setStyleSheet(
        QString("background-color: %1").arg(Options.vertex_color.name()));
    ui->labelColorBack->setStyleSheet(
        QString("background-color: %1").arg(Options.back_color.name()));
    valueZoomeDot = Options.vertex_size;
    valueZoomeLine = Options.line_width;
}

void MainWindow::proectionChanged() {
    if (ui->radioButtonParallelProection->isChecked()) {
        Options.projection_orth = false;
    } else {
        Options.projection_orth = true;
    }
    win->setOptions(Options);
}

void MainWindow::dotTypeChanged() {
    if (ui->radioButtonDotCircle->isChecked()) {
        Options.vertex_type = 0;
    } else if (ui->radioButtonDotSquare->isChecked()) {
        Options.vertex_type = 1;
    } else {
        Options.vertex_type = 2;
    }
    win->setOptions(Options);
}

void MainWindow::lineTypeChanged() {
    if (ui->radioButtonLineSolid->isChecked()) {
        Options.line_type = 0;
    } else if (ui->radioButtonLineDotted->isChecked()) {
        Options.line_type = 1;
    } else if (ui->radioButtonLineNothing->isChecked()) {
        Options.line_type = 2;
    }
    win->setOptions(Options);
}

void MainWindow::on_listView_doubleClicked(const QModelIndex &index) {
    QFileInfo fileInfo = fileList->fileInfo(index);
    if (fileInfo.fileName() == "..") {
        dir = fileInfo.dir();
        dir.cdUp();
        ui->listView->setRootIndex(fileList->index(dir.absolutePath()));
    } else if (fileInfo.fileName() == ".") {
        ui->listView->setRootIndex(fileList->index(""));
    } else if (fileInfo.isDir()) {
        ui->listView->setRootIndex(index);
    } else if (fileInfo.completeSuffix() == "obj") {
        QString filePath = fileInfo.filePath();
        ui->lineEdit->setText(filePath);
    } else {
        ui->statusBar->showMessage("⛔️ INPUT ERROR", 3000);
    }
}

void MainWindow::on_pushButton_clicked() {
    ui->pushButton->setEnabled(false);
    try {
        Controller->SetFilename(ui->lineEdit->text().toStdString());
        Controller->ProcessData(); // парсинг и нормализация
        // Controller->parse(ui->lineEdit->text().toStdString());
        win->translate(Controller->GetVertexes(), Controller->GetFaces());

        ui->statusBar->showMessage(
            QString("Количество вершин: %1      Количество рёбер: %2")
                .arg(Controller->GetVertexCount())
                .arg(Controller->GetFaceCount()));
    } catch (std::exception const &errorMessage) {
        ui->statusBar->showMessage(
            "ОШИБКА: возможно " + QString::fromStdString(errorMessage.what()),
            3000);
    }
    ui->pushButton->setEnabled(true);
}

void MainWindow::setColor() {
    color = QColorDialog::getColor();
    if (color.isValid()) {
        QObject *obj = (QObject *)(sender());
        if (obj->objectName() == "pushButtonColorDot") {
            ui->labelColorDot->setStyleSheet(
                QString("background-color: %1").arg(color.name()));
            Options.vertex_color = color;
        } else if (obj->objectName() == "pushButtonColorLine") {
            ui->labelColorLine->setStyleSheet(
                QString("background-color: %1").arg(color.name()));
            Options.line_color = color;
        } else if (obj->objectName() == "pushButtonColorBack") {
            ui->labelColorBack->setStyleSheet(
                QString("background-color: %1").arg(color.name()));
            Options.back_color = color;
        }
        win->setOptions(Options);
    }
}

void MainWindow::radioButtonValue() {
    QObject *obj = (QObject *)(sender());
    valueScrolBar = 50;
    if (obj->objectName() == "radioButtonRotationX") {
        ui->verticalScrollBar->setValue(valueScrolBar);
        win->scrollBar(0, obj->objectName());
    }
    if (obj->objectName() == "radioButtonRotationY") {
        ui->verticalScrollBar->setValue(valueScrolBar);
        win->scrollBar(0, obj->objectName());
    }
    if (obj->objectName() == "radioButtonRotationZ") {
        ui->verticalScrollBar->setValue(valueScrolBar);
        win->scrollBar(0, obj->objectName());
    }
    if (obj->objectName() == "radioButtonMoveX") {
        ui->verticalScrollBar->setValue(valueScrolBar);
        win->scrollBar(0, obj->objectName());
    }
    if (obj->objectName() == "radioButtonMoveY") {
        ui->verticalScrollBar->setValue(valueScrolBar);
        win->scrollBar(0, obj->objectName());
    }
    if (obj->objectName() == "radioButtonMoveZ") {
        ui->verticalScrollBar->setValue(valueScrolBar);
        win->scrollBar(0, obj->objectName());
    }
    if (obj->objectName() == "radioButtonZoomeLine") {
        ui->verticalScrollBar->setValue(Options.line_width * 100);
    }
    if (obj->objectName() == "radioButtonZoomeDot") {
        ui->verticalScrollBar->setValue(Options.vertex_size * 100);
    }
    if (obj->objectName() == "radioButtonZoomeModel") {
        ui->verticalScrollBar->setValue(valueScrolBar);
        win->scrollBar(1, obj->objectName());
    }
    win->setOptions(Options);
}

void MainWindow::on_verticalScrollBar_valueChanged(int value) {
    if (ui->radioButtonRotationX->isChecked()) {
        checkerName = ui->radioButtonRotationX->objectName();
    }
    if (ui->radioButtonRotationY->isChecked()) {
        checkerName = ui->radioButtonRotationY->objectName();
    }
    if (ui->radioButtonRotationZ->isChecked()) {
        checkerName = ui->radioButtonRotationZ->objectName();
    }
    if (ui->radioButtonMoveX->isChecked()) {
        checkerName = ui->radioButtonMoveX->objectName();
    }
    if (ui->radioButtonMoveY->isChecked()) {
        checkerName = ui->radioButtonMoveY->objectName();
    }
    if (ui->radioButtonMoveZ->isChecked()) {
        checkerName = ui->radioButtonMoveZ->objectName();
    }
    if (ui->radioButtonZoomeLine->isChecked()) {
        Options.line_width = value ? (value + 2) / 100.0 : 0.0;
        checkerName = ui->radioButtonZoomeLine->objectName();
    }
    if (ui->radioButtonZoomeDot->isChecked()) {
        Options.vertex_size = value / 100.0;
        checkerName = ui->radioButtonZoomeDot->objectName();
    }
    if (ui->radioButtonZoomeModel->isChecked()) {
        checkerName = ui->radioButtonZoomeModel->objectName();
    }
    int buffer = value;
    value -= valueScrolBar;
    valueScrolBar = buffer;
    win->scrollBar(value, checkerName);
    win->setOptions(Options);
}

void MainWindow::on_pushButtonGIF_clicked() {
    ui->pushButtonGIF->setEnabled(false);
    timer->start(100);
}

void MainWindow::on_pushButtonJPG_clicked() {
    QDateTime curTime = QDateTime::currentDateTime();
    QImage img = win->grabFramebuffer();
    QString formatDate = "hh:mm:ss_dd.MM.yyyy";
    QString dirPath = QDir::home().absolutePath() + "/Desktop/images/";
    if (QDir().exists(dirPath)) {
        img.save(dirPath + curTime.toString(formatDate) + ".jpg");
    } else {
        QDir().mkpath(dirPath);
        img.save(dirPath + curTime.toString(formatDate) + ".jpg");
    }
}

void MainWindow::slotTimerFinish() {
    if (imagesCounter < 50) {
        images[imagesCounter] = win->grabFramebuffer();
        imagesCounter++;
        ui->statusBar->showMessage(QString::number(imagesCounter), 100);
    } else {
        timer->stop();
        QGifImage gif(QSize(640, 480));
        gif.setDefaultDelay(100);
        gif.setDefaultTransparentColor(Qt::yellow);
        for (int i = 0; i < 50; ++i) {
            gif.addFrame(images[i].scaled(640, 480));
        }
        QDateTime curTime = QDateTime::currentDateTime();
        QImage img = win->grabFramebuffer();
        QString formatDate = "hh:mm:ss_dd.MM.yyyy";
        QString dirPath = QDir::home().absolutePath() + "/Desktop/images/";
        if (QDir().exists(dirPath)) {
            gif.save(dirPath + curTime.toString(formatDate) + ".gif");
        } else {
            QDir().mkpath(dirPath);
            gif.save(dirPath + curTime.toString(formatDate) + ".gif");
        }
        imagesCounter = 0;
        ui->pushButtonGIF->setEnabled(true);
        ui->statusBar->showMessage("Finish create gif ", 3000);
    }
}

void MainWindow::on_pushButtonBMP_clicked() {
    QDateTime curTime = QDateTime::currentDateTime();
    QImage img = win->grabFramebuffer();
    QString formatDate = "hh:mm:ss_dd.MM.yyyy";
    QString dirPath = QDir::home().absolutePath() + "/Desktop/images/";
    if (QDir().exists(dirPath)) {
        img.save(dirPath + curTime.toString(formatDate) + ".bmp");
    } else {
        QDir().mkpath(dirPath);
        img.save(dirPath + curTime.toString(formatDate) + ".bmp");
    }
}
