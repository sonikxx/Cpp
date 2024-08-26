#include <gtest/gtest.h>

#include "../s21_containers.h"

TEST(Queue, DefaultConstructor) {
  s21::Queue<int> queue;
  EXPECT_EQ(queue.size(), 0);
}

TEST(Queue, InitializerQueueConstructor) {
  s21::Queue<int> queue = {1, 2, 3, 4, 5};
  EXPECT_EQ(queue.size(), 5);
  EXPECT_FALSE(queue.empty());

  s21::Queue<int> queue2;
  queue2 = {};
  EXPECT_TRUE(queue2.empty());
  EXPECT_TRUE(queue2.head == nullptr);
  EXPECT_TRUE(queue2.tail == nullptr);
}

TEST(Queue, CopyConstructor) {
  s21::Queue<int> queue = {1, 2, 3, 4, 5};
  s21::Queue<int> queue2 = queue;
  EXPECT_EQ(queue2.size(), 5);

  s21::Queue<int> queue3 = {};
  s21::Queue<int> queue4 = queue3;
  EXPECT_TRUE(queue4.head == nullptr);
  EXPECT_TRUE(queue4.tail == nullptr);
}

TEST(Queue, MoveConstructor) {
  s21::Queue<int> queue = {1, 2, 3, 4, 5};
  s21::Queue<int> queue2 = std::move(queue);
  EXPECT_EQ(queue2.size(), 5);
}

TEST(Queue, MoveAssignment) {
  s21::Queue<int> queue = {1, 2, 3, 4, 5};
  s21::Queue<int> queue2;
  queue2 = std::move(queue);
  EXPECT_EQ(queue2.size(), 5);
  std::cout << queue2.back() << std::endl;
}

TEST(Queue, FrontElement) {
  s21::Queue<int> queue = {1, 2, 3, 4, 5};
  EXPECT_EQ(queue.back(), 5);

  s21::Queue<int> queue2;
  EXPECT_ANY_THROW(queue2.front());
}

TEST(Queue, BackElement) {
  s21::Queue<int> queue = {1, 2, 3, 4, 5};
  EXPECT_EQ(queue.back(), 5);

  s21::Queue<int> queue2;
  EXPECT_ANY_THROW(queue2.back());
}

TEST(Queue, PushElement) {
  s21::Queue<int> queue = {1, 2, 3, 4, 5};
  queue.push(6);
  EXPECT_EQ(queue.size(), 6);

  s21::Queue<int> queue2;
  queue2.push(6);
  EXPECT_EQ(queue2.size(), 1);
}

TEST(Queue, PopElement) {
  s21::Queue<int> queue = {1, 2, 3, 4, 5};
  queue.pop();
  EXPECT_EQ(queue.size(), 4);

  s21::Queue<int> queue2;
  EXPECT_ANY_THROW(queue2.pop());

  s21::Queue<int> queue3;
  queue3.push(6);
  queue3.pop();
  EXPECT_EQ(queue2.head, nullptr);
  EXPECT_EQ(queue2.tail, nullptr);
}

TEST(Queue, SwapElements) {
  s21::Queue<int> queue = {1, 2, 3, 4, 5};
  s21::Queue<int> queue2 = {6, 7, 8, 9, 10};
  queue.swap(queue2);
  EXPECT_EQ(queue.front(), 6);
  EXPECT_EQ(queue2.back(), 5);
}
