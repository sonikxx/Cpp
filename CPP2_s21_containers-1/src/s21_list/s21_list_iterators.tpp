#include "s21_list.h"

using namespace s21;

template <typename T>
List<T>::ListIterator::ListIterator(ListNode<T> *node) {
  currentNode = node;
}

template <typename T>
T &List<T>::ListIterator::operator*() {
  return currentNode->data;
}

template <typename T>
typename List<T>::ListIterator &List<T>::ListIterator::operator++() {
  currentNode = currentNode->next;
  return *this;
}

template <typename T>
typename List<T>::ListIterator &List<T>::ListIterator::operator--() {
  currentNode = currentNode->prev;
  return *this;
}

template <typename T>
bool List<T>::ListIterator::operator==(const ListIterator &other) {
  return currentNode == other.currentNode;
}

template <typename T>
bool List<T>::ListIterator::operator!=(const ListIterator &other) {
  return currentNode != other.currentNode;
}

template <typename T>
List<T>::ListConstIterator::ListConstIterator(const ListNode<T> *node)
    : currentNode(node) {}

template <typename T>
const T &List<T>::ListConstIterator::operator*() {
  return currentNode->data;
}

template <typename T>
typename List<T>::ListConstIterator &List<T>::ListConstIterator::operator++() {
  currentNode = currentNode->next;
  return *this;
}

template <typename T>
typename List<T>::ListConstIterator &List<T>::ListConstIterator::operator--() {
  currentNode = currentNode->prev;
  return *this;
}

template <typename T>
bool List<T>::ListConstIterator::operator==(
    const ListConstIterator &other) const {
  return currentNode == other.currentNode;
}

template <typename T>
bool List<T>::ListConstIterator::operator!=(
    const ListConstIterator &other) const {
  return currentNode != other.currentNode;
}
