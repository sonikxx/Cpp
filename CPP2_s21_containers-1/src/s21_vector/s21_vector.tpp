#include "s21_vector.h"

using namespace s21;

// Member functions
template <typename T>
Vector<T>::Vector() {
  arr = nullptr;
  m_size = 0;
  m_capacity = 0;
}

template <typename T>
Vector<T>::Vector(size_type n) {
  if (n) {
    arr = new T[n];
    m_size = n;
    m_capacity = n;
  } else {
    arr = nullptr;
    m_size = 0;
    m_capacity = 0;
  }
}

template <typename T>
Vector<T>::Vector(std::initializer_list<value_type> const &items) {
  arr = new T[items.size()];
  int i = 0;
  for (auto it = items.begin(); it != items.end(); it++) {
    arr[i] = *it;
    i++;
  }
  m_size = items.size();
  m_capacity = items.size();
}

template <typename T>
Vector<T>::Vector(const Vector<T> &l) {
  arr = new T[l.m_size];
  m_size = l.m_size;
  m_capacity = l.m_capacity;
  for (size_t i = 0; i < m_size; ++i) {
    arr[i] = l.arr[i];
  }
}

template <typename T>
Vector<T>::Vector(Vector<T> &&l) {
  arr = l.arr;
  m_size = l.m_size;
  m_capacity = l.m_capacity;
  l.arr = nullptr;
  l.m_size = 0;
  l.m_capacity = 0;
}

template <typename T>
Vector<T>::~Vector() {
  delete[] arr;
  arr = nullptr;
  m_size = 0;
  m_capacity = 0;
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector<T> &&l) {
  if (this != &l) {
    delete[] arr;
    arr = l.arr;
    m_size = l.m_size;
    m_capacity = l.m_capacity;
    l.arr = nullptr;
    l.m_size = 0;
    l.m_capacity = 0;
  }
  return *this;
}

// Element access
template <typename T>
T &Vector<T>::at(size_type i) {
  if (i < m_size) {
    return arr[i];
  } else {
    throw std::out_of_range("Index out of range");
  }
}

template <typename T>
T &Vector<T>::operator[](size_type i) {
  if (i < m_size) {
    return arr[i];
  } else {
    throw std::out_of_range("Index out of range");
  }
}

template <typename T>
const T &Vector<T>::front() {
  if (m_size) {
    return arr[0];
  } else {
    throw std::out_of_range("Vector is empty");
  }
}

template <typename T>
const T &Vector<T>::back() {
  if (m_size) {
    return arr[m_size - 1];
  } else {
    throw std::out_of_range("Vector is empty");
  }
}

template <typename T>
T *Vector<T>::data() {
  return arr;
}

// Capacity
template <typename T>
bool Vector<T>::empty() {
  return (m_size == 0);
}

template <typename T>
size_t Vector<T>::size() {
  return m_size;
}

template <typename T>
size_t Vector<T>::max_size() {
  return std::numeric_limits<size_t>::max() / sizeof(value_type);
}

template <typename T>
size_t Vector<T>::capacity() {
  return m_capacity;
}

template <typename T>
void Vector<T>::reserve(size_t size) {
  if (size > m_capacity) {
    T *buff = new T[size];
    for (size_t i = 0; i < m_size; ++i) {
      buff[i] = std::move(arr[i]);
    }
    delete[] arr;
    arr = buff;
    m_capacity = size;
  }
}

template <typename T>
void Vector<T>::shrink_to_fit() {
  if (m_size < m_capacity) {
    T *buff = new T[m_size];
    for (size_t i = 0; i < m_size; ++i) {
      buff[i] = std::move(arr[i]);
    }
    delete[] arr;
    arr = buff;
    m_capacity = m_size;
  }
}

// Modifiers
template <typename T>
void Vector<T>::clear() {
  m_size = 0;
}

template <typename T>
void Vector<T>::push_back(const T &v) {
  if (m_size == m_capacity) {
    reserve(m_size * 2);
  }
  arr[m_size++] = v;
}

template <typename T>
void Vector<T>::pop_back() {
  if (m_size) {
    m_size--;
  } else {
    throw std::out_of_range("Vector is empty");
  }
}

template <typename T>
void Vector<T>::swap(Vector<T> &other) {
  T *buff = arr;
  arr = other.arr;
  other.arr = buff;
  size_t buff_size = m_size;
  m_size = other.m_size;
  other.m_size = buff_size;

  size_t buff_capacity = m_capacity;
  m_capacity = other.m_capacity;
  other.m_capacity = buff_capacity;
}

template <typename T>
typename Vector<T>::VectorIterator Vector<T>::insert(VectorIterator pos,
                                                     const T &value) {
  size_t index = &(*pos) - arr;
  if (m_size == m_capacity) {
    reserve(m_size * 2);
  }
  for (size_t i = m_size; i > index; --i) {
    arr[i] = std::move(arr[i - 1]);
  }
  arr[index] = value;
  ++m_size;
  return VectorIterator(arr + index);
}

template <typename T>
void Vector<T>::erase(iterator pos) {
  size_t index = &(*pos) - arr;
  for (size_t i = index; i < m_size - 1; ++i) {
    arr[i] = std::move(arr[i + 1]);
  }
  --m_size;
}

// Iterators
template <typename T>
typename Vector<T>::iterator Vector<T>::begin() {
  return iterator(arr);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end() {
  return iterator(arr + m_size);
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::cbegin() const {
  return const_iterator(arr);
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::cend() const {
  return const_iterator(arr + m_size);
}
