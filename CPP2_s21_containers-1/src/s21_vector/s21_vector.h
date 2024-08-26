#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <stdexcept>

namespace s21 {

template <typename T>
class Vector {
  class VectorIterator {
    friend class Vector;

   private:
    T *arr;

   public:
    VectorIterator(T *arr);
    T &operator*();
    VectorIterator &operator++();
    VectorIterator &operator--();
    bool operator==(const VectorIterator &other);
    bool operator!=(const VectorIterator &other);
  };

  class VectorConstIterator {
    friend class Vector;

   private:
    const T *arr;

   public:
    VectorConstIterator(const T *arr);
    const T &operator*();
    VectorConstIterator &operator++();
    VectorConstIterator &operator--();
    bool operator==(const VectorConstIterator &other) const;
    bool operator!=(const VectorConstIterator &other) const;
  };

 private:
  T *arr;
  size_t m_size;
  size_t m_capacity;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = VectorIterator;
  using const_iterator = VectorConstIterator;
  using size_type = size_t;

  // Member functions
  Vector();
  Vector(size_type n);
  Vector(std::initializer_list<value_type> const &items);
  Vector(const Vector<T> &l);
  Vector(Vector<T> &&l);
  ~Vector<T>();
  Vector<T> &operator=(Vector<T> &&l);

  // Element access
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  T *data();

  // Iterators
  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  // Capacity
  bool empty();
  size_type size();
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();

  // Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(Vector<T> &other);
};

#include "s21_vector.tpp"
#include "s21_vector_iterators.tpp"

}  // namespace s21

#endif  // S21_VECTOR_H