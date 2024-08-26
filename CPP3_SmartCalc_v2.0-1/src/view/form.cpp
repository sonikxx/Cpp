#include "form.h"

#include "ui_form.h"

using namespace s21;

Form::Form(Controller &c, QWidget *parent)
    : QWidget(parent), ui(new Ui::Form), controller_(c) {
  ui->setupUi(this);
}

Form::~Form() { delete ui; }

void Form::Graph(std::string str, double x_min, double x_max, double y_min,
                 double y_max) {
  ui->widget->clearGraphs();  // удаление графика
  ui->widget->xAxis->setRange(x_min, x_max);
  ui->widget->yAxis->setRange(y_min, y_max);
  auto [x, y] = controller_.s21_draw_graph(str, x_min, x_max);
  QVector<double> Qx(x.begin(), x.end());
  QVector<double> Qy(y.begin(), y.end());
  ui->widget->addGraph();                 // добавление графика
  ui->widget->graph(0)->addData(Qx, Qy);  // установка значений графика
  ui->widget->replot();                   // рисование графика
}
