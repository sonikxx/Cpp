#ifndef MODEL_H
#define MODEL_H

#include <stdlib.h>

#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <optional>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#define ERROR 0
#define OK 1

// TODO обрабатывать ввод в экспоненциальной форме записи
// TODO убрать сборку build-view-Qt6-Debug

namespace s21 {

class Model {
 private:
  std::optional<double> data_;
  std::string input_;
  std::vector<std::string> output_;
  std::string x_;
  std::stack<std::string> stack_string;
  std::stack<double> stack_number;
  // удаление двойных пробелов, проверка на допустимые символы, замена mod на %
  int s21_remove_space();
  // проверка x на корректность и вставка
  int s21_insert_x();
  // проверка, что функции не разделены пробелом и не встречаются 2 числа
  // подряд, удаление оставшихся пробелов
  int s21_check_space();
  // скобочная последовательность вида ()
  int s21_check_bracket();
  // проверка, что знак равенства вставлен коррeктно
  int s21_check_equal();
  // проверка, что функция написана правильно
  int s21_check_function(std::string fun);
  // проверка корректности введеных слов
  int s21_check_alpha();
  // проверка, что числа написаны правильно
  int s21_check_digit();
  // проверка, что 2 операции или операнда не могут идти подряд + унарные
  // операции
  int s21_check_order();
  int s21_operation_priority(std::string operation);
  int s21_calculation_expressions();

 public:
  Model() {}
  Model(std::string input, std::string x) {
    input_ = input;
    x_ = x;
  };
  void s21_init(std::string input, std::string x) {
    input_ = input;
    x_ = x;
  }
  int s21_check_input();
  int s21_reverse_polish_notation();
  int s21_calculate();
  std::optional<double> get_data();
};
}  // namespace s21

#endif  // MODEL_H