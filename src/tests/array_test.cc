#include <gtest/gtest.h>

#include <array>

#include "../s21_containersplus.h"

// Array Test

TEST(ArrayTest, 1) {
  s21::array<int, 3> one{69, 70, 80};
  ASSERT_EQ(one.at(1), one[1]);
}

TEST(ArrayTest, 2) {
  const s21::array<int, 3> one{69, 70, 80};
  ASSERT_EQ(one.at(1), one[1]);
}

TEST(ArrayTest, 3) {
  s21::array<int, 3> one{69, 70, 80};
  ASSERT_EQ(one.front(), one[0]);
}

TEST(ArrayTest, 4) {
  const s21::array<int, 3> one{69, 70, 80};
  ASSERT_EQ(one.front(), one[0]);
}

TEST(ArrayTest, 5) {
  s21::array<int, 3> one{69, 70, 80};
  ASSERT_EQ(one.back(), one[2]);
}

TEST(ArrayTest, 6) {
  const s21::array<int, 3> one{69, 70, 80};
  ASSERT_EQ(one.back(), one[2]);
}

TEST(ArrayTest, 7) {
  s21::array<int, 3> one{69, 70, 80};
  ASSERT_EQ(*one.data(), one[0]);
}

TEST(ArrayTest, 8) {
  const s21::array<int, 3> one{69, 70, 80};
  ASSERT_EQ(*one.data(), one[0]);
}

TEST(ArrayTest, 9) {
  s21::array<int, 3> one{69, 70, 80};
  auto i = one.begin();
  ++i;
  ASSERT_EQ(*i, one[1]);
}

TEST(ArrayTest, 10) {
  const s21::array<int, 3> one{69, 70, 80};
  auto i = one.begin();
  ++i;
  ASSERT_EQ(*i, one[1]);
}

TEST(ArrayTest, 11) {
  s21::array<int, 3> one{69, 70, 80};
  auto i = one.end();
  --i;
  ASSERT_EQ(*i, one[2]);
}

TEST(ArrayTest, 12) {
  const s21::array<int, 3> one{69, 70, 80};
  auto i = one.end();
  --i;
  ASSERT_EQ(*i, one[2]);
}

TEST(ArrayTest, 13) {
  const s21::array<int, 3> one{1, 2, 3};
  ASSERT_EQ(one.empty(), false);
}

TEST(ArrayTest, 14) {
  s21::array<std::string, 3> one{"hello", "there", "01"};
  ASSERT_EQ(one.empty(), false);
}

TEST(ArrayTest, 17) {
  s21::array<int, 3> one{1, 2, 3};
  ASSERT_EQ(one.size(), 3);
}

TEST(ArrayTest, 18) {
  s21::array<int, 3> one{1, 2, 3};
  ASSERT_EQ(one.max_size(), 3);
}

TEST(ArrayTest, 19) {
  s21::array<int, 3> one{1, 2, 3};
  s21::array<int, 3> two{1, 2, 3};
  one.swap(two);
  for (size_t i = 0; i < one.size(); ++i) {
    ASSERT_EQ(one[i], two[i]);
  }
}

TEST(ArrayTest, 20) {
  s21::array<int, 3> one{1, 2, 3};
  s21::array<int, 3> two(one);
  two.fill(21);
  for (size_t i = 0; i < two.size(); ++i) {
    ASSERT_EQ(two[i], 21);
  }
}

TEST(ArrayTest, 21) {
  s21::array<int, 3> one{1, 2, 3};
  s21::array<int, 3> two(std::move(one));
  int t = 1;
  for (size_t i = 0; i < two.size(); ++i) {
    ASSERT_EQ(two[i], t);
    ++t;
  }
}

TEST(ArrayTest, 23) {
  s21::array<int, 5> one;
  s21::array<int, 5> two(one);
  s21::array<int, 5> three(std::move(one));
  two = one;
  three = std::move(two);
}

TEST(ArrayTest, 24) {
  const s21::array<int, 5> one{1, 2, 3, 4, 5};
  auto i = one.begin();
  auto j = one.begin();
  if (i == j) {
    ++i;
    if (i != j) return;
  }
}

TEST(ArrayTest, 25) {
  s21::array<int, 0> one;
  std::array<int, 0> two;
  ASSERT_EQ(one.size(), two.size());
}

TEST(ArrayTest, 26) {
  s21::array<std::string, 3> one{"1", "2", "3"};
  std::array<std::string, 3> two{"1", "2", "3"};
  auto it = one.begin();
  auto jt = two.begin();
  for (; it != one.end() && jt != two.end(); ++it, ++jt) {
    ASSERT_EQ(*it, *jt);
  }
}

TEST(ArrayTest, 27) {
  s21::array<std::string, 3> one{"1", "2", "3"};
  auto it = one.begin();
  auto jt = one.begin();
  it++;
  it--;
  bool res = false;
  if (it == jt) res = true;
  ASSERT_EQ(res, true);
}

TEST(ArrayTest, 28) {
  const s21::array<std::string, 3> one{"1", "2", "3"};
  auto it = one.begin();
  auto jt = one.begin();
  it++;
  it--;
  bool res = false;
  if (it == jt) res = true;
  ASSERT_EQ(res, true);
}

// cause leaks on mac

// TEST(ArrayTest, 15) {
//   s21::array<int, 3> one{1, 2, 3};
//   EXPECT_ANY_THROW(one.at(-4));
// }

// TEST(ArrayTest, 16) {
//   const s21::array<int, 3> one{1, 2, 3};
//   EXPECT_ANY_THROW(one.at(10));
// }

// TEST(ArrayTest, 22) {
//   try {
//     s21::array<int, 2> one{1, 2, 3};
//   } catch (std::out_of_range &e) {
//     ASSERT_EQ(e.what(), std::string("Too many initializers\n"));
//   }
// }