#include <gtest/gtest.h>

#include "../s21_containers.h"

using namespace s21;

TEST(Vector, DefaultConstructor) {
  Vector<int> v;
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);
}

TEST(Vector, ParameterizedConstructor) {
  Vector<int> v(10);
  EXPECT_EQ(v.size(), 10);
  EXPECT_EQ(v.capacity(), 10);

  Vector<int> v2(0);
  EXPECT_EQ(v2.size(), 0);
  EXPECT_EQ(v2.capacity(), 0);
}

TEST(Vector, CopyConstructor) {
  Vector<int> v = {1, 2, 3, 4, 5};
  Vector<int> v2(v);
  EXPECT_EQ(v2.size(), 5);
}

TEST(Vector, MoveConstructor) {
  Vector<int> v = {1, 2, 3, 4, 5};
  Vector<int> v2 = std::move(v);
  EXPECT_EQ(v2.size(), 5);
}

TEST(Vector, MoveAssignment) {
  Vector<int> v = {1, 2, 3, 4, 5};
  Vector<int> v2;
  v2 = std::move(v);
  EXPECT_EQ(v2.size(), 5);
}

TEST(Vector, At) {
  Vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.at(0), 1);
  EXPECT_EQ(v.at(1), 2);
  EXPECT_EQ(v.at(2), 3);
  EXPECT_EQ(v.at(3), 4);
  EXPECT_EQ(v.at(4), 5);

  EXPECT_ANY_THROW(v.at(5));
}

TEST(Vector, OperatorSquareBrackets) {
  Vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
  EXPECT_EQ(v[4], 5);

  EXPECT_ANY_THROW(v[5]);
}

TEST(Vector, Front) {
  Vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.front(), 1);

  Vector<int> v2;
  EXPECT_ANY_THROW(v2.front());
}

TEST(Vector, Back) {
  Vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.back(), 5);

  Vector<int> v2;
  EXPECT_ANY_THROW(v2.back());
}

TEST(Vector, Data) {
  Vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.data()[0], 1);
  EXPECT_EQ(v.data()[1], 2);
  EXPECT_EQ(v.data()[2], 3);
  EXPECT_EQ(v.data()[3], 4);
  EXPECT_EQ(v.data()[4], 5);
}

TEST(Vector, Empty) {
  Vector<int> v;
  EXPECT_EQ(v.empty(), true);

  Vector<int> v2 = {1, 2, 3, 4, 5};
  EXPECT_EQ(v2.empty(), false);
}

TEST(Vector, Size) {
  Vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.size(), 5);
}

TEST(Vector, MaxSize) {
  Vector<int> v = {1};
  EXPECT_EQ(v.max_size(), std::numeric_limits<size_t>::max() / sizeof(int));
}

TEST(Vector, Reserve) {
  Vector<int> v = {1, 2, 3, 4, 5};
  v.reserve(10);
  EXPECT_EQ(v.capacity(), 10);
}

TEST(Vector, Capacity) {
  Vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.capacity(), 5);
}

TEST(Vector, Clear) {
  Vector<int> v = {1, 2, 3, 4, 5};
  v.clear();
  EXPECT_EQ(v.size(), 0);
}

TEST(Vector, Insert) {
  Vector<int> v = {4, 2, 3, 4, 5};
  auto it = v.begin();
  it = v.insert(it, 1);
  EXPECT_EQ(v.size(), 6);
  EXPECT_EQ(v.front(), 1);
  EXPECT_EQ(v[1], 4);
}

TEST(Vector, Erase) {
  Vector<int> v = {1, 2, 3, 4, 5};
  v.erase(v.begin());
  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(v.capacity(), 5);

  v.shrink_to_fit();
  EXPECT_EQ(v.capacity(), 4);
  v.erase(v.begin());
  v.shrink_to_fit();
  EXPECT_EQ(v.capacity(), 3);
}

TEST(Vector, PushBack) {
  Vector<int> v = {1, 2, 3, 4, 5};
  v.push_back(6);
  EXPECT_EQ(v.size(), 6);
}

TEST(Vector, PopBack) {
  Vector<int> v = {1, 2, 3, 4, 5};
  v.pop_back();
  EXPECT_EQ(v.size(), 4);

  Vector<int> v2;
  EXPECT_ANY_THROW(v2.pop_back());
}

TEST(Vector, Swap) {
  Vector<int> v = {1, 2, 3, 4};
  Vector<int> v2 = {6, 7, 8, 9, 10};
  v.swap(v2);
  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v2.size(), 4);
}

// Iterators tests
TEST(Vector, Begin) {
  Vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(*v.begin(), 1);
}

TEST(Vector, End) {
  Vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(*(--v.end()), 5);
}

TEST(Vector, CBegin) {
  Vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(*v.cbegin(), 1);
}

TEST(Vector, CEnd) {
  Vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(*(--v.cend()), 5);
}

TEST(Vector, OperatorPlus) {
  Vector<int> v = {1, 2, 3, 4, 5};
  Vector<int>::iterator it = v.begin();
  ++it;
  EXPECT_EQ(*it, 2);
}

TEST(Vector, OperatorEqual) {
  Vector<int> v = {1, 2, 3, 4, 5};
  Vector<int>::iterator it = v.begin();
  ++it;
  EXPECT_FALSE(it == v.end());

  EXPECT_TRUE(it != v.end());
}

TEST(Vector, ConstOperatorPlus) {
  Vector<int> v = {1, 2, 3, 4, 5};
  Vector<int>::const_iterator it = v.cbegin();
  ++it;
  EXPECT_EQ(*it, 2);
}

TEST(Vector, ConstOperatorEqual) {
  Vector<int> v = {1, 2, 3, 4, 5};
  Vector<int>::const_iterator it = v.cbegin();
  ++it;
  EXPECT_FALSE(it == v.cend());

  EXPECT_TRUE(it != v.cend());
}
