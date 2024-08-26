#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <form.h>

#include <QMainWindow>

#include "../controller/controller.h"
#include "../model/model.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 private:
  Ui::MainWindow *ui;
  Controller &controller_;
  Form form;

 public:
  MainWindow(Controller &c, QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void input_char();
  void input_func();
  void delete_all();
  void equal();
  void get_graphic();
  void change_x();
  void change_xmin();
  void change_xmax();
  void change_ymin();
  void change_ymax();
  void clear();
};
}  // namespace s21

#endif  // MAINWINDOW_H
