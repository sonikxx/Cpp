#include "./controller.h"

using namespace s21;

std::string Controller::s21_calculate(std::string input, std::string x) {
  model_.s21_init(input, x);
  int flag = model_.s21_calculate();
  if (flag) {
    double res = model_.get_data().value();
    if (std::isnan(res))
      return "nan";
    else {
      std::ostringstream os;
      os << std::setprecision(11) << res;
      return os.str();
    }
  } else {
    return "Invalid input";
  }
}

int Controller::s21_can_draw_graph(std::string input, std::string x,
                                   double x_min, double x_max, double y_min,
                                   double y_max) {
  model_.s21_init(input, x);
  int flag = model_.s21_check_input();
  if (flag && x_min >= -1000000 && x_max <= 1000000 && y_min >= -1000000 &&
      y_max <= 1000000 && x_min < x_max && y_min < y_max &&
      input.find('x') != std::string::npos) {
    flag = model_.s21_reverse_polish_notation();
  } else {
    flag = ERROR;
  }
  return flag;
}

std::pair<std::vector<double>, std::vector<double>> Controller::s21_draw_graph(
    std::string input, double x_min, double x_max) {
  double x_begin = x_min;
  double x_end = x_max;
  double h = (x_end - x_begin) / 1000;
  std::vector<double> x, y;
  for (double x_tmp = x_begin; x_tmp <= x_end; x_tmp += h) {
    x.push_back(x_tmp);
    std::string string_x = std::to_string(x_tmp);
    model_.s21_init(input, string_x);
    int flag = model_.s21_calculate();
    if (flag) {
      y.push_back(this->get_data().value());
    } else
      x.pop_back();
  }
  return {x, y};
}

std::optional<double> Controller::get_data() { return model_.get_data(); }