#if !defined(SET)
#define SET

#include "../binary_tree.h"

namespace s21 {
template <typename KeyType>
class set : public Tree<KeyType, KeyType> {
 public:
  using key_type = KeyType;
  using value_type = KeyType;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename Tree<KeyType, KeyType>::BinIterator;
  using const_iterator = typename Tree<KeyType, KeyType>::ConstBinIterator;
  using size_type = size_t;

  set() {}  // вызовется родительский конструктор
  set(std::initializer_list<value_type> const &items);
  set(const set &s);
  set(set &&s);
  ~set(){};
  set &operator=(set &&s);
  void merge(set &other);
  std::pair<iterator, bool> insert(const value_type &value);
  iterator find(const key_type &key);
  bool contains(const key_type &key);
};

}  // namespace s21
#include "./s21_set.tpp"

#endif  // SET