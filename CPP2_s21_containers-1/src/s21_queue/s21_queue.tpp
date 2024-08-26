#include "s21_queue.h"

using namespace s21;

// Member functions
// Конструктор по умолчанию
template <typename T>
Queue<T>::Queue() {
  head = nullptr;
  tail = nullptr;
}

// Конструктор с параметрами
template <typename T>
Queue<T>::Queue(std::initializer_list<value_type> const &items) {
  head = new Node<T>(*items.begin());
  tail = head;
  for (auto it = items.begin() + 1; it != items.end(); it++) {
    tail->next = new Node<T>(*it);
    tail = tail->next;
  }
}

// Конструктор копирования
template <typename T>
Queue<T>::Queue(const Queue<T> &q) {
  if (q.head == nullptr) {
    head = nullptr;
    tail = nullptr;
  } else {
    head = new Node<T>(q.head->data);
    tail = head;
    Node<T> *tmp = q.head->next;
    while (tmp != nullptr) {
      tail->next = new Node<T>(tmp->data);
      tail = tail->next;
      tmp = tmp->next;
    }
  }
}

// Конструктор перемещения
template <typename T>
Queue<T>::Queue(Queue<T> &&q) {
  head = q.head;
  tail = q.tail;
  q.head = nullptr;
  q.tail = nullptr;
}

// Деструктор
template <typename T>
Queue<T>::~Queue() {
  while (head != nullptr) {
    Node<T> *tmp = head;
    head = head->next;
    delete tmp;
  }
}

// Перегруженный оператор перемещения
template <typename T>
Queue<T> &Queue<T>::operator=(Queue<T> &&q) {
  head = q.head;
  tail = q.tail;
  q.head = nullptr;
  q.tail = nullptr;
  return *this;
}

// Element access
// Доступ к первому элементу
template <typename T>
typename Queue<T>::const_reference Queue<T>::front() {
  if (head == nullptr) {
    throw std::out_of_range("Queue is empty");
  }
  return head->data;
}

// Доступ к последнему элементу
template <typename T>
typename Queue<T>::const_reference Queue<T>::back() {
  if (tail == nullptr) {
    throw std::out_of_range("Queue is empty");
  }
  return tail->data;
}

// Capacity
// Пуст ли контейнер
template <typename T>
bool Queue<T>::empty() {
  if (head == nullptr) {
    return true;
  } else {
    return false;
  }
}

// Размер контейнера
template <typename T>
typename Queue<T>::size_type Queue<T>::size() {
  size_type count = 0;
  Node<T> *tmp = head;
  while (tmp != nullptr) {
    count++;
    tmp = tmp->next;
  }
  return count;
}

// Modifiers
// Вставка элемента в конец
template <typename T>
void Queue<T>::push(const_reference value) {
  if (head == nullptr) {
    head = new Node<T>(value);
    tail = head;
  } else {
    tail->next = new Node<T>(value);
    tail = tail->next;
  }
}

// Удаление элемента с начала
template <typename T>
void Queue<T>::pop() {
  if (head == nullptr) {
    throw std::out_of_range("Queue is empty");
  }
  if (head == tail) {
    delete head;
    head = nullptr;
    tail = nullptr;
  } else {
    Node<T> *tmp = head;
    head = head->next;
    delete tmp;
  }
}

// Обмен содержимого двух контейнеров
template <typename T>
void Queue<T>::swap(Queue<T> &other) {
  Node<T> *tmp_head = head;
  Node<T> *tmp_tail = tail;
  head = other.head;
  tail = other.tail;
  other.head = tmp_head;
  other.tail = tmp_tail;
}