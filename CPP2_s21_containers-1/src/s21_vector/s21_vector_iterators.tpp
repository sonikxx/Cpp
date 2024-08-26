#include "s21_vector.h"

using namespace s21;

// Iterator
template <typename T>
Vector<T>::VectorIterator::VectorIterator(T *arr) {
  this->arr = arr;
}

template <typename T>
T &Vector<T>::VectorIterator::operator*() {
  return *arr;
}

template <typename T>
typename Vector<T>::VectorIterator &Vector<T>::VectorIterator::operator++() {
  arr++;
  return *this;
}

template <typename T>
typename Vector<T>::VectorIterator &Vector<T>::VectorIterator::operator--() {
  arr--;
  return *this;
}

template <typename T>
bool Vector<T>::VectorIterator::operator==(const VectorIterator &other) {
  return arr == other.arr;
}

template <typename T>
bool Vector<T>::VectorIterator::operator!=(const VectorIterator &other) {
  return arr != other.arr;
}

// Const Iterator
template <typename T>
Vector<T>::VectorConstIterator::VectorConstIterator(const T *arr) {
  this->arr = arr;
}

template <typename T>
const T &Vector<T>::VectorConstIterator::operator*() {
  return *arr;
}

template <typename T>
typename Vector<T>::VectorConstIterator &
Vector<T>::VectorConstIterator::operator++() {
  arr++;
  return *this;
}

template <typename T>
typename Vector<T>::VectorConstIterator &
Vector<T>::VectorConstIterator::operator--() {
  arr--;
  return *this;
}

template <typename T>
bool Vector<T>::VectorConstIterator::operator==(
    const VectorConstIterator &other) const {
  return arr == other.arr;
}

template <typename T>
bool Vector<T>::VectorConstIterator::operator!=(
    const VectorConstIterator &other) const {
  return arr != other.arr;
}
