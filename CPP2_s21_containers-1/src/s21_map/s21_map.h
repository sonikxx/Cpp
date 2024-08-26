#if !defined(MAP)
#define MAP

#include "../binary_tree.h"

namespace s21 {
template <typename K, typename T>
class map : public Tree<K, std::pair<K, T>> {
 public:
  using key_type = K;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename Tree<K, std::pair<K, T>>::BinIterator;
  using const_iterator = typename Tree<K, std::pair<K, T>>::ConstBinIterator;
  using size_type = size_t;

  map(){};
  map(std::initializer_list<value_type> const &items);
  map(const map &m);
  map(map &&m);
  ~map(){};
  map &operator=(map &&m);
  mapped_type &at(const key_type &key);
  mapped_type &operator[](const key_type &key);
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const key_type &key, const mapped_type &obj);
  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_type &obj);
  void merge(map &other);

 protected:
  iterator find(key_type &key);
};

}  // namespace s21
#include "./s21_map.tpp"

#endif  // MAP