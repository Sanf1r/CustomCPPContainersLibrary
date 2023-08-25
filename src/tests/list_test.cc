#include <gtest/gtest.h>

#include "../s21_containers.h"

using namespace s21;

TEST(ListTest, DefaultConstructor) {
  List<int> list;
  EXPECT_EQ(list.size(), 0U);
  EXPECT_TRUE(list.empty());
}

TEST(ListTest, MoveAssignmentOperator) {
  List<int> list1;
  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);

  List<int> list2;
  list2 = std::move(list1);

  // Проверяем, что list1 теперь пуст
  EXPECT_TRUE(list1.empty());

  // Проверяем, что list2 теперь содержит копию данных из list1
  ASSERT_EQ(list2.size(), 3U);
  int expected_values2[] = {1, 2, 3};
  auto i = 0;
  for (auto it = list2.begin(); it != list2.end(); ++it, ++i) {
    EXPECT_EQ(*it, expected_values2[i]);
  }
}

TEST(ListTest, CopyAssignmentOperator) {
  List<int> list1;
  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);

  List<int> list2;
  list2 = list1;  // здесь используется оператор присваивания копированием

  // Проверяем, что list1 все еще содержит свои исходные данные
  ASSERT_EQ(list1.size(), 3U);
  int expected_values1[] = {1, 2, 3};
  int i = 0;
  for (auto it = list1.begin(); it != list1.end(); ++it, ++i) {
    EXPECT_EQ(*it, expected_values1[i]);
  }

  // Проверяем, что list2 теперь содержит копию данных из list1
  ASSERT_EQ(list2.size(), 3U);
  int expected_values2[] = {1, 2, 3};
  i = 0;
  for (auto it = list2.begin(); it != list2.end(); ++it, ++i) {
    EXPECT_EQ(*it, expected_values2[i]);
  }
}

TEST(ListTest, PushFrontAndBack) {
  List<int> list;

  list.push_front(1);
  EXPECT_EQ(list.size(), 1U);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 1);

  list.push_back(2);
  EXPECT_EQ(list.size(), 2U);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 2);
}

TEST(ListTest, PopFrontAndBack) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  list.pop_front();
  EXPECT_EQ(list.size(), 2U);
  EXPECT_EQ(list.front(), 2);

  list.pop_back();
  EXPECT_EQ(list.size(), 1U);
  EXPECT_EQ(list.back(), 2);
}

TEST(ListTest, ClearList) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.clear();
  EXPECT_EQ(list.size(), 0U);
  EXPECT_TRUE(list.empty());
}

TEST(ListTest, ReverseList) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.reverse();
  EXPECT_EQ(list.front(), 3);
  EXPECT_EQ(list.back(), 1);
}

TEST(ListTest, UniqueList) {
  List<int> list;
  list.push_back(1);
  list.push_back(1);
  list.push_back(2);
  list.push_back(2);
  list.push_back(3);
  list.push_back(3);
  list.unique();
  EXPECT_EQ(list.size(), 3U);
}

TEST(ListTest, SortList) {
  List<int> list;
  list.push_back(3);
  list.push_back(1);
  list.push_back(2);
  list.sort();
  List<int>::iterator it = list.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it, 3);
}

TEST(ListTest, SpliceTest) {
  List<int> list1;
  List<int> list2;

  for (int i = 0; i < 5; ++i) {
    list1.push_back(i);
  }

  for (int i = 5; i < 10; ++i) {
    list2.push_back(i);
  }

  list1.splice(list1.end(), list2);

  ASSERT_TRUE(list2.empty());

  ASSERT_EQ(list1.size(), static_cast<size_t>(10));

  int expected_value = 0;
  for (auto it = list1.begin(); it != list1.end(); ++it, ++expected_value) {
    ASSERT_EQ(*it, expected_value);
  }
}

TEST(ListTest, InsertAtEnd) {
  List<int> list = {1, 2, 3};
  auto it = list.insert(list.end(), 42);
  EXPECT_EQ(*it, 42);
  EXPECT_EQ(list.size(), 4U);
  EXPECT_EQ(list.back(), 42);
}

TEST(ListTest, InsertAtBeginning) {
  List<int> list = {1, 2, 3};
  auto it = list.insert(list.begin(), 42);
  EXPECT_EQ(*it, 42);
  EXPECT_EQ(list.size(), 4U);
  EXPECT_EQ(list.front(), 42);
}

TEST(ListTest, EraseFirstElement) {
  List<int> list = {1, 2, 3};
  auto it = list.erase(list.begin());
  EXPECT_EQ(*it, 2);
  EXPECT_EQ(list.size(), 2U);
  EXPECT_EQ(list.front(), 2);
  EXPECT_EQ(list.back(), 3);
}

TEST(ListTest, Sort) {
  // Create a list of integers with unsorted values
  List<int> list = {8, 3, 2, 10, 7, 4, 6, 1, 9, 5};

  // Sort the list
  list.sort();

  // Expected sorted list
  List<int> expected_list = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  // Check if the list is sorted as expected
  auto it1 = list.begin();
  auto it2 = expected_list.begin();
  while (it1 != list.end() && it2 != expected_list.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
  EXPECT_EQ(it1, list.end());
  EXPECT_EQ(it2, expected_list.end());
}

TEST(ListMergeTest, MergeTwoEmptyLists) {
  List<int> list1;
  List<int> list2;

  list1.merge(list2);

  EXPECT_EQ(list1.size(), 0U);
  EXPECT_EQ(list2.size(), 0U);
}

TEST(ListMergeTest, MergeNonEmptyAndEmptyLists) {
  List<int> list1;
  List<int> list2;

  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);

  list1.merge(list2);

  EXPECT_EQ(list1.size(), 3U);
  EXPECT_EQ(list2.size(), 0U);

  int expected[] = {1, 2, 3};
  int i = 0;

  for (auto it = list1.begin(); it != list1.end(); ++it, ++i) {
    EXPECT_EQ(*it, expected[i]);
  }
}

TEST(ListMergeTest, MergeEmptyAndNonEmptyLists) {
  List<int> list1;
  List<int> list2;

  list2.push_back(1);
  list2.push_back(2);
  list2.push_back(3);

  list1.merge(list2);

  EXPECT_EQ(list1.size(), 3U);
  EXPECT_EQ(list2.size(), 0U);

  int expected[] = {1, 2, 3};
  int i = 0;

  for (auto it = list1.begin(); it != list1.end(); ++it, ++i) {
    EXPECT_EQ(*it, expected[i]);
  }
}

TEST(ListMergeTest, MergeTwoNonEmptyLists) {
  List<int> list1;
  List<int> list2;

  list1.push_back(1);
  list1.push_back(3);
  list1.push_back(5);

  list2.push_back(2);
  list2.push_back(4);
  list2.push_back(6);

  list1.merge(list2);

  EXPECT_EQ(list1.size(), 6U);
  EXPECT_EQ(list2.size(), 0U);

  int expected[] = {1, 2, 3, 4, 5, 6};
  int i = 0;

  for (auto it = list1.begin(); it != list1.end(); ++it, ++i) {
    EXPECT_EQ(*it, expected[i]);
  }
}

TEST(ListTest, EmplaceBack) {
  List<int> list;

  list.emplace_back(1);
  list.emplace_back(2);
  list.emplace_back(3);

  ASSERT_EQ(list.size(), 3U);

  auto iter = list.begin();
  EXPECT_EQ(*iter, 1);
  ++iter;
  EXPECT_EQ(*iter, 2);
  ++iter;
  EXPECT_EQ(*iter, 3);
}

TEST(ListTest, EmplaceFront) {
  List<int> list;

  list.emplace_front(1);
  list.emplace_front(2);
  list.emplace_front(3);

  ASSERT_EQ(list.size(), 3U);

  auto iter = list.begin();
  EXPECT_EQ(*iter, 3);
  ++iter;
  EXPECT_EQ(*iter, 2);
  ++iter;
  EXPECT_EQ(*iter, 1);
}

TEST(ListTest, MaxSize) {
  List<int> list;
  const auto max_size = list.max_size();
  EXPECT_GT(max_size, 0U);
  EXPECT_GT(max_size, list.size());
  EXPECT_LT(max_size, std::numeric_limits<List<int>::size_type>::max());
}

TEST(ListTest, EmplaceInt) {
  List<int> list = {1, 2, 3};
  auto iter = list.begin();
  ++iter;
  auto it = list.emplace(iter, 4);
  EXPECT_EQ(*it, 4);
  EXPECT_EQ(list.size(), 4U);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 3);
}

TEST(ListTest, Emplace) {
  List<int> list;

  list.emplace_back(1);
  list.emplace_back(2);
  list.emplace_back(3);

  ASSERT_EQ(list.size(), 3U);

  auto iter = list.begin();
  EXPECT_EQ(*iter, 1);
  ++iter;
  EXPECT_EQ(*iter, 2);
  ++iter;
  EXPECT_EQ(*iter, 3);
}

// cause leaks on mac

// TEST(ListTest, FrontOnEmptyListThrowsException) {
//   List<int> empty_list;
//   EXPECT_THROW(empty_list.front(), std::out_of_range);
// }

// TEST(ListTest, BackOnEmptyListThrowsException) {
//   List<int> empty_list;
//   EXPECT_THROW(empty_list.back(), std::out_of_range);
// }

// TEST(ListTest, PopOnEmptyListThrowsException) {
//   List<int> empty_list;
//   EXPECT_THROW(empty_list.pop_back(), std::out_of_range);
// }

// TEST(ListTest, Pop_frontOnEmptyListThrowsException) {
//   List<int> empty_list;
//   EXPECT_THROW(empty_list.pop_front(), std::out_of_range);
// }

// TEST(ListTest, EraseOnEmptyListThrowsException) {
//   List<int> empty_list;
//   EXPECT_THROW(empty_list.erase(empty_list.begin()), std::out_of_range);
// }