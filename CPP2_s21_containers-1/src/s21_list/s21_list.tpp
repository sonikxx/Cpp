#include "s21_list.h"
using namespace s21;

// Member functions
// Создать пустой список (конструктор по умолчанию)
template <typename T>
List<T>::List() {
  head = nullptr;
  tail = nullptr;
}

// Создать список заданного размера
template <typename T>
List<T>::List(size_type n) {
  if (n == 0) {
    head = nullptr;
    tail = nullptr;
  } else {
    head = new ListNode<T>(0);
    tail = head;
    for (size_t i = 1; i < n; i++) {
      tail->next = new ListNode<T>(0);
      tail->next->prev = tail;
      tail = tail->next;
    }
    tail->next = nullptr;
  }
}

// Создать список из std::initializer_list
template <typename T>
List<T>::List(std::initializer_list<value_type> const &items) {
  head = new ListNode<T>(*items.begin());
  tail = head;
  for (auto it = items.begin() + 1; it != items.end(); it++) {
    tail->next = new ListNode<T>(*it);
    tail->next->prev = tail;
    tail = tail->next;
  }
  tail->next = nullptr;
}

// Создать копию списка
template <typename T>
List<T>::List(const List<T> &l) {
  if (l.head == nullptr) {
    head = nullptr;
    tail = nullptr;
  } else {
    head = new ListNode<T>(l.head->data);
    tail = head;
    ListNode<T> *tmp = l.head->next;
    while (tmp != nullptr) {
      tail->next = new ListNode<T>(tmp->data);
      tail->next->prev = tail;
      tail = tail->next;
      tmp = tmp->next;
    }
    tail->next = nullptr;
  }
}

// Конструктор перемещения
template <typename T>
List<T>::List(List<T> &&l) {
  head = l.head;
  tail = l.tail;
  l.head = nullptr;
  l.tail = nullptr;
}

// Деструктор
template <typename T>
List<T>::~List<T>() {
  clear();
}

// Перегруженный оператор присваивания для перемещения
template <typename T>
List<T> &List<T>::operator=(List<T> &&l) {
  clear();
  head = l.head;
  tail = l.tail;
  l.head = nullptr;
  l.tail = nullptr;
  return *this;
}

// Element access
// Доступ к первому элементу
template <typename T>
typename List<T>::const_reference List<T>::front() {
  if (head == nullptr) {
    throw std::out_of_range("List is empty");
  }
  return head->data;
}

// Доступ к последнему элементу
template <typename T>
typename List<T>::const_reference List<T>::back() {
  if (tail == nullptr) {
    throw std::out_of_range("List is empty");
  }
  return tail->data;
}

// List Iterators
template <typename T>
typename List<T>::iterator List<T>::begin() {
  return iterator(head);
}

template <typename T>
typename List<T>::iterator List<T>::end() {
  return iterator(tail);
}

template <typename T>
typename List<T>::const_iterator List<T>::cbegin() const {
  return const_iterator(head);
}

template <typename T>
typename List<T>::const_iterator List<T>::cend() const {
  return const_iterator(tail);
}

// Capacity
// Проверка на пустой список
template <typename T>
bool List<T>::empty() {
  if (head == nullptr) {
    return true;
  } else {
    return false;
  }
}

// Количество элементов в списке
template <typename T>
typename List<T>::size_type List<T>::size() {
  size_type count = 0;
  ListNode<T> *tmp = head;
  while (tmp != nullptr) {
    count++;
    tmp = tmp->next;
  }
  return count;
}

// Максимальное количество элементов в списке
template <typename T>
typename List<T>::size_type List<T>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(ListNode<T>);
}

// Modifiers
// Очистить список
template <typename T>
void List<T>::clear() {
  ListNode<T> *tmp = head;
  while (tmp != nullptr) {
    head = head->next;
    delete tmp;
    tmp = head;
  }
}

// Вставить элемент в позицию pos
template <typename T>
typename List<T>::iterator List<T>::insert(iterator pos,
                                           const_reference value) {
  ListNode<T> *tmp = pos.currentNode;
  if (tmp == head) {
    head = new ListNode<T>(value);
    head->next = tmp;
    tmp->prev = head;
  } else if (tmp == tail) {
    tail->next = new ListNode<T>(value);
    tail->next->prev = tail;
    tail = tail->next;
  } else {
    tmp->prev->next = new ListNode<T>(value);
    tmp->prev->next->prev = tmp->prev;
    tmp->prev->next->next = tmp;
    tmp->prev = tmp->prev->next;
  }
  return iterator(tmp->prev);
}

// Удалить элемент в позиции pos
template <typename T>
void List<T>::erase(iterator pos) {
  ListNode<T> *tmp = pos.currentNode;
  if (tmp == head) {
    head = head->next;
    head->prev = nullptr;
  } else if (tmp == tail) {
    tail = tail->prev;
    tail->next = nullptr;
  }
  delete tmp;
}

// Добавить элемент в конец списка
template <typename T>
void List<T>::push_back(const_reference value) {
  if (head == nullptr) {
    head = new ListNode<T>(value);
    tail = head;
  } else {
    tail->next = new ListNode<T>(value);
    tail = tail->next;
  }
}

// Удалить последний элемент
template <typename T>
void List<T>::pop_back() {
  if (head == tail && head == nullptr) {
    throw std::out_of_range("List is empty");
  } else if (head == tail) {
    delete head;
    head = nullptr;
    tail = nullptr;
  } else {
    ListNode<T> *tmp = head;
    while (tmp->next != tail) {
      tmp = tmp->next;
    }
    delete tail;
    tail = tmp;
    tail->next = nullptr;
  }
}

// Добавить элемент в начало списка
template <typename T>
void List<T>::push_front(const_reference value) {
  if (head == nullptr) {
    head = new ListNode<T>(value);
    tail = head;
  } else {
    head->prev = new ListNode<T>(value);
    head->prev->next = head;
    head = head->prev;
  }
}

// Удалить первый элемент
template <typename T>
void List<T>::pop_front() {
  if (head == tail && head == nullptr) {
    throw std::out_of_range("List is empty");
  }
  if (head == tail) {
    delete head;
    head = nullptr;
    tail = nullptr;
  } else {
    ListNode<T> *tmp = head;
    head = head->next;
    head->prev = nullptr;
    delete tmp;
  }
}

// Обмен содержимого списков
template <typename T>
void List<T>::swap(List<T> &other) {
  ListNode<T> *tmp_head = head;
  ListNode<T> *tmp_tail = tail;
  head = other.head;
  tail = other.tail;
  other.head = tmp_head;
  other.tail = tmp_tail;
}

// Слияние двух отсортированных списков
template <typename T>
void List<T>::merge(List<T> &other) {
  List<T> result;
  ListNode<T> *current = head;
  ListNode<T> *otherCurrent = other.head;

  while (current != nullptr && otherCurrent != nullptr) {
    if (current->data < otherCurrent->data) {
      result.push_back(current->data);
      current = current->next;
    } else {
      result.push_back(otherCurrent->data);
      otherCurrent = otherCurrent->next;
    }
  }

  while (current != nullptr) {
    result.push_back(current->data);
    current = current->next;
  }
  while (otherCurrent != nullptr) {
    result.push_back(otherCurrent->data);
    otherCurrent = otherCurrent->next;
  }

  this->swap(result);
}

// Переместить элементы из other в текущий список
template <typename T>
void List<T>::splice(iterator pos, List<T> &other) {
  if (other.head == other.tail) {
    return;
  }
  ListNode<T> *tmp = other.head;
  while (tmp != nullptr) {
    insert(pos, tmp->data);
    tmp = tmp->next;
  }
}

// Перевернуть список
template <typename T>
void List<T>::reverse() {
  ListNode<T> *tmp = head;
  while (tmp != nullptr) {
    ListNode<T> *tmp2 = tmp->next;
    tmp->next = tmp->prev;
    tmp->prev = tmp2;
    tmp = tmp->prev;
  }
  tmp = head;
  head = tail;
  tail = tmp;
}

// Удалить дубликаты
template <typename T>
void List<T>::unique() {
  ListNode<T> *current = head;
  while (current != nullptr) {
    ListNode<T> *runner = current;
    while (runner->next != nullptr) {
      if (current->data == runner->next->data) {
        ListNode<T> *duplicate = runner->next;
        runner->next = runner->next->next;
        if (runner->next != nullptr) {
          runner->next->prev = runner;
        }
        if (duplicate == tail) {
          tail = runner;
        }
        delete duplicate;
      } else {
        runner = runner->next;
      }
    }
    current = current->next;
  }
}

// Сортировать список
template <typename T>
void List<T>::sort() {
  ListNode<T> *tmp = head;
  while (tmp != nullptr) {
    ListNode<T> *tmp2 = tmp->next;
    while (tmp2 != nullptr) {
      if (tmp->data > tmp2->data) {
        T tmp_data = tmp->data;
        tmp->data = tmp2->data;
        tmp2->data = tmp_data;
      }
      tmp2 = tmp2->next;
    }
    tmp = tmp->next;
  }
}
