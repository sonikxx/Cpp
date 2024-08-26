#include "./binary_tree.h"

using namespace s21;

// binary tree methods
template <typename KeyType, typename ValueType>
Tree<KeyType, ValueType>::Tree() {
  root_ = nullptr;
  size_ = 0;
}

template <typename KeyType, typename ValueType>
Tree<KeyType, ValueType>::~Tree() {
  destroy_node(root_);
}

template <typename KeyType, typename ValueType>
void Tree<KeyType, ValueType>::swap(Tree &other) {
  std::swap(root_, other.root_);
  std::swap(size_, other.size_);
  std::swap(end_node, other.end_node);
}

template <typename KeyType, typename ValueType>
bool Tree<KeyType, ValueType>::empty() {
  return (root_ == nullptr);
}

template <typename KeyType, typename ValueType>
typename Tree<KeyType, ValueType>::size_type Tree<KeyType, ValueType>::size() {
  return size_;
}

template <typename KeyType, typename ValueType>
typename Tree<KeyType, ValueType>::size_type
Tree<KeyType, ValueType>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(Node);
}

template <typename KeyType, typename ValueType>
void Tree<KeyType, ValueType>::clear() {
  destroy_node(root_);
  root_ = nullptr;
  size_ = 0;
}

template <typename KeyType, typename ValueType>
bool Tree<KeyType, ValueType>::contains(const KeyType &key) {
  return (bin_tree_find(key) != nullptr);
}

template <typename KeyType, typename ValueType>
void Tree<KeyType, ValueType>::erase(BinIterator pos) {
  if (pos != pos.my_tree_->end())
    const_cast<Tree *>(pos.my_tree_)->bin_remove(pos.node_->key_);
  // else
  //   throw std::runtime_error("BinIterator out of range\n");
}

template <typename KeyType, typename ValueType>
std::pair<typename Tree<KeyType, ValueType>::BinIterator, bool>
Tree<KeyType, ValueType>::bin_insert(KeyType key) {
  ++size_;
  // if (size_ > this->max_size()) {
  //   throw std::runtime_error("Tree is full\n");
  // }
  Node *cur_node = root_;
  Node *res = nullptr;
  if (this->empty()) {
    root_ = new Node(key);
    return (std::make_pair(BinIterator(root_, this), true));
  }
  while (res == nullptr) {
    if (key > cur_node->key_) {
      if (cur_node->right_ == nullptr) {
        cur_node->right_ = new Node(key);
        res = cur_node->right_;
      } else
        cur_node = cur_node->right_;
    }
    if (key < cur_node->key_) {
      if (cur_node->left_ == nullptr) {
        cur_node->left_ = new Node(key);
        res = cur_node->left_;
      } else
        cur_node = cur_node->left_;
    }
    if (key == cur_node->key_) {
      res = cur_node;
      --size_;
      return (std::make_pair(BinIterator(res, this), false));
    }
  }
  return std::make_pair(BinIterator(res, this), true);
}

template <typename KeyType, typename ValueType>
typename Tree<KeyType, ValueType>::Node *
Tree<KeyType, ValueType>::bin_tree_find(KeyType key) {
  Node *cur_node = root_;
  if (this->empty()) return nullptr;
  Node *res = nullptr;
  while (res == nullptr) {
    if (key > cur_node->key_) {
      if (cur_node->right_ == nullptr) break;
      cur_node = cur_node->right_;
    }
    if (key < cur_node->key_) {
      if (cur_node->left_ == nullptr) break;
      cur_node = cur_node->left_;
    }
    if (key == cur_node->key_) {
      res = cur_node;
      break;
    }
  }
  return res;
}

template <typename KeyType, typename ValueType>
void Tree<KeyType, ValueType>::bin_remove(KeyType key) {
  Node *cur_node = this->bin_tree_find(key);
  Node *parent = nullptr;
  if (cur_node != nullptr) {  // такой элемент гарантировано существует
    parent = this->get_parent(cur_node);
    if (cur_node->right_ == nullptr && cur_node->left_ == nullptr) {  // лист
      this->change_child(parent, cur_node, nullptr);
    } else if (cur_node->right_ != nullptr &&
               cur_node->left_ == nullptr) {  // есть правый ребенок
      this->change_child(parent, cur_node, cur_node->right_);
    } else if (cur_node->right_ == nullptr &&
               cur_node->left_ != nullptr) {  // есть левый ребенок
      this->change_child(parent, cur_node, cur_node->left_);
    } else {  // оба ребенка - идем в правое поддерево и ищем там мин элемент
      Node *new_cur = cur_node->right_;
      while (new_cur->left_ != nullptr) {
        new_cur = new_cur->left_;
      }
      ValueType new_value = new_cur->value_;
      KeyType new_key = new_cur->key_;
      this->bin_remove(new_key);
      cur_node->key_ = new_key;
      cur_node->value_ = new_value;
    }
  }
}

// node methods
template <typename KeyType, typename ValueType>
Tree<KeyType, ValueType>::Node::Node() {
  left_ = nullptr;
  right_ = nullptr;
}

template <typename KeyType, typename ValueType>
Tree<KeyType, ValueType>::Node::Node(KeyType key) {
  key_ = key;
  left_ = nullptr;
  right_ = nullptr;
}

// BinIterator methods
template <typename KeyType, typename ValueType>
Tree<KeyType, ValueType>::BinIterator::BinIterator() {
  node_ = nullptr;
  my_tree_ = nullptr;
}

template <typename KeyType, typename ValueType>
Tree<KeyType, ValueType>::BinIterator::BinIterator(Node *node, Tree *tree) {
  node_ = node;
  my_tree_ = tree;
}

template <typename KeyType, typename ValueType>
Tree<KeyType, ValueType>::BinIterator::BinIterator(const BinIterator &other) {
  node_ = other.node_;
  my_tree_ = other.my_tree_;
}

template <typename KeyType, typename ValueType>
typename Tree<KeyType, ValueType>::BinIterator &
Tree<KeyType, ValueType>::BinIterator::operator=(BinIterator &&other) {
  node_ = other.node_;
  my_tree_ = other.my_tree_;
  return *this;
}

template <typename KeyType, typename ValueType>
typename Tree<KeyType, ValueType>::reference
Tree<KeyType, ValueType>::BinIterator::operator*() {
  if (node_ == my_tree_->end().node_)
    throw std::runtime_error("BinIterator out of range\n");
  return reference(node_->value_);
}

template <typename KeyType, typename ValueType>
typename Tree<KeyType, ValueType>::reference
Tree<KeyType, ValueType>::BinIterator::operator++() {
  BinIterator result = const_cast<Tree *>(this->my_tree_)->get_next(node_);
  this->node_ = result.node_;
  if (this->my_tree_->end() == result) {
    return result.node_->value_;
  }
  return *result;
}

template <typename KeyType, typename ValueType>
typename Tree<KeyType, ValueType>::reference
Tree<KeyType, ValueType>::BinIterator::operator--() {
  BinIterator result = const_cast<Tree *>(this->my_tree_)->get_prev(node_);
  this->node_ = result.node_;
  if (result == this->my_tree_->end()) {
    return result.node_->value_;
  }
  // if (this->my_tree_->end() == result) {
  //     return result.node_->value_;
  // }
  return *result;
}

template <typename KeyType, typename ValueType>
bool Tree<KeyType, ValueType>::BinIterator::operator==(
    const BinIterator &other) const {
  return (node_ == other.node_);
}

template <typename KeyType, typename ValueType>
bool Tree<KeyType, ValueType>::BinIterator::operator!=(
    const BinIterator &other) const {
  return (node_ != other.node_);
}

template <typename KeyType, typename ValueType>
typename Tree<KeyType, ValueType>::BinIterator Tree<KeyType, ValueType>::begin()
    const {
  return get_min(root_);
}

template <typename KeyType, typename ValueType>
typename Tree<KeyType, ValueType>::BinIterator Tree<KeyType, ValueType>::end()
    const {
  BinIterator result(const_cast<Node *>(&(this->end_node)),
                     const_cast<Tree *>(this));  // const -> not const
  return result;
}

// const BinIterator methods
template <typename KeyType, typename ValueType>
Tree<KeyType, ValueType>::ConstBinIterator::ConstBinIterator() {
  node_ = nullptr;
  my_tree_ = nullptr;
}

template <typename KeyType, typename ValueType>
Tree<KeyType, ValueType>::ConstBinIterator::ConstBinIterator(const Node *node,
                                                             const Tree *tree) {
  node_ = node;
  my_tree_ = tree;
}

template <typename KeyType, typename ValueType>
Tree<KeyType, ValueType>::ConstBinIterator::ConstBinIterator(
    const ConstBinIterator &other) {
  node_ = other.node_;
  my_tree_ = other.my_tree_;
}

template <typename KeyType, typename ValueType>
Tree<KeyType, ValueType>::ConstBinIterator::ConstBinIterator(
    const BinIterator &other) {
  node_ = other.node_;
  my_tree_ = other.my_tree_;
}

template <typename KeyType, typename ValueType>
typename Tree<KeyType, ValueType>::ConstBinIterator &
Tree<KeyType, ValueType>::ConstBinIterator::operator=(
    ConstBinIterator &&other) {
  node_ = other.node_;
  my_tree_ = other.my_tree_;
  return *this;
}

template <typename KeyType, typename ValueType>
typename Tree<KeyType, ValueType>::const_reference
Tree<KeyType, ValueType>::ConstBinIterator::operator*() {
  if (node_ == my_tree_->end().node_)
    throw std::runtime_error("ConstBinIterator out of range\n");
  return const_reference(node_->value_);
}

template <typename KeyType, typename ValueType>
typename Tree<KeyType, ValueType>::const_reference
Tree<KeyType, ValueType>::ConstBinIterator::operator++() {
  ConstBinIterator result = const_cast<Tree *>(this->my_tree_)->get_next(node_);
  this->node_ = result.node_;
  if (this->my_tree_->cend() == result) {
    return result.node_->value_;
  }
  return *result;
}

template <typename KeyType, typename ValueType>
typename Tree<KeyType, ValueType>::const_reference
Tree<KeyType, ValueType>::ConstBinIterator::operator--() {
  ConstBinIterator result = const_cast<Tree *>(this->my_tree_)->get_prev(node_);
  this->node_ = result.node_;
  if (this->my_tree_->cend() == result) {
    return result.node_->value_;
  }
  return *result;
}

template <typename KeyType, typename ValueType>
bool Tree<KeyType, ValueType>::ConstBinIterator::operator==(
    const ConstBinIterator &other) const {
  return (node_ == other.node_);
}

template <typename KeyType, typename ValueType>
bool Tree<KeyType, ValueType>::ConstBinIterator::operator!=(
    const ConstBinIterator &other) const {
  return (node_ != other.node_);
}

template <typename KeyType, typename ValueType>
typename Tree<KeyType, ValueType>::ConstBinIterator
Tree<KeyType, ValueType>::cbegin() const {
  return get_min(root_);  // вызывается конструктор копирования
}

template <typename KeyType, typename ValueType>
typename Tree<KeyType, ValueType>::ConstBinIterator
Tree<KeyType, ValueType>::cend() const {
  return ConstBinIterator(&(this->end_node), this);  // const -> not const
}

// helper
template <typename KeyType, typename ValueType>
typename Tree<KeyType, ValueType>::Node *Tree<KeyType, ValueType>::get_parent(
    const Node *node) const {
  if (node == &end_node) {
    return get_max(root_).node_;
  }
  if (node == root_) return nullptr;
  Node *parent = nullptr;
  if (node != nullptr) {
    Node *cur_node = root_;
    while (cur_node != node) {
      parent = cur_node;
      if (cur_node->key_ < node->key_)
        cur_node = cur_node->right_;
      else
        cur_node = cur_node->left_;
    }
  }
  return parent;
}

template <typename KeyType, typename ValueType>
void Tree<KeyType, ValueType>::change_child(
    Tree<KeyType, ValueType>::Node *parent,
    Tree<KeyType, ValueType>::Node *cur_node,
    Tree<KeyType, ValueType>::Node *new_child) {
  if (parent == nullptr) {
    root_ = new_child;
  } else {
    if (cur_node == parent->right_) parent->right_ = new_child;
    if (cur_node == parent->left_) parent->left_ = new_child;
  }
  delete cur_node;
  --size_;
}

template <typename KeyType, typename ValueType>
typename Tree<KeyType, ValueType>::BinIterator
Tree<KeyType, ValueType>::get_min(Tree<KeyType, ValueType>::Node *node) const {
  // if (node == nullptr)
  //     return this->end();
  BinIterator min;
  while (node != nullptr && node->left_ != nullptr) {
    node = node->left_;
  }
  min.node_ = node;
  min.my_tree_ = this;
  return min;
}

template <typename KeyType, typename ValueType>
typename Tree<KeyType, ValueType>::BinIterator
Tree<KeyType, ValueType>::get_max(Node *node) const {
  // if (node == nullptr)
  //     return this->end();
  BinIterator max;
  while (node != nullptr && node->right_ != nullptr) {
    node = node->right_;
  }
  max.node_ = node;
  max.my_tree_ = this;
  return max;
}

template <typename KeyType, typename ValueType>
typename Tree<KeyType, ValueType>::BinIterator
Tree<KeyType, ValueType>::get_next(const Node *node) {
  if (node == nullptr || node == this->get_max(root_).node_) return this->end();
  if (node->right_ != nullptr) return get_min(node->right_);
  Node *parent = get_parent(node);
  while (parent != nullptr && parent->right_ == node) {
    node = parent;
    parent = get_parent(node);
  }
  return BinIterator(parent, this);
}

template <typename KeyType, typename ValueType>
typename Tree<KeyType, ValueType>::BinIterator
Tree<KeyType, ValueType>::get_prev(const Node *node) {
  if (node == nullptr || node == this->get_min(root_).node_) {
    return this->end();
  }
  if (node->left_ != nullptr) return get_max(node->left_);
  Node *parent = get_parent(node);
  while (parent != nullptr && parent->left_ == node) {
    node = parent;
    parent = get_parent(node);
  }
  return BinIterator(parent, this);
}

template <typename KeyType, typename ValueType>
void Tree<KeyType, ValueType>::print() {
  rec_print(root_);
  std::cout << "\n";
}

template <typename KeyType, typename ValueType>
void Tree<KeyType, ValueType>::rec_print(Node *node) {
  if (node != nullptr) {
    rec_print(node->left_);
    std::cout << node->key_ << " ";
    rec_print(node->right_);
  }
}

template <typename KeyType, typename ValueType>
void Tree<KeyType, ValueType>::destroy_node(Node *node) {
  if (node != nullptr) {
    destroy_node(node->left_);
    destroy_node(node->right_);
    delete node;
  }
}