#include <gtest/gtest.h>

#include <queue>

#include "../s21_containers.h"

TEST(QueueTest, DefaultConstructor) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  EXPECT_EQ(std_queue.empty(), s21_queue.empty());
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(QueueTest, InitializerListConstructor) {
  s21::queue<unsigned int> q1{1, 2, 3};
  ASSERT_EQ(q1.size(), 3u);
  ASSERT_EQ(q1.front(), 1u);
  ASSERT_EQ(q1.back(), 3u);

  s21::queue<std::string> q2{"hello", "world"};
  ASSERT_EQ(q2.size(), 2u);
  ASSERT_EQ(q2.front(), "hello");
  ASSERT_EQ(q2.back(), "world");
}

TEST(QueueTest, InitializerListConstructorPair) {
  s21::queue<std::pair<std::string, int>> q1{
      {"one", 1}, {"two", 2}, {"three", 3}};
  std::queue<std::pair<std::string, int>> q2;
  q2.push({"one", 1});
  q2.push({"two", 2});
  q2.push({"three", 3});
  EXPECT_EQ(q1.empty(), q2.empty());
  EXPECT_EQ(q1.size(), q2.size());
  while (!q1.empty()) {
    EXPECT_EQ(q1.front().first, q2.front().first);
    EXPECT_EQ(q1.front().second, q2.front().second);
    q1.pop();
    q2.pop();
  }
}

TEST(QueueTest, EmptyInitializerListConstructor) {
  s21::queue<unsigned int> q{};
  ASSERT_TRUE(q.empty());
}

TEST(QueueTest, CopyInitializerListConstructor) {
  s21::queue<unsigned int> q1{1, 2, 3};
  s21::queue<unsigned int> q2{q1};
  ASSERT_EQ(q1.size(), q2.size());
  ASSERT_EQ(q1.front(), q2.front());
  ASSERT_EQ(q1.back(), q2.back());
}

TEST(QueueTest, MoveInitializerListConstructor) {
  s21::queue<unsigned int> q1{1, 2, 3};
  s21::queue<unsigned int> q2{std::move(q1)};
  ASSERT_EQ(q1.size(), 0u);
  ASSERT_EQ(q2.size(), 3u);
  ASSERT_EQ(q2.front(), 1u);
  ASSERT_EQ(q2.back(), 3u);
}

TEST(QueueTest, PushPopFrontBack) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  for (int i = 1; i <= 10; ++i) {
    std_queue.push(i);
    s21_queue.push(i);
  }
  while (!std_queue.empty()) {
    EXPECT_EQ(std_queue.front(), s21_queue.front());
    EXPECT_EQ(std_queue.back(), s21_queue.back());
    std_queue.pop();
    s21_queue.pop();
  }
}

TEST(QueueTest, FrontBackPair) {
  s21::queue<std::pair<std::string, int>> q{
      {"one", 1}, {"two", 2}, {"three", 3}};
  std::queue<std::pair<std::string, int>> q2;
  q2.push({"one", 1});
  q2.push({"two", 2});
  q2.push({"three", 3});
  EXPECT_EQ(q.front().first, q2.front().first);
  EXPECT_EQ(q.front().second, q2.front().second);
  EXPECT_EQ(q.back().first, q2.back().first);
  EXPECT_EQ(q.back().second, q2.back().second);
}

TEST(QueueTest, PushPopPair) {
  s21::queue<std::pair<std::string, int>> q;
  std::queue<std::pair<std::string, int>> q2;
  q.push({"one", 1});
  q2.push({"one", 1});
  q.push({"two", 2});
  q2.push({"two", 2});
  q.push({"three", 3});
  q2.push({"three", 3});
  EXPECT_EQ(q.empty(), q2.empty());
  EXPECT_EQ(q.size(), q2.size());
  while (!q.empty()) {
    EXPECT_EQ(q.front().first, q2.front().first);
    EXPECT_EQ(q.front().second, q2.front().second);
    q.pop();
    q2.pop();
  }
}

TEST(QueueTest, CopyConstructor) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  for (int i = 1; i <= 10; ++i) {
    std_queue.push(i);
    s21_queue.push(i);
  }
  std::queue<int> std_copy(std_queue);
  s21::queue<int> s21_copy(s21_queue);
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  while (!std_copy.empty()) {
    EXPECT_EQ(std_copy.front(), s21_copy.front());
    std_copy.pop();
    s21_copy.pop();
  }
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(QueueTest, CopyConstructorPair) {
  s21::queue<std::pair<std::string, int>> q1{
      {"one", 1}, {"two", 2}, {"three", 3}};
  s21::queue<std::pair<std::string, int>> q2(q1);
  EXPECT_EQ(q1.empty(), q2.empty());
  EXPECT_EQ(q1.size(), q2.size());
  while (!q1.empty()) {
    EXPECT_EQ(q1.front().first, q2.front().first);
    EXPECT_EQ(q1.front().second, q2.front().second);
    q1.pop();
    q2.pop();
  }
}

TEST(QueueTest, CopyConstructorEmpty) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  std::queue<int> std_copy(std_queue);
  s21::queue<int> s21_copy(s21_queue);
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(QueueTest, CopyConstructorSize) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  for (int i = 1; i <= 10; ++i) {
    std_queue.push(i);
    s21_queue.push(i);
  }
  std::queue<int> std_copy(std_queue);
  s21::queue<int> s21_copy(s21_queue);
  std_queue.push(11);
  s21_queue.push(11);
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(QueueTest, CopyAssignmentOperator) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  for (int i = 1; i <= 10; ++i) {
    std_queue.push(i);
    s21_queue.push(i);
  }
  std::queue<int> std_copy;
  s21::queue<int> s21_copy;
  std_copy = std_queue;
  s21_copy = s21_queue;
  while (!std_copy.empty()) {
    EXPECT_EQ(std_copy.front(), s21_copy.front());
    std_copy.pop();
    s21_copy.pop();
  }
}

TEST(QueueTest, CopyAssignmentPair) {
  s21::queue<std::pair<std::string, int>> q1{
      {"one", 1}, {"two", 2}, {"three", 3}};
  s21::queue<std::pair<std::string, int>> q2;
  std::queue<std::pair<std::string, int>> q3;
  q2 = q1;
  EXPECT_EQ(q1.empty(), q2.empty());
  EXPECT_EQ(q1.size(), q2.size());
  while (!q1.empty()) {
    EXPECT_EQ(q1.front().first, q2.front().first);
    EXPECT_EQ(q1.front().second, q2.front().second);
    q1.pop();
    q2.pop();
  }
}

TEST(QueueTest, AssignmentOperator) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  for (int i = 1; i <= 10; ++i) {
    std_queue.push(i);
    s21_queue.push(i);
  }
  std::queue<int> std_copy;
  s21::queue<int> s21_copy;
  std_copy = std_queue;
  s21_copy = s21_queue;
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  while (!std_copy.empty()) {
    EXPECT_EQ(std_copy.front(), s21_copy.front());
    std_copy.pop();
    s21_copy.pop();
  }
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(QueueTest, AssignmentOperatorEmpty) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  std::queue<int> std_copy;
  s21::queue<int> s21_copy;
  std_copy = std_queue;
  s21_copy = s21_queue;
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(QueueTest, AssignmentOperatorSize) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  for (int i = 1; i <= 10; ++i) {
    std_queue.push(i);
    s21_queue.push(i);
  }
  std::queue<int> std_copy;
  s21::queue<int> s21_copy;
  std_copy = std_queue;
  s21_copy = s21_queue;
  std_queue.push(11);
  s21_queue.push(11);
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(QueueTest, MoveAssignmentOperator) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  for (int i = 1; i <= 10; ++i) {
    std_queue.push(i);
    s21_queue.push(i);
  }
  std::queue<int> std_move;
  s21::queue<int> s21_move;
  std_move = std::move(std_queue);
  s21_move = std::move(s21_queue);
  while (!std_move.empty()) {
    EXPECT_EQ(std_move.front(), s21_move.front());
    std_move.pop();
    s21_move.pop();
  }
}

TEST(QueueTest, MoveAssignmentPair) {
  s21::queue<std::pair<std::string, int>> q1{
      {"one", 1}, {"two", 2}, {"three", 3}};
  s21::queue<std::pair<std::string, int>> q2;
  std::queue<std::pair<std::string, int>> q3;
  q2 = std::move(q1);
  q3.push({"one", 1});
  q3.push({"two", 2});
  q3.push({"three", 3});
  EXPECT_EQ(q1.empty(), true);
  EXPECT_EQ(q2.size(), q3.size());
  while (!q2.empty()) {
    EXPECT_EQ(q2.front().first, q3.front().first);
    EXPECT_EQ(q2.front().second, q3.front().second);
    q2.pop();
    q3.pop();
  }
}

TEST(QueueTest, EmplaceBackTest) {
  s21::queue<unsigned int> q;
  q.emplace_back(1);
  q.emplace_back(2);
  q.emplace_back(3);

  EXPECT_EQ(q.size(), 3u);
  EXPECT_EQ(q.front(), 1u);
  EXPECT_EQ(q.back(), 3u);

  q.pop();
  EXPECT_EQ(q.size(), 2u);
  EXPECT_EQ(q.front(), 2u);

  q.emplace_back(4);
  EXPECT_EQ(q.size(), 3u);
  EXPECT_EQ(q.back(), 4u);
}

TEST(QueueTest, ConstFrontBack) {
  const std::queue<int> std_queue({1, 2, 3});
  const s21::queue<int> s21_queue{1, 2, 3};
  EXPECT_EQ(std_queue.front(), s21_queue.front());
  EXPECT_EQ(std_queue.back(), s21_queue.back());
}

// leaks on mac

// TEST(QueueTest, DefaultConstructorPair) {
//   s21::queue<std::pair<std::string, int>> q1;
//   std::queue<std::pair<std::string, int>> q2;
//   EXPECT_EQ(q1.empty(), q2.empty());
//   EXPECT_EQ(q1.size(), q2.size());
//   EXPECT_THROW(q1.front(), std::out_of_range);
//   EXPECT_THROW(q1.back(), std::out_of_range);
// }

// TEST(QueueTest, EmptyQueue) {
//   s21::queue<int> q;
//   ASSERT_TRUE(q.empty());
//   ASSERT_EQ(q.size(), 0u);
//   ASSERT_THROW(q.front(), std::out_of_range);
//   ASSERT_THROW(q.back(), std::out_of_range);
//   ASSERT_THROW(q.pop(), std::out_of_range);
// }

// TEST(QueueTest, ConstFrontBackThrow) {
//   const s21::queue<int> s21_queue;
//   EXPECT_ANY_THROW(s21_queue.front());
//   EXPECT_ANY_THROW(s21_queue.back());
// }