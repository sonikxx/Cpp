#include <gtest/gtest.h>

#include "../s21_containers.h"

using namespace s21;
using namespace std;

TEST(List, DefaultConstructor) {
  s21::List<int> list;
  EXPECT_EQ(list.size(), 0);
}

TEST(List, SizedConstructor) {
  s21::List<int> list(5);
  EXPECT_EQ(list.size(), 5);

  s21::List<int> list2(0);
  EXPECT_EQ(list2.head, nullptr);
  EXPECT_EQ(list2.tail, nullptr);
}

TEST(List, CopyConstructor) {
  s21::List<int> list(5);
  s21::List<int> list2(list);
  EXPECT_EQ(list2.size(), 5);
}

TEST(List, MoveConstructor) {
  s21::List<int> list(5);
  s21::List<int> list2(std::move(list));
  EXPECT_EQ(list2.size(), 5);
}

TEST(List, CopyAssignment) {
  s21::List<int> list(5);
  s21::List<int> list2 = list;
  EXPECT_EQ(list2.size(), 5);

  s21::List<int> list3;
  s21::List<int> list4 = list3;
  EXPECT_EQ(list4.size(), 0);
  EXPECT_EQ(list4.head, nullptr);
  EXPECT_EQ(list4.tail, nullptr);
}

TEST(List, MoveAssignment) {
  s21::List<int> list = {1, 2, 3, 4, 5};
  s21::List<int> list2 = {6, 7, 8, 9, 10};
  list2 = std::move(list);
  EXPECT_EQ(list2.size(), 5);
}

TEST(list, InitializerList) {
  s21::List<int> list = {1, 2, 3, 4, 5};
  EXPECT_EQ(list.size(), 5);

  s21::List<int> list2 = {};
  EXPECT_EQ(list2.size(), 0);
  EXPECT_EQ(list2.head, nullptr);
  EXPECT_EQ(list2.tail, nullptr);
}

TEST(List, FrontElement) {
  s21::List<int> list = {1, 2, 3, 4, 5};
  EXPECT_EQ(list.front(), 1);

  s21::List<int> list2 = {};
  EXPECT_ANY_THROW(list2.front());
}

TEST(List, BackElement) {
  s21::List<int> list = {1, 2, 3, 4, 5};
  EXPECT_EQ(list.back(), 5);

  s21::List<int> list2 = {};
  EXPECT_ANY_THROW(list2.back());
}

TEST(List, IsEmptyList) {
  s21::List<int> list;
  EXPECT_EQ(list.empty(), true);
  s21::List<int> list2 = {1, 2, 3, 4, 5};
  EXPECT_EQ(list2.empty(), false);
}

TEST(List, SizeList) {
  s21::List<int> list = {1, 2, 3, 4, 5};
  EXPECT_EQ(list.size(), 5);
}

TEST(List, MaxSizeList) {
  s21::List<string> list = {"1", "2", "3", "4", "5"};
  EXPECT_GT(list.max_size(), 0);
}

TEST(List, ClearList) {
  s21::List<int> list = {1, 2, 3, 4, 5};
  list.clear();
  EXPECT_EQ(list.size(), 0);
}

TEST(List, InsertList) {
  s21::List<int> list = {1, 2, 3, 4, 5};
  list.insert(list.begin(), 0);
  EXPECT_EQ(list.front(), 0);

  s21::List<int> list2 = {1, 2, 3, 4, 5};
  list2.insert(list2.end(), 6);
  EXPECT_EQ(list2.back(), 6);
  EXPECT_EQ(list2.size(), 6);
}

TEST(List, EraseList) {
  s21::List<int> list = {1, 2, 3, 4, 5};
  list.erase(list.begin());
  EXPECT_EQ(list.front(), 2);

  s21::List<int> list2 = {1, 2, 3, 4, 5};
  list2.erase(list2.end());
  EXPECT_EQ(list2.back(), 4);
}

TEST(List, PushBackList) {
  s21::List<int> list = {1, 2, 3, 4, 5};
  list.push_back(6);
  EXPECT_EQ(list.back(), 6);
}

TEST(List, PushFrontList) {
  s21::List<int> list = {1, 2, 3, 4, 5};
  list.push_front(6);
  EXPECT_EQ(list.front(), 6);

  s21::List<int> list2;
  list2.push_front(6);
  EXPECT_EQ(list2.front(), 6);
}

TEST(List, PopBackList) {
  s21::List<int> list = {1, 2, 3, 4, 5};
  list.pop_back();
  EXPECT_EQ(list.back(), 4);

  s21::List<int> list2 = {1};
  list2.pop_back();
  EXPECT_EQ(list2.head, nullptr);
  EXPECT_EQ(list2.tail, nullptr);

  s21::List<int> list3;
  EXPECT_ANY_THROW(list3.pop_back());
}

TEST(List, PopFrontList) {
  s21::List<int> list = {1, 2, 3, 4, 5};
  list.pop_front();
  EXPECT_EQ(list.front(), 2);

  s21::List<int> list2 = {1};
  list2.pop_front();
  EXPECT_EQ(list2.head, nullptr);
  EXPECT_EQ(list2.tail, nullptr);

  s21::List<int> list3;
  EXPECT_ANY_THROW(list3.pop_front());
}

TEST(List, SwapList) {
  s21::List<int> list = {1, 2, 3, 4, 5};
  s21::List<int> list2 = {6, 7, 8, 9, 10};
  list.swap(list2);
  EXPECT_EQ(list.front(), 6);
  EXPECT_EQ(list2.front(), 1);
}

TEST(List, MergeList) {
  s21::List<int> list = {1, 2, 3, 4, 5};
  s21::List<int> list2 = {6, 7, 8, 9, 10};
  list.merge(list2);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 10);
  EXPECT_EQ(list.size(), 10);

  s21::List<int> list3 = {6, 7, 8, 9, 10};
  s21::List<int> list4 = {1, 2, 3, 4, 5};
  list3.merge(list4);
  EXPECT_EQ(list3.front(), 1);
  EXPECT_EQ(list3.back(), 10);
  EXPECT_EQ(list3.size(), 10);
}

TEST(List, SpliceList) {
  s21::List<int> list = {1, 2, 3, 4, 5};
  s21::List<int> list2 = {6, 7, 8, 9, 10};
  list.splice(list.begin(), list2);
  EXPECT_EQ(list.front(), 6);
  EXPECT_EQ(list.back(), 5);
  EXPECT_EQ(list.size(), 10);

  s21::List<int> list3 = {1, 2, 3, 4, 5};
  s21::List<int> list4 = {};
  list3.splice(list3.begin(), list4);
  EXPECT_EQ(list3.front(), 1);
  EXPECT_EQ(list3.back(), 5);
  EXPECT_EQ(list3.size(), 5);
}

TEST(List, ReverseList) {
  s21::List<int> list = {1, 2, 3, 4, 5};
  list.reverse();
  EXPECT_EQ(list.front(), 5);
  EXPECT_EQ(list.back(), 1);
}

TEST(List, UniqueList) {
  s21::List<int> list = {1, 1, 2, 1, 1};
  list.unique();
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 2);
}

TEST(List, SortList) {
  s21::List<int> list = {5, 4, 3, 2, 1};
  list.sort();
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 5);
}

TEST(List, ConstIteratorList) {
  s21::List<int> list = {1, 2, 3, 4, 5};
  s21::List<int>::const_iterator it = list.cbegin();
  EXPECT_EQ(*it, 1);

  ++it;
  EXPECT_EQ(*it, 2);

  --it;
  EXPECT_EQ(*it, 1);

  it = list.cend();
  EXPECT_EQ(*it, 5);

  s21::List<int>::const_iterator it2 = list.cend();
  EXPECT_TRUE(it == it2);
  EXPECT_FALSE(it != it2);
}

TEST(List, IteratorList) {
  s21::List<int> list = {1, 2, 3, 4, 5};
  s21::List<int>::iterator it = list.begin();
  EXPECT_EQ(*it, 1);

  ++it;
  EXPECT_EQ(*it, 2);

  --it;
  EXPECT_EQ(*it, 1);

  it = list.end();
  EXPECT_EQ(*it, 5);

  s21::List<int>::iterator it2 = list.end();
  EXPECT_TRUE(it == it2);
  EXPECT_FALSE(it != it2);
}
