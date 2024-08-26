#include "model.h"

using namespace s21;

std::optional<double> Model::get_data() { return data_; }

int Model::s21_check_input() {
  int flag = ERROR;
  if (input_.length() <= 255 && this->s21_remove_space() &&
      this->s21_insert_x() && this->s21_check_space() &&
      this->s21_check_bracket() && this->s21_check_alpha() &&
      this->s21_check_digit() && this->s21_check_order())
    flag = OK;
  return flag;
}

int Model::s21_remove_space() {
  int flag = OK;
  int len = input_.length();
  std::string new_string;
  std::string special_char = "0123456789 ()+-*/^.";
  int k = 0;
  while (input_[k] == ' ' && k < len) {  // убираем лишние пробелы в начале
    ++k;
  }
  if (k > 0) {
    --k;
  }
  for (int i = k; i < len; ++i) {
    if (input_[i] == '=') {
      new_string.push_back('=');
      break;
    }
    if ((input_[i] >= 'a' && input_[i] <= 'z') ||
        special_char.find(input_[i]) != std::string::npos) {
      if ((input_[i] == ' ' && input_[i - 1] != ' ') || input_[i] != ' ') {
        if (i + 2 < len && input_.compare(i, 3, "mod") == 0) {
          new_string.push_back('%');
          i += 2;
        } else {
          new_string.push_back(input_[i]);
        }
      }
    } else {
      // std::cout << "Используются недопустимые символы\n";
      flag = ERROR;
      break;
    }
  }
  if (flag) {
    input_ = new_string;
    new_string.clear();
  }
  return flag;
}

int Model::s21_insert_x() {
  int flag = OK;
  int len = input_.length();
  std::string new_string;
  int flag_x = 0;
  int flag_dot = 0;
  int flag_e = 0;
  std::string special_char = "0123456789.,-e";
  while (x_.find(',') != std::string::npos) {
    auto start = x_.find(',');
    x_.replace(start, 1, ".");
  }
  for (size_t k = 0; k < x_.length(); ++k) {
    if (special_char.find(x_[k]) == std::string::npos) {
      flag = ERROR;
      break;
    } else {
      if (x_[k] == '.') {
        if (flag_dot == 0)
          flag_dot = 1;
        else {
          flag = ERROR;
          break;
        }
      }
      if (x_[k] == 'e') {
        if (flag_e == 0)
          flag_e = 1;
        else {
          flag = ERROR;
          break;
        }
      }
    }
  }
  if ((x_.length() > 1 && x_[0] == '0' && flag_dot == 0) ||
      (x_.length() >= 2 && x_[0] == '0' && x_[1] == '0')) {
    flag = ERROR;
  }
  if (flag) {
    char *nstr;
    const char *start = x_.c_str();
    double number_x = strtod(x_.c_str(), &nstr);
    if (x_[0] == '.' || (number_x == 0 && x_ != "0" && nstr != start)) {
      flag = ERROR;
    } else if (flag_e == 1) {
      std::ostringstream os;
      os << std::fixed << std::setprecision(15) << number_x;
      x_ = os.str();
    }
  }
  if (flag) {
    for (int i = 0; i < len && flag == OK; ++i) {
      if (input_[i] == 'x') {
        if ((i >= 1 && (isdigit(input_[i - 1]) || input_[i - 1] == 'x')) ||
            (i + 1 < len && (isdigit(input_[i + 1]) || input_[i + 1] == 'x'))) {
          flag = ERROR;
          break;
        } else {
          flag_x = 1;
          for (size_t k = 0; k < x_.length(); ++k) {
            new_string.push_back(x_[k]);
          }
        }
      } else
        new_string.push_back(input_[i]);
    }
    // убрать -- или +-
    if (x_[0] == '-') {
      std::string new_string2;
      for (size_t i = 0; i < new_string.length() - 1; ++i) {
        if (new_string[i] == '-' && new_string[i + 1] == '-') {
          new_string2.push_back('+');
          ++i;
        } else if (new_string[i] == '+' && new_string[i + 1] == '-') {
          new_string2.push_back('-');
          ++i;
        } else
          new_string2.push_back(new_string[i]);
      }
      if (flag_x) {
        input_ = new_string2;
        new_string.clear();
        new_string2.clear();
      }
    } else if (flag_x) {
      input_ = new_string;
      new_string.clear();
    }
  }
  return flag;
}

int Model::s21_check_space() {
  int flag = OK;
  int len = input_.length();
  std::string new_string;
  for (int i = 0; i < len; ++i) {
    if (input_[i] == ' ' && i - 1 >= 0 &&
        (((isdigit(input_[i - 1]) || input_[i - 1] == '.') && i + 1 < len &&
          (isdigit(input_[i + 1]) || input_[i + 1] == '.')) ||
         isalpha(input_[i - 1]))) {
      // std::cout << "Функция разделена пробелами или записаны 2 числа
      // подряд\n";
      flag = ERROR;
      break;
    }
    if (input_[i] != ' ') new_string.push_back(input_[i]);
  }
  if (flag) {
    input_ = new_string;
    new_string.clear();
  }
  return flag;
}

int Model::s21_check_bracket() {
  int flag = OK;
  for (size_t i = 0; i < input_.length() - 1; ++i) {
    if (input_[i] == '(' && input_[i + 1] == ')') flag = ERROR;
  }
  return flag;
}

int Model::s21_check_function(std::string fun) {
  int flag = ERROR;
  if (fun.find("sin") != std::string::npos ||
      fun.find("cos") != std::string::npos ||
      fun.find("tan") != std::string::npos ||
      fun.find("acos") != std::string::npos ||
      fun.find("asin") != std::string::npos ||
      fun.find("atan") != std::string::npos ||
      fun.find("sqrt") != std::string::npos ||
      fun.find("ln") != std::string::npos ||
      fun.find("log") != std::string::npos)
    flag = OK;
  return flag;
}

int Model::s21_check_alpha() {
  int flag = OK;
  int len = input_.length();
  std::string string_function;
  int flag_function = 0;
  for (int i = 0; i < len; ++i) {
    while (isalpha(input_[i]) &&
           !(i >= 1 && isdigit(input_[i - 1]) && i + 1 < len &&
             (isdigit(input_[i + 1]) || input_[i + 1] == '-' ||
              input_[i + 1] == '+'))) {
      string_function.push_back(input_[i]);
      ++i;
      flag_function = 1;
    }
    if (flag_function) {
      if (s21_check_function(string_function) && i < len && input_[i] == '(') {
        flag_function = 0;
        string_function.clear();
      } else {
        // std::cout << "Функция написана неправильно или после нее не идет
        // открывающаяся скобка\n";
        flag = ERROR;
        break;
      }
    }
  }
  return flag;
}

int Model::s21_check_digit() {
  int flag = OK;
  int len = input_.length();
  int flag_number = 0;
  int counter_dot = 0;
  int counter_e = 0;
  int flag_dot_after_e = 0;
  for (int i = 0; i < len && flag; ++i) {
    counter_dot = 0;
    flag_number = 0;
    while ((i < len) &&
           (isdigit(input_[i]) || input_[i] == '.' || input_[i] == 'e' ||
            (i - 1 >= 0 && input_[i - 1] == 'e' &&
             (input_[i] == '+' || input_[i] == '-')))) {
      flag_number = 1;
      if (input_[i] == '.') {
        ++counter_dot;
        if (counter_e > 0) {
          flag_dot_after_e = 1;
        }
      }
      if (input_[i] == 'e') ++counter_e;
      if (flag_dot_after_e == 1 || counter_e > 1 || counter_dot > 1 ||
          (input_[i] == '.' && (i - 1 < 0 || !isdigit(input_[i - 1]) ||
                                i + 1 >= len || !isdigit(input_[i + 1])))) {
        // std::cout << "Неверно введено вещественное число\n";
        flag = ERROR;
        break;
      }
      ++i;
    }
    if (flag_number == 1) {
      --i;
    }
  }
  return flag;
}

int Model::s21_check_order() {
  int flag = OK;
  int len = input_.length();
  std::string special_char = "*/^%";
  std::string char_prev_unary = "(+-*/^%";
  int flag_prev = -1;  // 0 - число, 1 - бинарная операция, 2 - унарная
                       // операция, 3 - функция
  for (int i = 0; i < len; ++i) {
    if (isdigit(input_[i]) || input_[i] == '.' || input_[i] == 'e') {
      if (flag_prev == 0) {
        flag = ERROR;
        break;
      } else {
        while (i < len &&
               (isdigit(input_[i]) || input_[i] == '.' || input_[i] == 'e' ||
                (i - 1 >= 0 && input_[i - 1] == 'e' &&
                 (input_[i] == '+' || input_[i] == '-')))) {
          ++i;
        }
        --i;
        flag_prev = 0;
      }
    }
    if (special_char.find(input_[i]) != std::string::npos) {
      if (flag_prev == 1 || flag_prev == -1) {
        flag = ERROR;
        break;
      } else
        flag_prev = 1;
    }
    if (input_[i] == '+' || input_[i] == '-') {
      if (i == 0 || (i - 1 >= 0 && char_prev_unary.find(input_[i - 1]) !=
                                       std::string::npos)) {
        if (flag_prev == 2) {
          flag = ERROR;
          break;
        } else
          flag_prev = 2;
      } else
        flag_prev = 1;
    }
  }
  if (flag == ERROR || flag_prev == 1 || flag_prev == 2) {
    flag = ERROR;
    // std::cout << "Операции и операнды расположены в неправильном порядке\n";
  }
  return flag;
}

int Model::s21_operation_priority(std::string operation) {
  int result = 0;
  if (operation == "(") {
    result = 1;
  } else if (operation == "+" || operation == "-") {
    result = 2;
  } else if (operation == "*" || operation == "/" || operation == "%") {
    result = 3;
  } else if (operation == "^") {
    result = 4;
  } else if (operation == "o+" || operation == "o-") {
    result = 5;
  } else if (operation == "sin" || operation == "cos" || operation == "tan" ||
             operation == "acos" || operation == "asin" ||
             operation == "atan" || operation == "sqrt" || operation == "ln" ||
             operation == "log") {
    result = 6;
  }
  return result;
}

int Model::s21_reverse_polish_notation() {
  // while (!stack_string.empty()) {
  //     stack_string.pop();
  // }
  output_.clear();
  std::string tmp_string;
  std::string tmp_number;
  std::string tmp_operation;
  int flag = OK;
  int flag_number = 0;     // было ли считано число
  int flag_operation = 0;  // была ли считана операция
  std::string char_prev_unary = "(+-*/^%";
  std::string char_bin = "+-*/^%";
  int len = input_.length();
  for (int i = 0; i < len; ++i) {
    flag_number = 0;
    flag_operation = 0;
    tmp_number.clear();
    while ((i < len) &&
           (isdigit(input_[i]) || input_[i] == '.' || input_[i] == 'e' ||
            (i - 1 >= 0 && input_[i - 1] == 'e' &&
             (input_[i] == '+' || input_[i] == '-')))) {
      flag_number = 1;
      tmp_number.push_back(input_[i]);
      ++i;
    }
    if (flag_number == 1) {
      output_.push_back(tmp_number);
      --i;
    }
    if (input_[i] == '(') {
      tmp_string.clear();
      tmp_string.push_back(input_[i]);
      stack_string.push(tmp_string);
    }
    if (input_[i] == ')') {
      std::string string_in_stack = stack_string.top();
      stack_string.pop();
      tmp_string.clear();
      tmp_string = string_in_stack;
      while (tmp_string != "(" && !stack_string.empty()) {
        output_.push_back(tmp_string);
        string_in_stack = stack_string.top();
        stack_string.pop();
        tmp_string.clear();
        tmp_string = string_in_stack;
      }
      // проверка на правильную скобочную последовательность
      if (tmp_string != "(") {
        flag = ERROR;
        break;
      }
    }
    tmp_operation.clear();
    // перед унарной операцией всегда стоит либо другая операция, либо
    // открывающая скобка, либо вообще ничего
    if ((input_[i] == '+' || input_[i] == '-') &&
        (i == 0 || (i - 1 >= 0 && char_prev_unary.find(input_[i - 1]) !=
                                      std::string::npos))) {
      tmp_operation.push_back('o');
      tmp_operation.push_back(input_[i]);
      flag_operation = 1;
    } else if (char_bin.find(input_[i]) != std::string::npos) {
      tmp_operation.push_back(input_[i]);
      flag_operation = 1;
    }
    // считываем операцию
    if (isalpha(input_[i])) {
      while (isalpha(input_[i]) && i < len) {
        tmp_operation.push_back(input_[i]);
        ++i;
      }
      --i;
      flag_operation = 1;
    }
    if (flag_operation == 1) {
      int priority_tmp_operation = s21_operation_priority(tmp_operation);
      int priority_stack = -1;
      if (!stack_string.empty())
        priority_stack = s21_operation_priority(stack_string.top());
      while (!stack_string.empty() &&
             (priority_stack > priority_tmp_operation ||
              (priority_stack == priority_tmp_operation &&
               tmp_operation != "^"))) {
        std::string string_in_stack = stack_string.top();
        stack_string.pop();
        tmp_string.clear();
        tmp_string = string_in_stack;
        output_.push_back(tmp_string);
        if (!stack_string.empty())
          priority_stack = s21_operation_priority(stack_string.top());
        else
          priority_stack = -1;
      }
      stack_string.push(tmp_operation);
    }
    if (input_[i] == '=') break;
  }
  while (!stack_string.empty()) {
    std::string string_in_stack = stack_string.top();
    stack_string.pop();
    tmp_string.clear();
    tmp_string = string_in_stack;
    // проверка на правильную скобочную последовательность
    if (tmp_string == "(") {
      flag = ERROR;
      break;
    }
    output_.push_back(tmp_string);
  }
  return flag;
}

int Model::s21_calculation_expressions() {
  // while (!stack_number.empty()) {
  //     stack_number.pop();
  // }
  data_ = std::nullopt;
  int flag = OK;
  double left_number = 0;
  double right_number = 0;
  double number = 0;
  double tmp_data = 0;
  for (size_t i = 0; i < output_.size(); ++i) {
    if (isdigit(output_[i][0])) {
      char *nstr;
      stack_number.push(strtod(output_[i].c_str(), &nstr));
    } else {
      if (this->s21_operation_priority(output_[i]) <= 3 || output_[i] == "^" ||
          output_[i] == "%") {
        left_number = stack_number.top();
        stack_number.pop();
        right_number = stack_number.top();
        stack_number.pop();
        if (output_[i] == "-")
          tmp_data = right_number - left_number;
        else if (output_[i] == "+")
          tmp_data = right_number + left_number;
        else if (output_[i] == "*")
          tmp_data = right_number * left_number;
        else if (output_[i] == "/") {
          if (left_number == 0) {
            flag = ERROR;
            break;
          } else
            tmp_data = right_number / left_number;
        } else if (output_[i] == "%")
          tmp_data = fmod(
              (left_number + fmod(right_number, left_number)),
              left_number);  // чтобы для отрицательных right number работало
        else if (output_[i] == "^")
          tmp_data = pow(right_number, left_number);
      } else {  // унарные операции
        number = stack_number.top();
        stack_number.pop();
        if (output_[i] == "o-")
          tmp_data = (-1) * number;
        else if (output_[i] == "o+")
          tmp_data = number;
        else if (output_[i] == "sin")
          tmp_data = sin(number);
        else if (output_[i] == "cos")
          tmp_data = cos(number);
        else if (output_[i] == "tan")
          tmp_data = tan(number);
        else if (output_[i] == "acos")
          tmp_data = acos(number);
        else if (output_[i] == "asin")
          tmp_data = asin(number);
        else if (output_[i] == "atan")
          tmp_data = atan(number);
        else if (output_[i] == "sqrt")
          tmp_data = sqrt(number);
        else if (output_[i] == "ln")
          tmp_data = log(number);
        else if (output_[i] == "log")
          tmp_data = log10(number);
      }
      stack_number.push(tmp_data);
    }
  }
  if (flag) {
    data_ = stack_number.top();
  }
  return flag;
}

int Model::s21_calculate() {
  std::setlocale(LC_NUMERIC, "C");
  int flag = this->s21_check_input();
  if (flag) {
    flag = this->s21_reverse_polish_notation();
    if (flag) {
      flag = this->s21_calculation_expressions();
    }
  }
  return flag;
}