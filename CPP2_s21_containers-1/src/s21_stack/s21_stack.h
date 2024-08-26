#ifndef S21_STACK_H_
#define S21_STACK_H_

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

#include "../s21_queue/queue_node.tpp"

namespace s21 {
template <typename T>
class Stack {
 public:
  Node<T> *head;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  // Member functions
  Stack();
  Stack(std::initializer_list<value_type> const &items);
  Stack(const Stack &s);
  Stack(Stack &&s);
  ~Stack();
  Stack &operator=(Stack &&s);

  // Element access
  const_reference top();

  // Capacity
  bool empty();
  size_type size();

  // Modifiers
  void push(const_reference value);
  void pop();
  void swap(Stack &other);
};

#include "s21_stack.tpp"
}  // namespace s21

#endif  // S21_STACK_H_