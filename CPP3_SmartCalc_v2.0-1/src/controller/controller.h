#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iomanip>
#include <sstream>

#include "../model/model.h"

namespace s21 {

class Controller {
 private:
  Model &model_;

 public:
  Controller(Model &model) : model_(model){};
  std::string s21_calculate(std::string input, std::string x);
  int s21_can_draw_graph(std::string input, std::string x, double x_min,
                         double x_max, double y_min, double y_max);
  std::pair<std::vector<double>, std::vector<double>> s21_draw_graph(
      std::string input, double x_min, double x_max);
  std::optional<double> get_data();
};
}  // namespace s21

#endif  // CONTROLLER_H