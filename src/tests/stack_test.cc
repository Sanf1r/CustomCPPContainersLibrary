#include <gtest/gtest.h>

#include <stack>

#include "../s21_containers.h"

TEST(StackTest, DefaultConstructor) {
  s21::stack<int> my_stack;
  std::stack<int> stl_stack;
  EXPECT_EQ(my_stack.size(), stl_stack.size());
  EXPECT_EQ(my_stack.empty(), stl_stack.empty());
}

TEST(StackTest, InitializerListConstructor) {
  s21::stack<unsigned int> s1{1, 2, 3};
  ASSERT_EQ(s1.size(), 3u);
  ASSERT_EQ(s1.top(), 3u);

  s21::stack<std::string> s2{"hello", "world"};
  ASSERT_EQ(s2.size(), 2u);
  ASSERT_EQ(s2.top(), "world");
}

TEST(StackTest, InitializerListConstructorPair) {
  s21::stack<std::pair<std::string, int>> q1{
      {"one", 1}, {"two", 2}, {"three", 3}};
  std::stack<std::pair<std::string, int>> q2;
  q2.push({"one", 1});
  q2.push({"two", 2});
  q2.push({"three", 3});
  EXPECT_EQ(q1.empty(), q2.empty());
  EXPECT_EQ(q1.size(), q2.size());
  while (!q1.empty()) {
    EXPECT_EQ(q1.top(), q2.top());
    q1.pop();
    q2.pop();
  }
}

TEST(StackTest, EmptyInitializerListConstructor) {
  s21::stack<int> s{};
  ASSERT_TRUE(s.empty());
  ASSERT_EQ(s.size(), 0u);
}

TEST(StackTest, Empty) {
  s21::stack<std::pair<std::string, int>> s;
  std::stack<std::pair<std::string, int>> s_stl;

  EXPECT_TRUE(s.empty());
  EXPECT_TRUE(s_stl.empty());

  s.push({"one", 1});
  s_stl.push({"one", 1});

  EXPECT_FALSE(s.empty());
  EXPECT_FALSE(s_stl.empty());

  s.pop();
  s_stl.pop();

  EXPECT_TRUE(s.empty());
  EXPECT_TRUE(s_stl.empty());
}

TEST(StackTest, Size) {
  s21::stack<std::pair<std::string, unsigned int>> s;
  std::stack<std::pair<std::string, unsigned int>> s_stl;

  EXPECT_EQ(s.size(), 0u);
  EXPECT_EQ(s_stl.size(), 0u);

  s.push({"one", 1u});
  s_stl.push({"one", 1u});
  EXPECT_EQ(s.size(), s_stl.size());

  s.push({"two", 2u});
  s_stl.push({"two", 2u});
  EXPECT_EQ(s.size(), s_stl.size());

  s.push({"three", 3u});
  s_stl.push({"three", 3u});
  EXPECT_EQ(s.size(), s_stl.size());

  s.pop();
  s_stl.pop();
  EXPECT_EQ(s.size(), s_stl.size());

  s.pop();
  s_stl.pop();
  EXPECT_EQ(s.size(), s_stl.size());

  s.pop();
  s_stl.pop();
  EXPECT_EQ(s.size(), s_stl.size());
}

TEST(StackTest, PushPopTop) {
  std::stack<int> std_stack;
  s21::stack<int> s21_stack;
  for (int i = 1; i <= 10; ++i) {
    std_stack.push(i);
    s21_stack.push(i);
  }
  while (!std_stack.empty()) {
    EXPECT_EQ(std_stack.top(), s21_stack.top());
    std_stack.pop();
    s21_stack.pop();
  }
}

TEST(StackTest, PushAndPopString) {
  s21::stack<std::string> s;
  std::stack<std::string> s_stl;

  s.push("one");
  s_stl.push("one");
  EXPECT_EQ(s.top(), s_stl.top());

  s.push("two");
  s_stl.push("two");
  EXPECT_EQ(s.top(), s_stl.top());

  s.pop();
  s_stl.pop();
  EXPECT_EQ(s.top(), s_stl.top());

  s.pop();
  s_stl.pop();
  EXPECT_TRUE(s.empty());
  EXPECT_TRUE(s_stl.empty());
}

TEST(StackTest, TopPair) {
  s21::stack<std::pair<std::string, int>> s;
  std::stack<std::pair<std::string, int>> s_stl;

  s.push({"one", 1});
  s_stl.push({"one", 1});

  // Проверяем, что top() возвращает правильный элемент
  EXPECT_EQ(s.top(), s_stl.top());

  s.push({"two", 2});
  s_stl.push({"two", 2});

  EXPECT_EQ(s.top(), s_stl.top());

  s.pop();
  s_stl.pop();

  EXPECT_EQ(s.top(), s_stl.top());

  s.pop();
  s_stl.pop();

  EXPECT_TRUE(s.empty());
  EXPECT_TRUE(s_stl.empty());
}

TEST(StackTest, CopyConstructor) {
  std::stack<int> std_stack;
  s21::stack<int> s21_stack;
  for (int i = 1; i <= 10; ++i) {
    std_stack.push(i);
    s21_stack.push(i);
  }
  std::stack<int> std_copy(std_stack);
  s21::stack<int> s21_copy(s21_stack);
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  while (!std_copy.empty()) {
    EXPECT_EQ(std_copy.top(), s21_copy.top());
    std_copy.pop();
    s21_copy.pop();
  }
  EXPECT_EQ(std_stack.size(), s21_stack.size());
}

TEST(StackTest, CopyConstructorString) {
  s21::stack<std::string> s1;
  std::stack<std::string> s1_stl;

  s1.push("one");
  s1_stl.push("one");
  s1.push("two");
  s1_stl.push("two");

  s21::stack<std::string> s2(s1);
  std::stack<std::string> s2_stl(s1_stl);

  while (!s1.empty() && !s2.empty()) {
    EXPECT_EQ(s1.top(), s2.top());
    EXPECT_EQ(s1_stl.top(), s2_stl.top());
    s1.pop();
    s2.pop();
    s1_stl.pop();
    s2_stl.pop();
  }
}

TEST(StackTest, CopyConstructorPair) {
  s21::stack<std::pair<std::string, int>> s1;
  std::stack<std::pair<std::string, int>> s1_stl;

  s1.push({"one", 1});
  s1_stl.push({"one", 1});
  s1.push({"two", 2});
  s1_stl.push({"two", 2});

  s21::stack<std::pair<std::string, int>> s2(s1);
  std::stack<std::pair<std::string, int>> s2_stl(s1_stl);

  while (!s1.empty() && !s2.empty()) {
    EXPECT_EQ(s1.top(), s2.top());
    EXPECT_EQ(s1_stl.top(), s2_stl.top());
    s1.pop();
    s2.pop();
    s1_stl.pop();
    s2_stl.pop();
  }
}

TEST(StackTest, CopyConstructorEmpty) {
  std::stack<int> std_stack;
  s21::stack<int> s21_stack;
  std::stack<int> std_copy(std_stack);
  s21::stack<int> s21_copy(s21_stack);
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  EXPECT_EQ(std_stack.size(), s21_stack.size());
}

TEST(StackTest, MoveConstructorPair) {
  s21::stack<std::pair<std::string, int>> s1;
  std::stack<std::pair<std::string, int>> s1_stl;

  s1.push({"one", 1});
  s1_stl.push({"one", 1});
  s1.push({"two", 2});
  s1_stl.push({"two", 2});

  s21::stack<std::pair<std::string, int>> s2(std::move(s1));
  std::stack<std::pair<std::string, int>> s2_stl(std::move(s1_stl));

  EXPECT_TRUE(s1.empty());
  EXPECT_TRUE(s2.size() == 2);

  EXPECT_TRUE(s1_stl.empty());
  EXPECT_TRUE(s2_stl.size() == 2);
}

TEST(StackTest, MoveConstructorString) {
  s21::stack<std::string> s1;
  std::stack<std::string> s1_stl;

  s1.push("one");
  s1_stl.push("one");
  s1.push("two");
  s1_stl.push("two");

  s21::stack<std::string> s2(std::move(s1));
  std::stack<std::string> s2_stl(std::move(s1_stl));

  EXPECT_TRUE(s1.empty());
  EXPECT_TRUE(s2.size() == 2);
  EXPECT_TRUE(s2.top() == "two");

  EXPECT_TRUE(s1_stl.empty());
  EXPECT_TRUE(s2_stl.size() == 2);
  EXPECT_TRUE(s2_stl.top() == "two");
}

TEST(StackTest, CopyAssignmentOperator) {
  s21::stack<int> my_stack;
  std::stack<int> stl_stack;

  for (int i = 0; i < 10; ++i) {
    my_stack.push(i);
    stl_stack.push(i);
  }

  s21::stack<int> my_copy_stack;
  std::stack<int> stl_copy_stack;

  my_copy_stack = my_stack;
  stl_copy_stack = stl_stack;

  EXPECT_EQ(my_copy_stack.size(), stl_copy_stack.size());

  while (!my_copy_stack.empty()) {
    EXPECT_EQ(my_copy_stack.top(), stl_copy_stack.top());
    my_copy_stack.pop();
    stl_copy_stack.pop();
  }

  EXPECT_TRUE(my_copy_stack.empty());
  EXPECT_TRUE(stl_copy_stack.empty());
}

TEST(StackTest, CopyAssignmentOperatorPair) {
  s21::stack<std::pair<std::string, int>> s1;
  std::stack<std::pair<std::string, int>> s1_stl;

  s1.push({"one", 1});
  s1_stl.push({"one", 1});
  s1.push({"two", 2});
  s1_stl.push({"two", 2});
  s1.push({"three", 3});
  s1_stl.push({"three", 3});

  s21::stack<std::pair<std::string, int>> s2;
  std::stack<std::pair<std::string, int>> s2_stl;

  s2.push({"four", 4});
  s2_stl.push({"four", 4});

  s2 = s1;
  s2_stl = s1_stl;

  while (!s1.empty() && !s2.empty()) {
    EXPECT_EQ(s1.top(), s2.top());
    EXPECT_EQ(s1_stl.top(), s2_stl.top());
    s1.pop();
    s2.pop();
    s1_stl.pop();
    s2_stl.pop();
  }
}

TEST(StackTest, MoveAssignmentOperator) {
  s21::stack<int> my_stack;
  std::stack<int> stl_stack;

  for (int i = 0; i < 10; ++i) {
    my_stack.push(i);
    stl_stack.push(i);
  }

  s21::stack<int> my_move_stack;
  std::stack<int> stl_move_stack;

  my_move_stack = std::move(my_stack);
  stl_move_stack = std::move(stl_stack);

  EXPECT_EQ(my_move_stack.size(), stl_move_stack.size());
  EXPECT_EQ(my_stack.size(), stl_stack.size());

  while (!my_move_stack.empty()) {
    EXPECT_EQ(my_move_stack.top(), stl_move_stack.top());
    my_move_stack.pop();
    stl_move_stack.pop();
  }

  EXPECT_TRUE(my_stack.empty());
  EXPECT_TRUE(stl_stack.empty());
}

TEST(StackTest, MoveAssignmentOperatorPair) {
  s21::stack<std::pair<std::string, int>> s1;
  std::stack<std::pair<std::string, int>> s1_stl;

  s1.push({"one", 1});
  s1_stl.push({"one", 1});
  s1.push({"two", 2});
  s1_stl.push({"two", 2});
  s1.push({"three", 3});
  s1_stl.push({"three", 3});

  s21::stack<std::pair<std::string, int>> s2;
  std::stack<std::pair<std::string, int>> s2_stl;

  s2.push({"four", 4});
  s2_stl.push({"four", 4});

  s2 = std::move(s1);
  s2_stl = std::move(s1_stl);

  EXPECT_TRUE(s1.empty());
  EXPECT_TRUE(s2.size() == 3);

  EXPECT_TRUE(s1_stl.empty());
  EXPECT_TRUE(s2_stl.size() == 3);
}

TEST(StackTest, AssignmentOperatorEmpty) {
  std::stack<int> std_stack;
  s21::stack<int> s21_stack;
  std::stack<int> std_copy;
  s21::stack<int> s21_copy;
  std_copy = std_stack;
  s21_copy = s21_stack;
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  EXPECT_EQ(std_stack.size(), s21_stack.size());
}

TEST(StackTest, EmplaceFrontTest) {
  s21::stack<unsigned int> my_stack;
  my_stack.emplace_front(1);
  my_stack.emplace_front(2);
  my_stack.emplace_front(3);

  EXPECT_EQ(my_stack.size(), 3u);
  EXPECT_EQ(my_stack.top(), 3u);

  my_stack.pop();
  EXPECT_EQ(my_stack.size(), 2u);
  EXPECT_EQ(my_stack.top(), 2u);

  my_stack.emplace_front(4);
  EXPECT_EQ(my_stack.size(), 3u);
  EXPECT_EQ(my_stack.top(), 4u);
}

// leaks on mac

// TEST(StackTest, DefaultConstructorPair) {
//   s21::stack<std::pair<std::string, int>> q1;
//   std::stack<std::pair<std::string, int>> q2;
//   EXPECT_EQ(q1.empty(), q2.empty());
//   EXPECT_EQ(q1.size(), q2.size());
//   EXPECT_THROW(q1.top(), std::out_of_range);
//   EXPECT_THROW(q1.pop(), std::out_of_range);
// }

// TEST(StackTest, TopPopThrow) {
//   s21::stack<int> s;
//   EXPECT_THROW(s.top(), std::out_of_range);
//   EXPECT_THROW(s.pop(), std::out_of_range);
//   s.push(1);
//   s.push(2);
//   EXPECT_EQ(s.top(), 2);
//   s.pop();
//   EXPECT_EQ(s.top(), 1);
// }
