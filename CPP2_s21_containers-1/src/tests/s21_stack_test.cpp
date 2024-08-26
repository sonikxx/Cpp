#include <gtest/gtest.h>

#include "../s21_containers.h"

using namespace s21;

TEST(Stack, DefaultConstructor) {
  Stack<int> stack;
  ASSERT_TRUE(stack.empty());
}

TEST(Stack, PushPop) {
  s21::Stack<int> stack;
  stack.push(10);
  stack.push(20);
  stack.push(30);
  ASSERT_TRUE(!stack.empty());
  ASSERT_EQ(stack.top(), 30);
  stack.pop();
  ASSERT_EQ(stack.top(), 20);
  stack.pop();
  ASSERT_EQ(stack.top(), 10);
  stack.pop();
  ASSERT_TRUE(stack.empty());

  ASSERT_ANY_THROW(stack.top());
  ASSERT_ANY_THROW(stack.pop());
}

TEST(Stack, Size) {
  Stack<int> stack;
  stack.push(10);
  stack.push(20);
  stack.push(30);
  ASSERT_EQ(stack.size(), 3);
}

TEST(Stack, InitializerList) {
  Stack<int> stack = {10, 20, 30};
  ASSERT_EQ(stack.top(), 30);

  Stack<int> stack2 = {};
  ASSERT_EQ(stack2.head, nullptr);
  ASSERT_TRUE(stack2.empty());
}
TEST(Stack, MoveConstructor) {
  Stack<int> stack;
  stack.push(10);
  stack.push(20);
  stack.push(30);
  Stack<int> stack2(std::move(stack));
  ASSERT_EQ(stack2.top(), 30);
}

TEST(Stack, MoveAssignment) {
  Stack<int> stack;
  stack.push(10);
  stack.push(20);
  stack.push(30);
  Stack<int> stack2;
  stack2 = std::move(stack);
  ASSERT_EQ(stack2.top(), 30);
}

TEST(Stack, CopyConstructor) {
  Stack<int> stack;
  stack.push(10);
  stack.push(20);
  stack.push(30);
  Stack<int> stack2(stack);
  ASSERT_EQ(stack2.top(), 30);

  Stack<int> stack3 = {};
  Stack<int> stack4(stack3);
  ASSERT_EQ(stack4.head, nullptr);
  ASSERT_TRUE(stack4.empty());
}

TEST(Stack, CopyAssignment) {
  Stack<int> stack;
  stack.push(10);
  stack.push(20);
  stack.push(30);
  Stack<int> stack2 = stack;
  ASSERT_EQ(stack2.top(), 30);
}

TEST(Stack, Swap) {
  Stack<int> stack;
  stack.push(10);
  stack.push(20);
  stack.push(30);
  Stack<int> stack2;
  stack2.push(40);
  stack2.push(50);
  stack2.push(60);
  stack.swap(stack2);
  ASSERT_EQ(stack.top(), 60);
  ASSERT_EQ(stack2.top(), 30);
}

TEST(Stack, Empty) {
  Stack<int> stack;
  ASSERT_TRUE(stack.empty());
  stack.push(10);
  ASSERT_FALSE(stack.empty());
}
