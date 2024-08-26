#include "./s21_map.h"

using namespace s21;

template <typename K, typename T>
map<K, T>::map(std::initializer_list<value_type> const &items) {
  for (auto it = items.begin(); it != items.end(); ++it) {
    this->insert(*it);
  }
}

template <typename K, typename T>
map<K, T>::map(const map &m) {
  for (auto it = m.cbegin(); it != m.cend(); ++it) {
    this->insert(*it);
  }
}

template <typename K, typename T>
map<K, T>::map(map &&m) {
  this->swap(m);
  m.size_ = 0;
  m.root_ = nullptr;
}

template <typename K, typename T>
map<K, T> &map<K, T>::operator=(map &&m) {
  this->swap(m);
  return *this;
}

template <typename K, typename T>
typename map<K, T>::mapped_type &map<K, T>::at(const key_type &key) {
  typename Tree<K, std::pair<K, T>>::Node *result = this->bin_tree_find(key);
  if (result == nullptr) {
    throw std::out_of_range("Key not found");
  }
  return result->value_.second;
}

template <typename K, typename T>
typename map<K, T>::mapped_type &map<K, T>::operator[](const key_type &key) {
  typename Tree<K, std::pair<K, T>>::Node *result = this->bin_tree_find(key);
  if (result == nullptr) {
    this->insert({key, mapped_type()});  // для mapped_type вызывается
                                         // конструктор по умолчанию
    result = this->bin_tree_find(key);
  }
  return result->value_.second;
}

template <typename K, typename T>
void map<K, T>::merge(map &other) {
  map<K, T> tmp = other;
  for (auto it = other.begin(); it != other.end(); ++it) {
    if (this->insert(*it).second == true) {
      iterator tmp_it = tmp.find(it.node_->key_);
      tmp.erase(tmp_it);
    }
  }
  other.swap(tmp);
}

template <typename K, typename T>
std::pair<typename map<K, T>::iterator, bool> map<K, T>::insert(
    const key_type &key, const mapped_type &obj) {
  std::pair<iterator, bool> result = this->bin_insert(key);
  if (result.second == true)
    result.first.node_->value_ = std::make_pair(key, obj);
  return result;
}

template <typename K, typename T>
std::pair<typename map<K, T>::iterator, bool> map<K, T>::insert(
    const value_type &value) {
  return this->insert(value.first, value.second);
}

template <typename K, typename T>
std::pair<typename map<K, T>::iterator, bool> map<K, T>::insert_or_assign(
    const key_type &key, const mapped_type &obj) {
  std::pair<iterator, bool> result = this->bin_insert(key);
  result.first.node_->value_ = std::make_pair(key, obj);
  return result;
}

template <typename K, typename T>
typename map<K, T>::iterator map<K, T>::find(key_type &key) {
  typename Tree<K, std::pair<K, T>>::Node *result = this->bin_tree_find(key);
  return iterator(result, this);
}