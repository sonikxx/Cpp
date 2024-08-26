#if !defined(BINARY_TREE)
#define BINARY_TREE

#include <cstdint>
#include <exception>
#include <iostream>
#include <limits>

// TODO проверить тесты на утечки
// TODO собрать тесты в один файл
// TODO обьединить makefile

namespace s21 {

template <typename KeyType, typename ValueType>
class Tree {
 protected:
  class Node;
  class BinIterator;
  class ConstBinIterator;

 public:
  using key_type = KeyType;
  using value_type = ValueType;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = BinIterator;
  using const_iterator = ConstBinIterator;
  using size_type = size_t;

 protected:
  class Node {
   public:
    KeyType key_;
    ValueType value_;
    Node *left_;
    Node *right_;
    Node();
    Node(KeyType key);
  };
  class BinIterator {
    friend class Tree;

   public:
    Node *node_;
    const Tree *my_tree_;
    BinIterator();
    BinIterator(Node *node, Tree *tree);
    BinIterator(const BinIterator &other);
    reference operator*();
    reference operator++();
    reference operator--();
    BinIterator &operator=(BinIterator &&other);
    bool operator==(const BinIterator &other) const;
    bool operator!=(const BinIterator &other) const;
  };

  class ConstBinIterator {  // итератор на элемент, который нельзя изменить
    friend class Tree;

   public:
    const Node *node_;
    const Tree *my_tree_;
    ConstBinIterator();
    ConstBinIterator(const Node *node, const Tree *tree);
    ConstBinIterator(const ConstBinIterator &other);
    ConstBinIterator(const BinIterator &other);
    const_reference operator*();
    const_reference operator++();
    const_reference operator--();
    ConstBinIterator &operator=(ConstBinIterator &&other);
    bool operator==(const ConstBinIterator &other) const;
    bool operator!=(const ConstBinIterator &other) const;
  };
  Node *root_;
  Node end_node;  // for iterator end()
  size_type size_;
  std::pair<BinIterator, bool> bin_insert(KeyType key);
  Node *bin_tree_find(KeyType key);
  void bin_remove(KeyType key);
  BinIterator get_min(Node *node) const;
  BinIterator get_max(Node *node) const;
  BinIterator get_next(const Node *node);
  BinIterator get_prev(const Node *node);
  Node *get_parent(const Node *node) const;
  void change_child(Node *parent, Node *cur_node, Node *new_child);
  void destroy_node(Node *node);
  void print();
  void rec_print(Node *node);

 public:
  Tree();
  ~Tree();
  void swap(Tree &other);
  bool empty();
  size_type size();
  size_type max_size();
  void clear();
  void erase(BinIterator pos);
  bool contains(const KeyType &key);
  BinIterator begin() const;
  BinIterator end() const;
  ConstBinIterator cbegin() const;
  ConstBinIterator cend() const;
};

}  // namespace s21
#include "./binary_tree.tpp"

#endif  // BINARY_TREE