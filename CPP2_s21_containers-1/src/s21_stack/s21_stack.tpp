#include "s21_stack.h"

using namespace s21;

// Member functions
template <typename T>
Stack<T>::Stack() {
  head = nullptr;
}

template <typename T>
Stack<T>::Stack(std::initializer_list<value_type> const &items) {
  head = new Node<T>(*items.begin());
  for (auto it = items.begin() + 1; it != items.end(); it++) {
    Node<T> *tmp = new Node<T>(*it);
    tmp->next = head;
    head = tmp;
  }
}

template <typename T>
Stack<T>::Stack(const Stack &s) {
  if (s.head == nullptr) {
    head = nullptr;
  } else {
    Node<T> *current = s.head;
    Node<T> *newStackHead = new Node<T>(current->data);
    head = newStackHead;
    current = current->next;
    while (current != nullptr) {
      newStackHead->next = new Node<T>(current->data);
      newStackHead = newStackHead->next;
      current = current->next;
    }
  }
}

template <typename T>
Stack<T>::Stack(Stack &&s) {
  head = s.head;
  s.head = nullptr;
}

template <typename T>
Stack<T>::~Stack() {
  while (head != nullptr) {
    Node<T> *tmp = head;
    head = head->next;
    delete tmp;
  }
}

template <typename T>
Stack<T> &Stack<T>::operator=(Stack &&s) {
  if (this != &s) {
    head = s.head;
    s.head = nullptr;
  }

  return *this;
}

// Element access
template <typename T>
typename Stack<T>::const_reference Stack<T>::top() {
  if (head == nullptr) {
    throw std::out_of_range("Stack is empty");
  }
  return head->data;
}

// Capacity
template <typename T>
bool Stack<T>::empty() {
  if (head == nullptr) {
    return true;
  } else {
    return false;
  }
}

template <typename T>
typename Stack<T>::size_type Stack<T>::size() {
  size_type count = 0;
  Node<T> *tmp = head;
  while (tmp != nullptr) {
    count++;
    tmp = tmp->next;
  }
  return count;
}

// Modifiers
template <typename T>
void Stack<T>::push(const_reference value) {
  if (head == nullptr) {
    head = new Node<T>(value);
  } else {
    Node<T> *tmp = new Node<T>(value);
    tmp->next = head;
    head = tmp;
  }
}

template <typename T>
void Stack<T>::pop() {
  if (head == nullptr) {
    throw std::out_of_range("Stack is empty");
  }
  Node<T> *tmp = head;
  head = head->next;
  delete tmp;
}

template <typename T>
void Stack<T>::swap(Stack &other) {
  Node<T> *tmp = head;
  head = other.head;
  other.head = tmp;
}