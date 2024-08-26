#include <QApplication>
#include <QLabel>

#include "./view/mainwindow.h"

using namespace s21;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Model m;
  Controller c(m);
  MainWindow v(c);
  v.setWindowTitle("Calc");
  v.show();
  return a.exec();
}
