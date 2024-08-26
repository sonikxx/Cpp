#ifndef S21_LIST_H
#define S21_LIST_H

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <stdexcept>

#include "list_node.tpp"

namespace s21 {

template <typename T>
class List {
  class ListIterator {
    friend class List;

   private:
    ListNode<T> *currentNode;

   public:
    ListIterator(ListNode<T> *node);
    T &operator*();
    ListIterator &operator++();
    ListIterator &operator--();
    bool operator==(const ListIterator &other);
    bool operator!=(const ListIterator &other);
  };

  class ListConstIterator {
    friend class List;

   private:
    const ListNode<T> *currentNode;

   public:
    ListConstIterator(const ListNode<T> *node);
    const T &operator*();
    ListConstIterator &operator++();
    ListConstIterator &operator--();
    bool operator==(const ListConstIterator &other) const;
    bool operator!=(const ListConstIterator &other) const;
  };

 public:
  ListNode<T> *head;
  ListNode<T> *tail;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;

  // Member functions
  List();
  List(size_type n);
  List(std::initializer_list<value_type> const &items);
  List(const List<T> &l);
  List(List<T> &&l);
  ~List<T>();
  List<T> &operator=(List<T> &&l);

  // Element access
  const_reference front();
  const_reference back();

  // Iterators
  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  // Capacity
  bool empty();
  size_type size();
  size_type max_size();

  // Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(List<T> &other);
  void merge(List<T> &other);
  void splice(iterator pos, List<T> &other);
  void reverse();
  void unique();
  void sort();
};

#include "s21_list.tpp"
#include "s21_list_iterators.tpp"
}  // namespace s21

#endif  // S21_LIST_H