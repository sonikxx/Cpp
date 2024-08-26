#include "./s21_set.h"

using namespace s21;

template <typename KeyType>
set<KeyType>::set(std::initializer_list<value_type> const &items) {
  for (auto it = items.begin(); it != items.end(); ++it) {
    this->insert(*it);
  }
}

template <typename KeyType>
set<KeyType>::set(const set &s) {
  for (auto it = s.cbegin(); it != s.cend(); ++it) {
    this->insert(*it);
  }
}

// && ссылка на обьект, который умрет, после вызова этой функции, временный
// обьект, r-value ссылка
template <typename KeyType>
set<KeyType>::set(set &&s) {
  this->swap(s);
  s.size_ = 0;  // для корректной работы конструктора
  s.root_ = nullptr;
}

template <typename KeyType>
set<KeyType> &set<KeyType>::operator=(set &&s) {
  this->swap(s);
  return *this;
}

template <typename KeyType>
void set<KeyType>::merge(set &other) {
  set<KeyType> tmp_set(other);
  for (auto it = other.begin(); it != other.end(); ++it) {
    if (this->insert(*it).second == true) {
      tmp_set.erase(tmp_set.find(it.node_->key_));
    }
  }
  other.swap(tmp_set);
}

template <typename KeyType>
std::pair<typename set<KeyType>::iterator, bool> set<KeyType>::insert(
    const value_type &value) {
  std::pair<iterator, bool> res = this->bin_insert(value);
  res.first.node_->value_ = value;
  return res;
}

template <typename KeyType>
typename set<KeyType>::iterator set<KeyType>::find(const key_type &key) {
  typename set<KeyType>::Node *result = this->bin_tree_find(key);
  if (result == nullptr) {
    return this->end();
  }
  return iterator(result, this);
}

template <typename KeyType>
bool set<KeyType>::contains(const key_type &key) {
  typename set<KeyType>::Node *result = this->bin_tree_find(key);
  if (result == nullptr) {
    return false;
  }
  return true;
}