#include <gtest/gtest.h>

#include <set>

#include "../s21_containers.h"

TEST(set_test, constructorInit) {
  s21::set<int> m1 = {1, 2, 3, 4, 5};
  std::set<int> m2 = {1, 2, 3, 4, 5};
  auto it1 = m1.begin();
  for (auto it2 = m2.begin(); it2 != m2.end(); it1++, it2++)
    EXPECT_EQ((*it1), (*it2));
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(set_test, constructorEmpty) {
  s21::set<int> m1;
  std::set<int> m2;
  EXPECT_EQ(m1.size(), m2.size());
  m1.insert(1);
  m2.insert(1);
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(set_test, constructorCopy) {
  s21::set<int> m1 = {1, 2, 3, 4, 5};
  s21::set<int> m2(m1);
  EXPECT_EQ(m1.size(), m2.size());
  auto it1 = m1.begin();
  for (auto it2 = m2.begin(); it2 != m2.end(); it1++, it2++)
    EXPECT_EQ((*it1), (*it2));
}

TEST(set_test, constructorMove) {
  s21::set<int> m1 = {1, 2, 3, 4, 5};
  s21::set<int> m3 = {1, 2, 3, 4, 5};
  s21::set<int> m2 = std::move(m1);
  EXPECT_EQ(m1.size(), 0);
  EXPECT_EQ(m1.empty(), 1);
  auto it1 = m2.begin();
  for (auto it2 = m2.begin(); it2 != m2.end(); it1++, it2++)
    EXPECT_EQ((*it1), (*it2));
}

TEST(set_test, begin) {
  s21::set<int> m1 = {1};
  std::set<int> m2 = {1};
  auto it1 = m1.begin();
  auto it2 = m2.begin();
  EXPECT_EQ((*it1), (*it2));
}

TEST(set_test, beginLap) {
  s21::set<int> m1 = {1};
  std::set<int> m2 = {1};
  auto it1 = m1.begin();
  it1--;
  auto it2 = m2.begin();
  it2--;
  EXPECT_EQ((*it1), (*it2));
}

TEST(set_test, end) {
  s21::set<int> m1 = {1, 2, 3, 4, 5};
  std::set<int> m2 = {1, 2, 3, 4, 5};
  auto it1 = m1.end();
  auto it2 = m2.end();
  it1--, it2--;
  EXPECT_EQ((*it2), (*it1));
}

TEST(set_test, endLap) {
  s21::set<int> m1 = {1, 2, 3, 4, 5};
  std::set<int> m2 = {1, 2, 3, 4, 5};
  auto it1 = m1.end();
  auto it2 = m2.end();
  it1++, it2++;
  EXPECT_EQ((*it2), (*it1));
}

TEST(set_test, emptyFalse) {
  s21::set<int> m1 = {1, 2, 3, 4, 5};
  std::set<int> m2 = {1, 2, 3, 4, 5};
  EXPECT_EQ(m1.empty(), m2.empty());
}

TEST(set_test, emptyTrue) {
  s21::set<int> m1;
  std::set<int> m2;
  EXPECT_EQ(m1.empty(), m2.empty());
}

TEST(set_test, size) {
  s21::set<int> m1;
  std::set<int> m2;
  m1.insert(1);
  m2.insert(1);
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(set_test, sizeZero) {
  s21::set<int> m1;
  std::set<int> m2;
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(set_test, clear) {
  s21::set<int> m1 = {1, 2, 3, 4, 5};
  std::set<int> m2 = {1, 2, 3, 4, 5};
  m1.clear();
  m2.clear();
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m1.empty(), m2.empty());
}

TEST(set_test, clearEmpty) {
  s21::set<int> m1;
  std::set<int> m2;
  m1.clear();
  m2.clear();
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m1.empty(), m2.empty());
}

TEST(set_test, Insert) {
  s21::set<int> m1;
  std::set<int> m2;

  auto s_pr = m1.insert(1);
  auto o_pr = m2.insert(1);
  EXPECT_EQ(*(s_pr.first), (*o_pr.first));
  EXPECT_EQ(s_pr.second, o_pr.second);

  s_pr = m1.insert(2);
  o_pr = m2.insert(2);
  s_pr = m1.insert(3);
  o_pr = m2.insert(3);

  auto si = m1.begin();
  auto oi = m2.begin();
  for (; si != m1.end() && oi != m2.end(); ++si, ++oi) {
    EXPECT_EQ(*(si), *(oi));
  }

  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m1.empty(), m2.empty());
}

TEST(set_test, Erase) {
  s21::set<int> m1;
  std::set<int> m2;

  m1.insert(1);
  m2.insert(1);

  auto s_pr = m1.insert(2);
  auto o_pr = m2.insert(2);
  m1.erase(s_pr.first);
  m2.erase(o_pr.first);

  auto si = m1.begin();
  auto oi = m2.begin();
  for (; si != m1.end() && oi != m2.end(); ++si, ++oi) {
    EXPECT_EQ(*(si), *(oi));
  }
}

TEST(set_test, EraseOneChild) {
  s21::set<int> m1{1, 2, 3};
  auto it = m1.find(2);
  m1.erase(it);
  EXPECT_EQ(m1.contains(2), false);
}

TEST(set_test, EraseOneChild2) {
  s21::set<int> m1{2};
  auto it = m1.find(2);
  m1.erase(it);
  EXPECT_EQ(m1.contains(2), false);
}

TEST(set_test, EraseTwoChild) {
  s21::set<int> m1{2, 1, 3};
  auto it = m1.find(2);
  m1.erase(it);
  EXPECT_EQ(m1.contains(2), false);
}

TEST(set_test, MergeTwoChildTop) {
  s21::set<int> m1{3, 1, 2, 0};
  s21::set<int> m2;
  m2.merge(m1);
  EXPECT_EQ(m1.contains(1), false);
}

TEST(set_test, InsertAlreadyHave) {
  s21::set<int> m1;
  std::set<int> m2;
  m1.insert(1);
  auto s_pr2 = m1.insert(1);
  m2.insert(1);
  auto o_pr2 = m2.insert(1);
  EXPECT_EQ(*(s_pr2.first), (*o_pr2.first));
  EXPECT_EQ(s_pr2.second, o_pr2.second);
}

TEST(set_test, Swap) {
  s21::set<std::string> f_s_tree = {{"zero"},  {"one"},  {"two"}, {"three"},
                                    {"four"},  {"five"}, {"six"}, {"seven"},
                                    {"eight"}, {"nine"}};

  s21::set<std::string> s_s_tree = {{"ten"},    {"twenty"}, {"thirty"},
                                    {"fourty"}, {"fifty"},  {"sixty"},
                                    {"seventy"}};

  std::set<std::string> f_o_tree = {{"zero"},  {"one"},  {"two"}, {"three"},
                                    {"four"},  {"five"}, {"six"}, {"seven"},
                                    {"eight"}, {"nine"}};

  std::set<std::string> s_o_tree = {{"ten"},    {"twenty"}, {"thirty"},
                                    {"fourty"}, {"fifty"},  {"sixty"},
                                    {"seventy"}};
  f_s_tree.swap(s_s_tree);
  f_o_tree.swap(s_o_tree);

  EXPECT_EQ(f_s_tree.size(), f_o_tree.size());
  EXPECT_EQ(f_s_tree.empty(), f_o_tree.empty());
  EXPECT_EQ(s_s_tree.size(), s_o_tree.size());
  EXPECT_EQ(s_s_tree.empty(), s_o_tree.empty());

  auto si = f_s_tree.begin();
  auto oi = f_o_tree.begin();
  for (; si != f_s_tree.end() && oi != f_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }
  si = s_s_tree.begin();
  oi = s_o_tree.begin();
  for (; si != s_s_tree.end() && oi != s_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }
}

TEST(set_test, Merge) {
  s21::set<int> s1{1, 2, 3};
  s21::set<int> s2{3, 4, 5};
  std::set<int> s3{1, 2, 3};
  std::set<int> s4{3, 4, 5};
  s1.merge(s2);
  s3.merge(s4);
  EXPECT_EQ(s1.size(), s3.size());
  EXPECT_TRUE(s1.contains(4));
  EXPECT_TRUE(s2.contains(3));
}

TEST(set_test, MergeEmpty) {
  s21::set<int> s1;
  s21::set<int> s2{3, 4, 5};
  std::set<int> s3;
  std::set<int> s4{3, 4, 5};
  s1.merge(s2);
  s3.merge(s4);
  EXPECT_EQ(s1.size(), s3.size());
  EXPECT_TRUE(s1.contains(3));
  EXPECT_FALSE(s2.contains(3));
}

TEST(set_test, Merge2) {
  s21::set<int> s1{1, 2, 3, 4, 5, 6, 7, 8};
  s21::set<int> s2{9, -1, 3};
  std::set<int> s3{1, 2, 3, 4, 5, 6, 7, 8};
  std::set<int> s4{9, -1, 3};
  s1.merge(s2);
  s3.merge(s4);
  EXPECT_EQ(s1.size(), s3.size());
}

TEST(set_test, containsTrue) {
  s21::set<int> m1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(m1.contains(1), true);
}

TEST(set_test, containsFalse) {
  s21::set<int> m1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(m1.contains(0), false);
}

TEST(set_test, Max_size) {
  s21::set<int> m1 = {1, 2, 3, 4, 5};
  std::set<int> m2 = {1, 2, 3, 4, 5};

  EXPECT_EQ(m1.max_size(), m2.max_size());
}

TEST(set_test, Operator) {
  s21::set<int> m1 = {1, 2, 3, 4, 5};
  s21::set<int> &m2 = m1;

  auto it1 = m1.begin();
  for (auto it2 = m2.begin(); it2 != m2.end(); it1++, it2++)
    EXPECT_EQ((*it1), (*it2));
}

TEST(set_test, Find) {
  s21::set<int> m1 = {1, 2, 3, 4, 5};
  std::set<int> m2 = {1, 2, 3, 4, 5};

  EXPECT_EQ(*m1.find(0), *m2.find(0));
  EXPECT_EQ(*m1.find(1), *m2.find(1));
}

TEST(set_test, BackwardsIterator) {
  s21::set<int> m1 = {60, 58, 63, 1, 59, 61, 65};
  std::set<int> m2 = {60, 58, 63, 1, 59, 61, 65};

  auto it1 = m1.end();
  auto it2 = m2.end();
  for (; it1 != m1.begin() && it2 != m2.begin(); --it1, --it2)
    EXPECT_EQ((*it1), (*it2));
}

TEST(set_test, Erase_Test_2) {
  s21::set<int> m1 = {60, 58, 63, 1, 59, 61, 65};
  std::set<int> m2 = {60, 58, 63, 1, 59, 61, 65};

  auto it1 = m1.find(1);
  auto it2 = m2.find(1);
  m1.erase(it1);
  m2.erase(it2);
  it1 = m1.begin();
  it2 = m2.begin();
  for (; it1 != m1.end() && it2 != m2.end(); ++it1, ++it2)
    EXPECT_EQ((*it1), (*it2));
}

TEST(set_test, Erase_Test_3) {
  s21::set<int> m1 = {60, 58, 63, 1, 59, 61, 65, 62};
  std::set<int> m2 = {60, 58, 63, 1, 59, 61, 65, 62};

  auto it1 = m1.find(62);
  auto it2 = m2.find(62);
  m1.erase(it1);
  m2.erase(it2);
  it1 = m1.begin();
  it2 = m2.begin();
  for (; it1 != m1.end() && it2 != m2.end(); ++it1, ++it2)
    EXPECT_EQ((*it1), (*it2));
}

TEST(set_test, Erase_Test_4) {
  s21::set<int> m1 = {60, 58, 63, 1, 61, 65, 62};
  std::set<int> m2 = {60, 58, 63, 1, 61, 65, 62};

  auto it1 = m1.find(58);
  auto it2 = m2.find(58);
  m1.erase(it1);
  m2.erase(it2);
  it1 = m1.begin();
  it2 = m2.begin();
  for (; it1 != m1.end() && it2 != m2.end(); ++it1, ++it2)
    EXPECT_EQ((*it1), (*it2));
}

TEST(set_test, Erase_Test_5) {
  s21::set<int> m1 = {10, 12};
  std::set<int> m2 = {10, 12};

  auto it1 = m1.find(10);
  auto it2 = m2.find(10);
  m1.erase(it1);
  m2.erase(it2);
  it1 = m1.begin();
  it2 = m2.begin();
  for (; it1 != m1.end() && it2 != m2.end(); ++it1, ++it2)
    EXPECT_EQ((*it1), (*it2));
}

TEST(set_test, Erase_Test_6) {
  s21::set<int> m1 = {60, 58, 55, 63, 1, 59, 61, 65, 62};
  std::set<int> m2 = {60, 58, 55, 63, 1, 59, 61, 65, 62};

  auto it1 = m1.find(58);
  auto it2 = m2.find(58);
  m1.erase(it1);
  m2.erase(it2);
  it1 = m1.begin();
  it2 = m2.begin();
  for (; it1 != m1.end() && it2 != m2.end(); ++it1, ++it2)
    EXPECT_EQ((*it1), (*it2));
}

TEST(set_test, MergeTest_3) {
  s21::set<int> m1 = {1};
  s21::set<int> m2 = {5, 1, 7, 2, 3};
  std::set<int> m3 = {1};
  std::set<int> m4 = {5, 1, 7, 2, 3};

  m1.merge(m2);
  m3.merge(m4);
  auto it1 = m1.begin();
  auto it2 = m3.begin();
  for (; it1 != m1.end() && it2 != m3.end(); ++it1, ++it2)
    EXPECT_EQ((*it1), (*it2));
}

TEST(set_test, MergeTest_4) {
  s21::set<int> m1 = {1, 0};
  s21::set<int> m2 = {5, 2, 7, 0, 3, 6, 9, 10};
  std::set<int> m3 = {1, 0};
  std::set<int> m4 = {5, 2, 7, 0, 3, 6, 9, 10};

  m1.merge(m2);
  m3.merge(m4);
  auto it1 = m1.begin();
  auto it2 = m3.begin();
  for (; it1 != m1.end() && it2 != m3.end(); ++it1, ++it2)
    EXPECT_EQ((*it1), (*it2));
}

TEST(set_test, MergeTest_5) {
  s21::set<int> m1 = {5, 2, 6};
  s21::set<int> m2 = {5, 2, 7, 0, 3, 6, 9, 10};
  std::set<int> m3 = {5, 2, 6};
  std::set<int> m4 = {5, 2, 7, 0, 3, 6, 9, 10};

  m1.merge(m2);
  m3.merge(m4);
  auto it1 = m1.begin();
  auto it2 = m3.begin();
  for (; it1 != m1.end() && it2 != m3.end(); ++it1, ++it2)
    EXPECT_EQ((*it1), (*it2));
}

TEST(set_test, MergeTest_6) {
  s21::set<int> m1 = {10, 13, 15};
  s21::set<int> m2 = {10, 20, 15, 13, 25};
  std::set<int> m3 = {10, 13, 15};
  std::set<int> m4 = {10, 20, 15, 13, 25};

  m1.merge(m2);
  m3.merge(m4);
  auto it1 = m1.begin();
  auto it2 = m3.begin();
  for (; it1 != m1.end() && it2 != m3.end(); ++it1, ++it2)
    EXPECT_EQ((*it1), (*it2));
}

TEST(set_test, Emplace_Test) {
  s21::set<int> m1 = {10, 13, 15};
  std::set<int> m2 = {10, 13, 15};

  m1.emplace(5);
  m2.emplace(5);
  auto it1 = m1.begin();
  auto it2 = m2.begin();
  for (; it1 != m1.end() && it2 != m2.end(); ++it1, ++it2)
    EXPECT_EQ((*it1), (*it2));
}

TEST(set_test, ItaratorEq) {
  s21::set<int> m1 = {10, 13, 15};

  auto it1 = m1.begin();
  auto it2 = m1.begin();
  bool res = false;
  if (it1 == it2) res = true;
  EXPECT_EQ(res, true);
}

TEST(set_test, Operators_2) {
  s21::set<int> m1 = {10, 13, 15};
  s21::set<int> m2;
  m2 = m1;
  std::set<int> m3 = {10, 13, 15};
  std::set<int> m4;
  m4 = m3;

  auto it1 = m2.begin();
  auto it2 = m4.begin();
  for (; it1 != m2.end() && it2 != m4.end(); ++it1, ++it2)
    EXPECT_EQ((*it1), (*it2));
}

TEST(set_test, Operators_3) {
  s21::set<int> m1 = {10, 13, 15};
  s21::set<int> m2;
  m2 = std::move(m1);
  std::set<int> m3 = {10, 13, 15};
  std::set<int> m4;
  m4 = std::move(m3);

  auto it1 = m2.begin();
  auto it2 = m4.begin();
  for (; it1 != m2.end() && it2 != m4.end(); ++it1, ++it2)
    EXPECT_EQ((*it1), (*it2));
}

TEST(set_test, Const_Iter) {
  const s21::set<int> m1 = {10, 13, 15};
  const std::set<int> m3 = {10, 13, 15};

  auto it1 = m1.begin();
  auto it2 = m3.begin();
  EXPECT_EQ(*it1, *it2);
  it1 = m1.end();
  it2 = m3.end();
  EXPECT_EQ(*it1, *it2);
}

TEST(set_test, Const_Find_Contains_Test) {
  const s21::set<int> m1 = {10, 13, 15};
  const std::set<int> m3 = {10, 13, 15};

  auto it1 = m1.find(10);
  auto it2 = m3.find(10);
  EXPECT_EQ(*it1, *it2);
  bool res1 = m1.contains(15);
  EXPECT_EQ(res1, true);
}

// throw cause leaks on Mac

// TEST(set_test, throw_test) {
//   s21::set<int> m1 = {10, 3, 11, 15};
//   auto it = m1.end();
//   EXPECT_ANY_THROW(m1.erase(it));
// }