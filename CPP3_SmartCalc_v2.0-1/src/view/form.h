#ifndef FORM_H
#define FORM_H

#include <QVector>
#include <QWidget>

#include "../controller/controller.h"
#include "qcustomplot.h"

namespace Ui {
class Form;
}

namespace s21 {
class Form : public QWidget {
  Q_OBJECT

 private:
  Ui::Form *ui;
  Controller &controller_;

 public:
  explicit Form(Controller &c, QWidget *parent = nullptr);
  ~Form();
  void Graph(std::string str, double x_min, double x_max, double y_min,
             double y_max);
};
}  // namespace s21

#endif  // FORM_H
