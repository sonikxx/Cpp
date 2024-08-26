#include <QApplication>

#include "view/mainwindow.h"

int main(int argc, char *argv[]) {
    QSurfaceFormat window_surface = QSurfaceFormat::defaultFormat();
    window_surface.setMajorVersion(4);
    window_surface.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(window_surface);
    QApplication a(argc, argv);

    s21::Controller c("");
    // создать мейнвиндоу и там получить название файла, передать в котроллер и тд
    MainWindow w(&c);

    w.setFixedSize(1250, 830);
    w.setWindowTitle("3DViewer v2");
    w.show();
    return a.exec();
}
