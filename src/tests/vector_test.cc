#include <gtest/gtest.h>

#include <array>
#include <vector>

#include "../s21_containers.h"

TEST(VectorTest, 1) {
  s21::vector<std::string> one{"1", "2", "3"};
  std::vector<std::string> two{"1", "2", "3"};
  ASSERT_EQ(one.at(1), two.at(1));
}

TEST(VectorTest, 3) {
  s21::vector<int> one{1, 2, 3};
  int test = one[1];
  ASSERT_EQ(test, 2);
}

TEST(VectorTest, 4) {
  const s21::vector<int> one{1, 2, 3};
  int test = one[1];
  ASSERT_EQ(test, 2);
}

TEST(VectorTest, 5) {
  s21::vector<int> one{1, 2, 3};
  int test = one.front();
  ASSERT_EQ(test, 1);
}

TEST(VectorTest, 6) {
  const s21::vector<double> one{1.5252, 2.25255, 3.25255};
  const std::vector<double> two{1.5252, 2.25255, 3.25255};
  ASSERT_EQ(one.front(), two.front());
}

TEST(VectorTest, 7) {
  s21::vector<int> one{1, 2, 3};
  int test = one.back();
  ASSERT_EQ(test, 3);
}

TEST(VectorTest, 8) {
  const s21::vector<int> one{1, 2, 3};
  int test = one.back();
  ASSERT_EQ(test, 3);
}

TEST(VectorTest, 9) {
  s21::vector<int> one{1, 2, 3};
  int test = *one.data();
  ASSERT_EQ(test, 1);
}

TEST(VectorTest, 10) {
  const s21::vector<int> one{1, 2, 3};
  int test = *one.data() + 2;
  ASSERT_EQ(test, 3);
}

TEST(VectorTest, 11) {
  s21::vector<int> one{1, 2, 3};
  auto i = one.begin();
  ASSERT_EQ(*i, 1);
}

TEST(VectorTest, 12) {
  s21::vector<int> one{1, 2, 3};
  auto i = one.begin();
  ++i;
  i++;
  ASSERT_EQ(*i, 3);
}

TEST(VectorTest, 13) {
  const s21::vector<int> one{1, 2, 3};
  auto i = one.begin();
  ++i;
  i++;
  --i;
  ASSERT_EQ(*i, 2);
}

TEST(VectorTest, 14) {
  s21::vector<int> one{1, 2, 3};
  auto i = one.end();
  --i;
  ASSERT_EQ(*i, 3);
}

TEST(VectorTest, 15) {
  const s21::vector<int> one{1, 2, 3};
  auto i = one.end();
  i--;
  ASSERT_EQ(*i, 3);
}

TEST(VectorTest, 16) {
  s21::vector<int> one{1, 2, 3};
  auto i = one.size();
  ASSERT_EQ(i, 3);
}

TEST(VectorTest, 17) {
  s21::vector<int> one{1, 2, 3};
  auto i = one.max_size();
  ASSERT_EQ(i, 2305843009213693951);
}

TEST(VectorTest, 18) {
  s21::vector<int> one{1, 2, 3};
  one.clear();
  ASSERT_EQ(one.empty(), true);
}

TEST(VectorTest, 19) {
  s21::vector<int> one{1, 2, 3};
  one.reserve(10);
  ASSERT_EQ(one.capacity(), 10);
}

TEST(VectorTest, 20) {
  s21::vector<int> one{1, 2, 3};
  one.reserve(3);
  ASSERT_EQ(one.capacity(), 3);
}

TEST(VectorTest, 21) {
  s21::vector<int> one{1, 2, 3};
  one.reserve(10);
  one.shrink_to_fit();
  ASSERT_EQ(one.capacity(), 3);
}

TEST(VectorTest, 22) {
  s21::vector<int> one{1, 3, 4};
  s21::vector<int> two{1, 2, 3, 4};
  auto i = one.begin();
  ++i;
  one.insert(i, 2);
  for (size_t j = 0; j < one.size(); ++j) {
    ASSERT_EQ(one[j], two[j]);
  }
}

TEST(VectorTest, 23) {
  s21::vector<int> one;
  s21::vector<int> two(one);
  auto i = one.begin();
  one.insert(i, 2);
  ASSERT_EQ(one[0], 2);
}

TEST(VectorTest, 24) {
  s21::vector<int> one;
  s21::vector<int> two(std::move(one));
  s21::vector<int> test{1, 2, 3, 4};
  two.push_back(1);
  two.push_back(3);
  two.push_back(4);
  auto i = two.begin();
  ++i;
  two.insert(i, 2);
  for (size_t j = 0; j < two.size(); ++j) {
    ASSERT_EQ(two[j], test[j]);
  }
}

TEST(VectorTest, 25) {
  s21::vector<int> one;
  s21::vector<int> two;
  two = one;
  s21::vector<int> test{1, 2, 3, 4};
  two.push_back(1);
  two.push_back(3);
  two.push_back(4);
  two.reserve(10);
  auto i = two.begin();
  ++i;
  two.insert(i, 2);
  for (size_t j = 0; j < two.size(); ++j) {
    ASSERT_EQ(two[j], test[j]);
  }
}

TEST(VectorTest, 28) {
  s21::vector<int> one{1, 1, 2, 3, 4};
  s21::vector<int> test{1, 2, 3, 4};
  auto i = one.begin();
  ++i;
  one.erase(i);
  for (size_t j = 0; j < one.size(); ++j) {
    ASSERT_EQ(one[j], test[j]);
  }
}

TEST(VectorTest, 29) {
  s21::vector<int> one{69};
  s21::vector<int> test{21};
  one.swap(test);

  ASSERT_EQ(one[0], 21);
  ASSERT_EQ(test[0], 69);
}

TEST(VectorTest, 30) {
  s21::vector<std::string> one{"69", "70", "80"};
  std::vector<std::string> two{"69", "70"};
  one.pop_back();

  for (size_t i = 0, j = 0; i < one.size() && j < two.size(); ++i, ++j) {
    ASSERT_EQ(one[i], two[i]);
  }
}

TEST(VectorTest, 31) {
  s21::vector<int> one{69, 70, 80};
  s21::vector<int> test{69, 70, 80};
  size_t j = 0;
  for (auto i = one.begin(); i != one.end(), j < test.size(); ++i, ++j) {
    ASSERT_EQ(*i, test[j]);
  }
}

TEST(VectorTest, 32) {
  s21::vector<int> one{69, 70, 80};
  auto i = one.begin();
  auto t = one.end();
  t--;
  --t;
  --t;
  ASSERT_EQ(*i, *t);
}

TEST(VectorTest, 33) {
  s21::vector<int> one{69, 70, 80};
  std::vector<int> two{69, 70, 80};
  one.emplace(one.begin(), 100);
  two.emplace(two.begin(), 100);
  auto it = one.begin();
  auto jt = two.begin();
  for (; it != one.end() && jt != two.end(); ++it, ++jt) {
    ASSERT_EQ(*it, *jt);
  }
}

TEST(VectorTest, 34) {
  s21::vector<int> one{69, 70, 80};
  std::vector<int> two{69, 70, 80};
  one.emplace_back(100);
  two.emplace_back(100);
  auto it = one.begin();
  auto jt = two.begin();
  for (; it != one.end() && jt != two.end(); ++it, ++jt) {
    ASSERT_EQ(*it, *jt);
  }
}

TEST(VectorTest, 35) {
  const s21::vector<int> one{69, 70, 80};
  const std::vector<int> two{69, 70, 80};

  ASSERT_EQ(one.at(2), two.at(2));
}

TEST(VectorTest, 36) {
  s21::vector<int> one{69, 70, 80};
  std::vector<int> two{69, 70, 80};
  s21::vector<int> three;
  std::vector<int> four;
  three = std::move(one);
  four = std::move(two);

  auto it = three.begin();
  auto jt = four.begin();
  for (; it != three.end() && jt != four.end(); ++it, ++jt) {
    ASSERT_EQ(*it, *jt);
  }
}

TEST(VectorTest, 37) {
  const s21::vector<int> one{69, 70, 80};

  auto it = one.begin();
  auto it2 = one.begin();

  bool res = false;
  if (it == it2) res = true;
  ASSERT_EQ(res, true);

  for (; it != one.end(); ++it) {
    ASSERT_EQ(*it, *it);
  }
}

// leaks on mac

// TEST(VectorTest, 2) {
//   EXPECT_ANY_THROW(s21::vector<int> one(2305843009213693952));
// }

// TEST(VectorTest, 26) {
//   s21::vector<int> one;
//   s21::vector<int> two;
//   two = std::move(one);
//   two.push_back(1);

//   EXPECT_ANY_THROW(two.at(-5));
// }

// TEST(VectorTest, 27) {
//   const s21::vector<int> one{1, 2, 3};
//   ASSERT_EQ(one.at(1), 2);
//   EXPECT_ANY_THROW(one.at(-5));
// }

// TEST(VectorTest, Erase) {
//   s21::vector<int> m1 = {10, 3, 11, 15};
//   auto it = m1.end();
//   EXPECT_ANY_THROW(m1.erase(it));
// }
