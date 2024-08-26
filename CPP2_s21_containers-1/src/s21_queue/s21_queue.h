#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

#include "queue_node.tpp"

namespace s21 {
template <typename T>
class Queue {
 public:
  Node<T> *head;
  Node<T> *tail;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  // Member functions
  Queue();
  Queue(std::initializer_list<value_type> const &items);
  Queue(const Queue<T> &q);
  Queue(Queue<T> &&q);
  ~Queue();
  Queue<T> &operator=(Queue<T> &&q);

  // Element access
  const_reference front();
  const_reference back();

  // Capacity
  bool empty();
  size_type size();

  // Modifiers
  void push(const_reference value);
  void pop();
  void swap(Queue<T> &other);
};

#include "s21_queue.tpp"
}  // namespace s21

#endif  // S21_QUEUE_H