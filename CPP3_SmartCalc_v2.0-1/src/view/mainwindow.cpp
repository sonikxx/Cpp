#include "./mainwindow.h"

#include "./ui_mainwindow.h"

using namespace s21;

int flag_input = 0;
int flag_change_x = 0;
int flag_change_xmin = 0;
int flag_change_xmax = 0;
int flag_change_ymin = 0;
int flag_change_ymax = 0;

MainWindow::MainWindow(Controller &c, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), controller_(c), form(c) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(input_char()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(input_char()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(input_char()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(input_char()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(input_char()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(input_char()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(input_char()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(input_char()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(input_char()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(input_char()));
  connect(ui->pushButton_e, SIGNAL(clicked()), this, SLOT(input_char()));
  connect(ui->pushButton_point, SIGNAL(clicked()), this, SLOT(input_char()));

  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(input_func()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(input_func()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(input_func()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(input_func()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(input_func()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(input_func()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(input_func()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(input_func()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(input_func()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(input_char()));
  connect(ui->pushButton_sum, SIGNAL(clicked()), this, SLOT(input_char()));
  connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(input_char()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(input_char()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(input_char()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(input_char()));

  connect(ui->pushButton_open_bracket, SIGNAL(clicked()), this,
          SLOT(input_char()));
  connect(ui->pushButton_close_bracket, SIGNAL(clicked()), this,
          SLOT(input_char()));

  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(input_char()));

  connect(ui->pushButton_clear, SIGNAL(clicked()), this, SLOT(delete_all()));
  connect(ui->pushButton_equal, SIGNAL(clicked()), this, SLOT(equal()));
  connect(ui->pushButton_graphic, SIGNAL(clicked()), this, SLOT(get_graphic()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::input_char() {
  if (flag_input == 0) clear();
  flag_input = 1;
  QPushButton *button =
      (QPushButton *)sender();  // получить ту кнопку, на которую нажали
  QString new_label = ui->result_show->text() + button->text();
  ui->result_show->setText(new_label);
}

void MainWindow::input_func() {
  if (flag_input == 0) clear();
  flag_input = 1;
  QPushButton *button = (QPushButton *)sender();
  QString new_label = ui->result_show->text() + button->text() + '(';
  ui->result_show->setText(new_label);
}

void MainWindow::equal() {
  flag_input = 0;
  QPushButton *button = (QPushButton *)sender();
  QString label = ui->result_show->text() + button->text();
  QByteArray arr = label.toLocal8Bit();
  std::string str = arr.data();
  QString x = ui->line_edit->text();
  QByteArray arr_x = x.toLocal8Bit();
  if (arr_x.size() == 0) {
    ui->result_show->setText("Enter value x");
    flag_input = 0;
  } else {
    std::string x_value = arr_x.data();
    std::string output_std = controller_.s21_calculate(str, x_value);
    QString output = QString::fromStdString(output_std);
    if (output_std == "nan" || output_std == "Invalid input") flag_input = 0;
    ui->result_show->setText(output);
  }
}

void MainWindow::get_graphic() {
  double x_min = ui->line_edit_xmin->text().toDouble();
  double x_max = ui->line_edit_xmax->text().toDouble();
  double y_min = ui->line_edit_ymin->text().toDouble();
  double y_max = ui->line_edit_ymax->text().toDouble();
  QString label = ui->result_show->text() + '=';
  QByteArray arr = label.toLocal8Bit();
  std::string str = arr.data();
  std::string x_value = "0";
  if (!controller_.s21_can_draw_graph(str, x_value, x_min, x_max, y_min,
                                      y_max)) {
    ui->result_show->setText("Invalid input");
  } else {
    form.Graph(str, x_min, x_max, y_min, y_max);
    form.setWindowTitle("Graphic");
    form.show();
  }
  flag_change_xmin = 0;
  flag_change_xmax = 0;
  flag_change_ymin = 0;
  flag_change_ymax = 0;
  flag_input = 0;
}

void MainWindow::change_x() {
  if (flag_change_x == 0) {
    QString newLabel;
    ui->line_edit->setText(newLabel);
  }
  flag_change_x = 1;
}

void MainWindow::change_xmin() {
  if (flag_change_xmin == 0) {
    QString newLabel;
    ui->line_edit_xmin->setText(newLabel);
  }
  flag_change_xmin = 1;
}

void MainWindow::change_xmax() {
  if (flag_change_xmax == 0) {
    QString newLabel;
    ui->line_edit_xmax->setText(newLabel);
  }
  flag_change_xmax = 1;
}

void MainWindow::change_ymin() {
  if (flag_change_ymin == 0) {
    QString newLabel;
    ui->line_edit_ymin->setText(newLabel);
  }
  flag_change_ymin = 1;
}

void MainWindow::change_ymax() {
  if (flag_change_ymax == 0) {
    QString newLabel;
    ui->line_edit_ymax->setText(newLabel);
  }
  flag_change_ymax = 1;
}

void MainWindow::delete_all() {
  QString newLabel = "0";
  ui->result_show->setText(newLabel);
  flag_input = 0;
}

void MainWindow::clear() {
  QString newLabel;
  ui->result_show->setText(newLabel);
}
