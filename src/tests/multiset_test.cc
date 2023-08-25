#include <gtest/gtest.h>

#include <set>

#include "../s21_containersplus.h"

TEST(multiset_test, constructorInit) {
  s21::multiset<int> m1 = {1, 2, 3, 4, 5};
  std::multiset<int> m2 = {1, 2, 3, 4, 5};
  auto it1 = m1.begin();
  for (auto it2 = m2.begin(); it2 != m2.end(); it1++, it2++)
    EXPECT_EQ((*it1), (*it2));
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(multiset_test, constructorEmpty) {
  s21::multiset<int> m1;
  std::multiset<int> m2;
  EXPECT_EQ(m1.size(), m2.size());
  m1.insert(1);
  m2.insert(1);
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(multiset_test, constructorCopy) {
  s21::multiset<int> m1 = {1, 2, 3, 4, 5};
  s21::multiset<int> m2(m1);
  EXPECT_EQ(m1.size(), m2.size());
  auto it1 = m1.begin();
  for (auto it2 = m2.begin(); it2 != m2.end(); it1++, it2++)
    EXPECT_EQ((*it1), (*it2));
}

TEST(multiset_test, constructorMove) {
  s21::multiset<int> m1 = {1, 2, 3, 4, 5};
  s21::multiset<int> m3 = {1, 2, 3, 4, 5};
  s21::multiset<int> m2 = std::move(m1);
  EXPECT_EQ(m1.size(), 0);
  EXPECT_EQ(m1.empty(), 1);
  auto it1 = m2.begin();
  for (auto it2 = m2.begin(); it2 != m2.end(); it1++, it2++)
    EXPECT_EQ((*it1), (*it2));
}

TEST(multiset_test, begin) {
  s21::multiset<int> m1 = {1};
  std::multiset<int> m2 = {1};
  auto it1 = m1.begin();
  auto it2 = m2.begin();
  EXPECT_EQ((*it1), (*it2));
}

TEST(multiset_test, beginLap) {
  s21::multiset<int> m1 = {1};
  std::multiset<int> m2 = {1};
  auto it1 = m1.begin();
  it1--;
  auto it2 = m2.begin();
  it2--;
  EXPECT_EQ((*it1), (*it2));
}

TEST(multiset_test, end) {
  s21::multiset<int> m1 = {1, 2, 3, 4, 5};
  std::multiset<int> m2 = {1, 2, 3, 4, 5};
  auto it1 = m1.end();
  auto it2 = m2.end();
  it1--, it2--;
  EXPECT_EQ((*it2), (*it1));
}

TEST(multiset_test, endLap) {
  s21::multiset<int> m1 = {1, 2, 3, 4, 5};
  std::multiset<int> m2 = {1, 2, 3, 4, 5};
  auto it1 = m1.end();
  auto it2 = m2.end();
  it1++, it2++;
  EXPECT_EQ((*it2), (*it1));
}

TEST(multiset_test, backPrintTest) {
  s21::multiset<int> m1 = {60, 58, 63, 1, 59, 61, 65};
  std::multiset<int> m2 = {60, 58, 63, 1, 59, 61, 65};
  auto it1 = m1.end();
  --it1;
  auto it2 = m2.end();
  --it2;
  for (; it1 != m1.begin() && it2 != m2.begin(); --it1, --it2) {
    EXPECT_EQ(*(it1), *(it2));
  }
}

TEST(multiset_test, emptyFalse) {
  s21::multiset<int> m1 = {1, 2, 3, 4, 5};
  std::multiset<int> m2 = {1, 2, 3, 4, 5};
  EXPECT_EQ(m1.empty(), m2.empty());
}

TEST(multiset_test, emptyTrue) {
  s21::multiset<int> m1;
  std::multiset<int> m2;
  EXPECT_EQ(m1.empty(), m2.empty());
}

TEST(multiset_test, size) {
  s21::multiset<int> m1;
  std::multiset<int> m2;
  m1.insert(1);
  m2.insert(1);
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(multiset_test, sizeZero) {
  s21::multiset<int> m1;
  std::multiset<int> m2;
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(multiset_test, clear) {
  s21::multiset<int> m1 = {1, 2, 3, 4, 5};
  std::multiset<int> m2 = {1, 2, 3, 4, 5};
  m1.clear();
  m2.clear();
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m1.empty(), m2.empty());
}

TEST(multiset_test, clearEmpty) {
  s21::multiset<int> m1;
  std::multiset<int> m2;
  m1.clear();
  m2.clear();
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m1.empty(), m2.empty());
}

TEST(multiset_test, Insert) {
  s21::multiset<int> m1;
  std::multiset<int> m2;

  auto s_pr = m1.insert(1);
  auto o_pr = m2.insert(1);
  EXPECT_EQ(*s_pr, *o_pr);

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

TEST(multiset_test, Erase) {
  s21::multiset<int> m1;
  std::multiset<int> m2;

  m1.insert(1);
  m2.insert(1);

  auto s_pr = m1.insert(2);
  auto o_pr = m2.insert(2);
  m1.erase(s_pr);
  m2.erase(o_pr);

  auto si = m1.begin();
  auto oi = m2.begin();
  for (; si != m1.end() && oi != m2.end(); ++si, ++oi) {
    EXPECT_EQ(*(si), *(oi));
  }
}

TEST(multiset_test, Erase_2) {
  s21::multiset<int> m1{10, 5, 8, 4, 3, 15};
  std::multiset<int> m2{10, 5, 8, 4, 3, 15};

  auto s_pr = m1.find(5);
  auto o_pr = m2.find(5);

  m1.erase(s_pr);
  m2.erase(o_pr);

  auto si = m1.begin();
  auto oi = m2.begin();
  for (; si != m1.end() && oi != m2.end(); ++si, ++oi) {
    EXPECT_EQ(*(si), *(oi));
  }
}

TEST(multiset_test, Erase_3) {
  s21::multiset<int> m1{10, 5};
  std::multiset<int> m2{10, 5};

  auto s_pr = m1.find(5);
  auto o_pr = m2.find(5);

  m1.erase(s_pr);
  m2.erase(o_pr);

  auto si = m1.begin();
  auto oi = m2.begin();
  for (; si != m1.end() && oi != m2.end(); ++si, ++oi) {
    EXPECT_EQ(*(si), *(oi));
  }
}

TEST(multiset_test, Erase_4) {
  s21::multiset<int> m1{10, 5, 20, 16, 17};
  std::multiset<int> m2{10, 5, 20, 16, 17};

  auto s_pr = m1.find(17);
  auto o_pr = m2.find(17);

  m1.erase(s_pr);
  m2.erase(o_pr);

  auto si = m1.begin();
  auto oi = m2.begin();
  for (; si != m1.end() && oi != m2.end(); ++si, ++oi) {
    EXPECT_EQ(*(si), *(oi));
  }
}

TEST(multiset_test, Erase_5) {
  s21::multiset<int> m1{10, 5, 4};
  std::multiset<int> m2{10, 5, 4};

  auto s_pr = m1.find(5);
  auto o_pr = m2.find(5);

  m1.erase(s_pr);
  m2.erase(o_pr);

  auto si = m1.begin();
  auto oi = m2.begin();
  for (; si != m1.end() && oi != m2.end(); ++si, ++oi) {
    EXPECT_EQ(*(si), *(oi));
  }
}

TEST(multiset_test, Erase_6) {
  s21::multiset<int> m1{10};
  std::multiset<int> m2{10};

  auto s_pr = m1.find(10);
  auto o_pr = m2.find(10);

  m1.erase(s_pr);
  m2.erase(o_pr);

  auto si = m1.begin();
  auto oi = m2.begin();

  EXPECT_EQ(*(si), *(oi));
}

TEST(multiset_test, Erase_7) {
  s21::multiset<int> m1{10, 11};
  std::multiset<int> m2{10, 11};

  auto s_pr = m1.find(10);
  auto o_pr = m2.find(10);

  m1.erase(s_pr);
  m2.erase(o_pr);

  auto si = m1.begin();
  auto oi = m2.begin();
  for (; si != m1.end() && oi != m2.end(); ++si, ++oi) {
    EXPECT_EQ(*(si), *(oi));
  }
}

TEST(multiset_test, EraseOneChild) {
  s21::multiset<int> m1{1, 2, 3};
  auto it = m1.find(2);
  m1.erase(it);
  EXPECT_EQ(m1.contains(2), false);
}

TEST(multiset_test, EraseOneChild2) {
  s21::multiset<int> m1{2};
  auto it = m1.find(2);
  m1.erase(it);
  EXPECT_EQ(m1.contains(2), false);
}

TEST(multiset_test, EraseTwoChild) {
  s21::multiset<int> m1{2, 1, 3};
  auto it = m1.find(2);
  m1.erase(it);
  EXPECT_EQ(m1.contains(2), false);
}

TEST(multiset_test, MergeTwoChildTop) {
  s21::multiset<int> m1{3, 1, 2, 0};
  s21::multiset<int> m2;
  m2.merge(m1);
  EXPECT_EQ(m1.contains(1), false);
}

TEST(multiset_test, InsertAlreadyHave) {
  s21::multiset<int> m1;
  std::multiset<int> m2;
  m1.insert(1);
  auto s_pr2 = m1.insert(1);
  m2.insert(1);
  auto o_pr2 = m2.insert(1);
  EXPECT_EQ(*s_pr2, *o_pr2);
}

TEST(multiset_test, Swap) {
  s21::multiset<std::string> f_s_tree = {
      {"zero"}, {"one"}, {"two"},   {"three"}, {"four"},
      {"five"}, {"six"}, {"seven"}, {"eight"}, {"nine"}};

  s21::multiset<std::string> s_s_tree = {{"ten"},    {"twenty"}, {"thirty"},
                                         {"fourty"}, {"fifty"},  {"sixty"},
                                         {"seventy"}};

  std::multiset<std::string> f_o_tree = {
      {"zero"}, {"one"}, {"two"},   {"three"}, {"four"},
      {"five"}, {"six"}, {"seven"}, {"eight"}, {"nine"}};

  std::multiset<std::string> s_o_tree = {{"ten"},    {"twenty"}, {"thirty"},
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

TEST(multiset_test, Merge) {
  s21::multiset<int> s1{1, 2, 3};
  s21::multiset<int> s2{3, 4, 5};
  std::multiset<int> s3{1, 2, 3};
  std::multiset<int> s4{3, 4, 5};
  s1.merge(s2);
  s3.merge(s4);
  EXPECT_EQ(s1.size(), s3.size());
  auto i = s1.begin();
  auto j = s3.begin();
  for (; i != s1.end(), j != s3.end(); ++i, ++j) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(multiset_test, MergeEmpty) {
  s21::multiset<int> s1;
  s21::multiset<int> s2{3, 4, 5};
  std::multiset<int> s3;
  std::multiset<int> s4{3, 4, 5};
  s1.merge(s2);
  s3.merge(s4);
  EXPECT_EQ(s1.size(), s3.size());
  auto i = s1.begin();
  auto j = s3.begin();
  for (; i != s1.end(), j != s3.end(); ++i, ++j) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(multiset_test, Merge2) {
  s21::multiset<int> s1{1, 2, 3, 4, 5, 6, 7, 8};
  s21::multiset<int> s2{9, -1, 3};
  std::multiset<int> s3{1, 2, 3, 4, 5, 6, 7, 8};
  std::multiset<int> s4{9, -1, 3};
  s1.merge(s2);
  s3.merge(s4);
  EXPECT_EQ(s1.size(), s3.size());
  auto i = s1.begin();
  auto j = s3.begin();
  for (; i != s1.end(), j != s3.end(); ++i, ++j) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(multiset_test, Merge3) {
  s21::multiset<int> s1{10, 2, 3};
  s21::multiset<int> s2{1, 2};
  std::multiset<int> s3{10, 2, 3};
  std::multiset<int> s4{1, 2};
  s1.merge(s2);
  s3.merge(s4);
  EXPECT_EQ(s1.size(), s3.size());
  auto i = s1.begin();
  auto j = s3.begin();
  for (; i != s1.end(), j != s3.end(); ++i, ++j) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(multiset_test, MergeIteratorsTest) {
  s21::multiset<int> s1{1, 2, 3};
  s21::multiset<int> s2{3, 4, 5};
  std::multiset<int> s3{1, 2, 3};
  std::multiset<int> s4{3, 4, 5};
  auto test1 = s2.begin();
  auto test2 = s4.begin();
  s1.merge(s2);
  s3.merge(s4);
  EXPECT_EQ(s1.size(), s3.size());
  auto i = s1.begin();
  auto j = s3.begin();
  for (; i != s1.end(), j != s3.end(); ++i, ++j) {
    EXPECT_EQ(*i, *j);
  }
  EXPECT_EQ(*test1, *test2);
}

TEST(multiset_test, containsTrue) {
  s21::multiset<int> m1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(m1.contains(1), true);
}

TEST(multiset_test, containsFalse) {
  s21::multiset<int> m1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(m1.contains(0), false);
}

TEST(multiset_test, Max_size) {
  s21::multiset<int> m1 = {1, 2, 3, 4, 5};
  std::multiset<int> m2 = {1, 2, 3, 4, 5};

  EXPECT_EQ(m1.max_size(), m2.max_size());
}

TEST(multiset_test, Operator) {
  s21::multiset<int> m1 = {1, 2, 3, 4, 5};
  s21::multiset<int> &m2 = m1;

  auto it1 = m1.begin();
  for (auto it2 = m2.begin(); it2 != m2.end(); it1++, it2++)
    EXPECT_EQ((*it1), (*it2));
}

TEST(multiset_test, Count) {
  s21::multiset<int> m1 = {1, 2, 3, 4, 5, 1};
  std::multiset<int> m2 = {1, 2, 3, 4, 5, 1};
  EXPECT_EQ(m1.count(1), m2.count(1));
}

TEST(multiset_test, Find) {
  s21::multiset<int> m1 = {1, 2, 3, 4, 5};
  std::multiset<int> m2 = {1, 2, 3, 4, 5};

  EXPECT_EQ(*m1.find(0), *m2.find(0));
  EXPECT_EQ(*m1.find(1), *m2.find(1));
}

TEST(multiset_test, equal_range) {
  s21::multiset<int> m1 = {1, 2, 3, 4, 5, 1};
  auto its = m1.equal_range(1);
  std::multiset<int> m2 = {1, 2, 3, 4, 5, 1};
  auto its2 = m2.equal_range(1);
  EXPECT_EQ((*its.first), (*its2.first));
}

TEST(multiset_test, upper_bound) {
  s21::multiset<int> m1 = {1, 2, 3, 4, 5, 1};
  auto its = m1.upper_bound(1);
  std::multiset<int> m2 = {1, 2, 3, 4, 5, 1};
  auto its2 = m2.upper_bound(1);
  EXPECT_EQ((*its), (*its2));
}

TEST(multiset_test, upper_bound_2) {
  s21::multiset<int> m1 = {1, 2, 3, 4, 5, 1};
  auto its = m1.upper_bound(6);
  std::multiset<int> m2 = {1, 2, 3, 4, 5, 1};
  auto its2 = m2.upper_bound(6);
  EXPECT_EQ((*its), (*its2));
}

TEST(multiset_test, upper_bound_3) {
  s21::multiset<int> m1 = {10, 5, 15, 7};
  auto its = m1.upper_bound(6);
  std::multiset<int> m2 = {10, 5, 15, 7};
  auto its2 = m2.upper_bound(6);
  EXPECT_EQ((*its), (*its2));
}

TEST(multiset_test, upper_bound_4) {
  s21::multiset<int> m1 = {10, 5, 15, 7};
  auto its = m1.upper_bound(50);
  std::multiset<int> m2 = {10, 5, 15, 7};
  auto its2 = m2.upper_bound(50);
  EXPECT_EQ((*its), (*its2));
}

TEST(multiset_test, lower_bound) {
  s21::multiset<int> m1 = {1, 2, 3, 4, 5, 1};
  auto its = m1.lower_bound(1);
  std::multiset<int> m2 = {1, 2, 3, 4, 5, 1};
  auto its2 = m2.lower_bound(1);
  EXPECT_EQ((*its), (*its2));
}

TEST(multiset_test, lower_bound_2) {
  s21::multiset<int> m1 = {10, 3, 11, 15};
  auto its = m1.lower_bound(5);
  s21::multiset<int> m2 = {10, 3, 11, 15};
  auto its2 = m2.lower_bound(5);
  EXPECT_EQ((*its), (*its2));
}

TEST(multiset_test, lower_bound_3) {
  s21::multiset<int> m1 = {10, 3, 11, 15};
  auto its = m1.lower_bound(2);
  s21::multiset<int> m2 = {10, 3, 11, 15};
  auto its2 = m2.lower_bound(2);
  EXPECT_EQ((*its), (*its2));
}

TEST(multiset_test, lower_bound_4) {
  s21::multiset<int> m1 = {10, 3, 11, 15};
  auto its = m1.lower_bound(16);
  s21::multiset<int> m2 = {10, 3, 11, 15};
  auto its2 = m2.lower_bound(16);
  EXPECT_EQ((*its), (*its2));
}

TEST(multiset_test, Emplace) {
  s21::multiset<int> m1 = {10, 3, 11, 15};
  std::multiset<int> m2 = {10, 3, 11, 15};
  m1.emplace(14);
  m2.emplace(14);

  auto i = m1.begin();
  auto j = m2.begin();
  for (; i != m1.end() && j != m2.end(); ++i, ++j) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(multiset_test, Emplace_2) {
  s21::multiset<int> m1 = {10, 3, 11, 15};
  std::multiset<int> m2 = {10, 3, 11, 15, 14, 73, 35, 67, 21, 5, 7, 8};
  m1.emplace(14, 73, 35, 67, 21, 5, 7, 8);

  auto i = m1.begin();
  auto j = m2.begin();
  for (; i != m1.end() && j != m2.end(); ++i, ++j) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(multiset_test, CopyAssign) {
  s21::multiset<int> m1 = {10, 3, 11, 15};
  s21::multiset<int> m2;
  m2 = m1;
  auto i = m1.begin();
  auto j = m2.begin();
  for (; i != m1.end() && j != m2.end(); ++i, ++j) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(multiset_test, MoveAssign) {
  s21::multiset<int> m1 = {10, 3, 11, 15};
  s21::multiset<int> m2;
  m2 = std::move(m1);
  s21::multiset<int> m3 = {10, 3, 11, 15};
  auto i = m2.begin();
  auto j = m3.begin();
  for (; i != m2.end() && j != m3.end(); ++i, ++j) {
    EXPECT_EQ(*i, *j);
  }
  EXPECT_EQ(m1.empty(), true);
}

TEST(multiset_test, ConstTest) {
  const s21::multiset<int> m1 = {10, 3, 11, 15};
  auto i = m1.begin();
  auto j = m1.end();
  EXPECT_EQ(*i, 3);
  EXPECT_EQ(*--j, 15);
}

TEST(multiset_test, IterEq) {
  const s21::multiset<int> m1 = {10, 3, 11, 15};
  auto i = m1.begin();
  auto j = m1.begin();
  bool res = false;
  if (i == j) res = true;
  EXPECT_EQ(res, true);
}

TEST(multiset_test, ConstBoundsTest) {
  const s21::multiset<int> m1 = {10, 10, 10, 3, 11, 15};
  const std::multiset<int> m2 = {10, 10, 10, 3, 11, 15};
  auto i = m1.equal_range(10);
  auto j = m2.equal_range(10);
  EXPECT_EQ(*i.first, *j.first);
  EXPECT_EQ(*i.second, *j.second);
}

TEST(multiset_test, ConstBoundsTest_2) {
  const s21::multiset<int> m1 = {10, 10, 10, 3, 11, 15};
  const std::multiset<int> m2 = {10, 10, 10, 3, 11, 15};
  auto i = m1.upper_bound(11);
  auto j = m2.upper_bound(11);
  EXPECT_EQ(*i, *j);
}

TEST(multiset_test, ConstBoundsTest_3) {
  const s21::multiset<int> m1 = {10, 10, 10, 3, 11, 15};
  const std::multiset<int> m2 = {10, 10, 10, 3, 11, 15};
  auto i = m1.lower_bound(11);
  auto j = m2.lower_bound(11);
  EXPECT_EQ(*i, *j);
}

// throw cause leaks on Mac

// TEST(multiset_test, throw_test) {
//   s21::multiset<int> m1 = {10, 3, 11, 15};
//   auto it = m1.end();
//   EXPECT_ANY_THROW(m1.erase(it));
// }
