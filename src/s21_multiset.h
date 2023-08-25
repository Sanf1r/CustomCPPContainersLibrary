#ifndef SRC_S21_MULTISET_H_
#define SRC_S21_MULTISET_H_

#include "s21_vector.h"

namespace s21 {
template <typename Key>
class multiset {
  class BinaryTreeNode;

 public:
  // Multiset Member type
  class TreeIterator;
  using key_type = Key;
  using value_type = Key;
  using node = BinaryTreeNode;
  using iterator = TreeIterator;
  using const_iterator = TreeIterator;
  using pointer_to_node = BinaryTreeNode*;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

  // Public class of Iterator
  class TreeIterator {
    friend class multiset;

   public:
    using value_type = Key;
    using pointer_to_node = BinaryTreeNode*;
    using const_reference = const value_type&;

   public:
    TreeIterator();
    explicit TreeIterator(pointer_to_node ptr);
    TreeIterator& operator++();
    TreeIterator operator++(int);
    TreeIterator& operator--();
    TreeIterator operator--(int);
    const_reference operator*() const;
    bool operator==(const TreeIterator& other);
    bool operator!=(const TreeIterator& other);

   private:
    pointer_to_node ptr_;
  };

  // Multiset Member functions
 public:
  multiset();
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& other);
  multiset(multiset&& other);
  ~multiset();

  multiset& operator=(const multiset& other);
  multiset& operator=(multiset&& other);

  // Multiset Iterators
  // begin() returns an iterator to the beginning
  iterator begin();
  const_iterator begin() const;
  // end() returns an iterator to the end
  iterator end();
  const_iterator end() const;

  // Multiset Capacity
  // empty() checks whether the container is empty
  bool empty() const;
  // size() returns the number of elements
  size_type size() const;
  // max_size() returns the maximum possible number of elements
  size_type max_size() const;

  // Multiset Modifiers
  // clear() clears the contents
  void clear();
  // insert() inserts node and returns iterator to where the element is in the
  // container
  iterator insert(const value_type& value);
  // erase() erases element at pos
  void erase(iterator pos);
  // swap() swaps the contents
  void swap(multiset& other);
  // merge() splices nodes from another container
  void merge(multiset& other);

  // Multiset Lookup
  // count() returns the number of elements matching specific key
  size_type count(const value_type& key) const;
  // find() finds element with specific key
  iterator find(const value_type& key);
  const_iterator find(const value_type& key) const;
  // contains() checks if the container contains element with specific key
  bool contains(const value_type& key) const;
  // equal_range() returns range of elements matching a specific key
  std::pair<iterator, iterator> equal_range(const value_type& key);
  std::pair<const_iterator, const_iterator> equal_range(
      const value_type& key) const;
  // lower_bound() returns an iterator to the first element not less than the
  // given key
  iterator lower_bound(const value_type& key);
  const_iterator lower_bound(const value_type& key) const;
  // upper_bound() returns an iterator to the first element greater than the
  // given key
  iterator upper_bound(const value_type& key);
  const_iterator upper_bound(const value_type& key) const;

  // Multiset Emplace
  // emplace() inserts new elements into the container
  template <typename... Args>
  vector<std::pair<iterator, bool>> emplace(Args&&... args);

 private:
  pointer_to_node root_;
  pointer_to_node fake_node_;
  size_type size_ = 0;

  // Private Node class
  class BinaryTreeNode {
   public:
    using value_type = Key;
    using pointer_to_node = BinaryTreeNode*;

   public:
    BinaryTreeNode();
    BinaryTreeNode(value_type data, pointer_to_node top = nullptr,
                   pointer_to_node left = nullptr,
                   pointer_to_node right = nullptr);
    pointer_to_node NextNode();
    pointer_to_node PreviousNode();
    pointer_to_node FarLeft();
    pointer_to_node FarRight();
    pointer_to_node FarTop();
    void CleanNodePointers();

    value_type value_;
    pointer_to_node top_;
    pointer_to_node left_;
    pointer_to_node right_;
  };

  // Multiset Helper Methods
  void DeleteNodes(pointer_to_node node);
  pointer_to_node RecursiveFind(const value_type& value,
                                pointer_to_node node) const;
  void InsertForMerge(pointer_to_node node);
  void EraseLeafNode(pointer_to_node node_to_erase);
  void EraseNodeOneChildren(pointer_to_node node);
  void EraseNodeTwoChildren(pointer_to_node node);
  void WhileLoopForInsert(pointer_to_node node);
  void EraseLogicForMerge(multiset& other, pointer_to_node node);
  void EraseLogicForLeafNode(multiset& other, pointer_to_node node_to_erase);
  void EraseLogicForOneChildrenNode(multiset& other, pointer_to_node node);
  void RecursiveCopyWholeSet(pointer_to_node node, const multiset& other);
  iterator LowerBoundHelper(iterator& result, const Key& key) const;
  iterator UpperBoundHelper(iterator& result, const Key& key) const;
  std::pair<iterator, bool> InsertForEmplace(const value_type& value);
  void CopySwapWithStd(multiset& one, multiset& two) noexcept;
};

// TreeIterator class implementation

template <typename T>
multiset<T>::TreeIterator::TreeIterator() : ptr_(nullptr) {}

template <typename T>
multiset<T>::TreeIterator::TreeIterator(pointer_to_node ptr) : ptr_(ptr) {}

template <typename T>
typename multiset<T>::TreeIterator& multiset<T>::TreeIterator::operator++() {
  if (ptr_ == ptr_->FarTop()->FarRight()) {
    --(*this);
  } else {
    ptr_ = ptr_->NextNode();
  }
  return *this;
}

template <typename T>
typename multiset<T>::TreeIterator multiset<T>::TreeIterator::operator++(int) {
  TreeIterator temp = *this;
  ++(*this);
  return temp;
}

template <typename T>
typename multiset<T>::TreeIterator& multiset<T>::TreeIterator::operator--() {
  if (ptr_ == ptr_->FarTop()->FarLeft()) {
    ptr_ = ptr_->FarTop()->FarRight();
  } else {
    ptr_ = ptr_->PreviousNode();
  }
  return *this;
}

template <typename T>
typename multiset<T>::TreeIterator multiset<T>::TreeIterator::operator--(int) {
  TreeIterator temp = *this;
  --(*this);
  return temp;
}

template <typename T>
typename multiset<T>::TreeIterator::const_reference
multiset<T>::TreeIterator::operator*() const {
  return ptr_->value_;
}

template <typename T>
bool multiset<T>::TreeIterator::operator==(const TreeIterator& other) {
  return ptr_ == other.ptr_;
}

template <typename T>
bool multiset<T>::TreeIterator::operator!=(const TreeIterator& other) {
  return !(ptr_ == other.ptr_);
}

// BinaryNodeTree class implementation

template <typename T>
multiset<T>::BinaryTreeNode::BinaryTreeNode()
    : top_(nullptr), left_(nullptr), right_(nullptr) {}

template <typename T>
multiset<T>::BinaryTreeNode::BinaryTreeNode(value_type data,
                                            pointer_to_node top,
                                            pointer_to_node left,
                                            pointer_to_node right)
    : value_(data), top_(top), left_(left), right_(right) {}

template <typename T>
typename multiset<T>::BinaryTreeNode::pointer_to_node
multiset<T>::BinaryTreeNode::NextNode() {
  pointer_to_node temp = this;
  if (temp->right_) {
    temp = temp->right_;
    while (temp->left_) temp = temp->left_;
  } else {
    while (temp->top_ && temp == temp->top_->right_) {
      temp = temp->top_;
    }
    temp = temp->top_;
  }
  return temp;
}

template <typename T>
typename multiset<T>::BinaryTreeNode::pointer_to_node
multiset<T>::BinaryTreeNode::PreviousNode() {
  pointer_to_node temp = this;
  if (temp->left_) {
    temp = temp->left_;
    while (temp->right_) temp = temp->right_;
  } else {
    while (temp->top_ && temp == temp->top_->left_) {
      temp = temp->top_;
    }
    temp = temp->top_;
  }
  return temp;
}

template <typename T>
typename multiset<T>::BinaryTreeNode::pointer_to_node
multiset<T>::BinaryTreeNode::FarLeft() {
  pointer_to_node temp(this);
  while (temp->left_) temp = temp->left_;
  return temp;
}

template <typename T>
typename multiset<T>::BinaryTreeNode::pointer_to_node
multiset<T>::BinaryTreeNode::FarRight() {
  pointer_to_node temp(this);
  while (temp->right_) temp = temp->right_;
  return temp;
}

template <typename T>
typename multiset<T>::BinaryTreeNode::pointer_to_node
multiset<T>::BinaryTreeNode::FarTop() {
  pointer_to_node temp(this);
  while (temp->top_) temp = temp->top_;
  return temp;
}

template <typename T>
void multiset<T>::BinaryTreeNode::CleanNodePointers() {
  top_ = nullptr;
  left_ = nullptr;
  right_ = nullptr;
}

// Multiset class implementation

template <typename T>
multiset<T>::multiset() {
  root_ = new node();
  fake_node_ = new node();
  root_->right_ = fake_node_;
  fake_node_->top_ = root_;
}

template <typename T>
multiset<T>::multiset(std::initializer_list<value_type> const& items)
    : multiset() {
  for (auto ptr = items.begin(); ptr != items.end(); ++ptr) {
    insert(*ptr);
  }
}

template <typename T>
multiset<T>::multiset(const multiset& other) : multiset() {
  if (other.size_ > 0) {
    RecursiveCopyWholeSet(other.root_, other);
    size_ = other.size_;
  }
}

template <typename T>
multiset<T>::multiset(multiset&& other) : multiset() {
  CopySwapWithStd(*this, other);
  other.size_ = 0;
}

template <typename T>
multiset<T>::~multiset() {
  clear();
  delete fake_node_;
  delete root_;
}

template <typename T>
multiset<T>& multiset<T>::operator=(const multiset& other) {
  if (this != &other) {
    multiset<value_type> temp(other);
    CopySwapWithStd(*this, temp);
  }
  return *this;
}

template <typename T>
multiset<T>& multiset<T>::operator=(multiset&& other) {
  if (this != &other) {
    multiset<value_type> temp(std::move(other));
    CopySwapWithStd(*this, temp);
  }
  return *this;
}

template <typename T>
typename multiset<T>::iterator multiset<T>::begin() {
  return empty() ? end() : iterator(root_->FarLeft());
}

template <typename T>
typename multiset<T>::const_iterator multiset<T>::begin() const {
  return empty() ? end() : iterator(root_->FarLeft());
}

template <typename T>
typename multiset<T>::iterator multiset<T>::end() {
  return iterator(root_->FarRight());
}

template <typename T>
typename multiset<T>::const_iterator multiset<T>::end() const {
  return iterator(root_->FarRight());
}

template <typename T>
bool multiset<T>::empty() const {
  return size_ == 0;
}

template <typename T>
typename multiset<T>::size_type multiset<T>::size() const {
  return size_;
}

template <typename T>
typename multiset<T>::size_type multiset<T>::max_size() const {
  return SIZE_MAX / sizeof(value_type) / 20;
}

template <typename T>
void multiset<T>::clear() {
  DeleteNodes(root_);
  root_->left_ = nullptr;
  root_->right_ = fake_node_;
  fake_node_->top_ = root_;
  size_ = 0;
  fake_node_->value_ = size_;
}

template <typename T>
typename multiset<T>::iterator multiset<T>::insert(const value_type& value) {
  pointer_to_node temp = new node(value);
  iterator result;
  if (empty()) {
    root_->value_ = value;
    ++size_;
    fake_node_->value_ = size_;
    result.ptr_ = root_;
    delete temp;
  } else {
    WhileLoopForInsert(temp);
    ++size_;
    fake_node_->value_ = size_;
    result.ptr_ = temp;
  }
  return result;
}

template <typename T>
void multiset<T>::erase(iterator pos) {
  pointer_to_node current = pos.ptr_;
  // end cant be erase
  if (current == end().ptr_) {
    throw std::logic_error(
        "The end() iterator cannot be used as a value for pos\n");
    // if node is a leaf (got no children) or right children is fake
  } else if (!current->left_ &&
             (!current->right_ || current->right_ == fake_node_)) {
    EraseLeafNode(current);
    // if node got one childres (left OR right)
  } else if ((current->left_ && !current->right_) ||
             (!current->left_ && current->right_)) {
    EraseNodeOneChildren(current);
    // if node got two childrens
  } else if (current->left_ && current->right_) {
    EraseNodeTwoChildren(current);
  }
  --size_;
  fake_node_->value_ = size_;
}

template <typename T>
void multiset<T>::swap(multiset& other) {
  CopySwapWithStd(*this, other);
}

template <typename T>
void multiset<T>::merge(multiset& other) {
  for (auto i = other.root_->FarLeft(); i != other.root_->FarRight();) {
    pointer_to_node to_merge = i;
    i = i->NextNode();
    EraseLogicForMerge(other, to_merge);
    InsertForMerge(to_merge);
    ++size_;
    fake_node_->value_ = size_;
  }
}

template <typename T>
typename multiset<T>::size_type multiset<T>::count(
    const value_type& key) const {
  size_type result = 0;
  auto i = find(key);
  if (i != end()) {
    while (i.ptr_->value_ == key) {
      ++i;
      ++result;
    }
  }
  return result;
}

template <typename T>
typename multiset<T>::iterator multiset<T>::find(const value_type& key) {
  iterator result(RecursiveFind(key, root_));
  return result;
}

template <typename T>
typename multiset<T>::const_iterator multiset<T>::find(
    const value_type& key) const {
  const_iterator result(RecursiveFind(key, root_));
  return result;
}

template <typename T>
bool multiset<T>::contains(const value_type& key) const {
  bool result = false;
  if (RecursiveFind(key, root_) != end().ptr_) {
    result = true;
  }
  return result;
}

template <typename T>
std::pair<typename multiset<T>::iterator, typename multiset<T>::iterator>
multiset<T>::equal_range(const value_type& key) {
  iterator first, second;
  first = lower_bound(key);
  second = upper_bound(key);
  return std::pair<iterator, iterator>(first, second);
}

template <typename T>
std::pair<typename multiset<T>::const_iterator,
          typename multiset<T>::const_iterator>
multiset<T>::equal_range(const value_type& key) const {
  const_iterator first, second;
  first = lower_bound(key);
  second = upper_bound(key);
  return std::pair<const_iterator, const_iterator>(first, second);
}

template <typename T>
typename multiset<T>::iterator multiset<T>::lower_bound(const value_type& key) {
  iterator result = end();
  LowerBoundHelper(result, key);
  return result;
}

template <typename T>
typename multiset<T>::const_iterator multiset<T>::lower_bound(
    const value_type& key) const {
  const_iterator result = end();
  LowerBoundHelper(result, key);
  return result;
}

template <typename T>
typename multiset<T>::iterator multiset<T>::upper_bound(const value_type& key) {
  iterator result = end();
  UpperBoundHelper(result, key);
  return result;
}

template <typename T>
typename multiset<T>::const_iterator multiset<T>::upper_bound(
    const value_type& key) const {
  const_iterator result = end();
  UpperBoundHelper(result, key);
  return result;
}

template <typename T>
template <typename... Args>
vector<std::pair<typename multiset<T>::iterator, bool>> multiset<T>::emplace(
    Args&&... args) {
  vector<std::pair<iterator, bool>> result = {(InsertForEmplace(args))...};
  return result;
}

template <typename T>
void multiset<T>::DeleteNodes(pointer_to_node node) {
  if (node) {
    DeleteNodes(node->left_);
    DeleteNodes(node->right_);
    if (node != root_ && node != fake_node_) {
      delete node;
    }
  }
}

template <typename T>
typename multiset<T>::pointer_to_node multiset<T>::RecursiveFind(
    const value_type& value, pointer_to_node node) const {
  if (node == fake_node_ || size_ == 0 || !node) return end().ptr_;
  if (value == node->value_) {
    return (node->left_ && node->left_->value_ == value)
               ? RecursiveFind(value, node->left_)
               : node;
  } else {
    return (value < node->value_) ? RecursiveFind(value, node->left_)
                                  : RecursiveFind(value, node->right_);
  }
}

template <typename T>
void multiset<T>::InsertForMerge(pointer_to_node node) {
  node->CleanNodePointers();
  if (empty()) {
    delete root_;
    root_ = node;
    root_->right_ = fake_node_;
    fake_node_->top_ = root_;
  } else {
    WhileLoopForInsert(node);
  }
}

template <typename T>
void multiset<T>::EraseLeafNode(pointer_to_node node_to_erase) {
  if (node_to_erase == root_ && node_to_erase->right_ == fake_node_) {
    delete root_;
    root_ = new node();
    root_->right_ = fake_node_;
    fake_node_->top_ = root_;
    return;
  }
  if (node_to_erase->top_->left_ == node_to_erase) {
    node_to_erase->top_->left_ = nullptr;
  } else {
    if (node_to_erase->right_ == fake_node_) {
      node_to_erase->top_->right_ = fake_node_;
    } else {
      node_to_erase->top_->right_ = nullptr;
    }
  }
  delete node_to_erase;
}

template <typename T>
void multiset<T>::EraseNodeOneChildren(pointer_to_node node) {
  pointer_to_node child = (node->left_) ? node->left_ : node->right_;
  if (node != root_) {
    if (node == node->top_->left_) {
      node->top_->left_ = child;
      child->top_ = node->top_;
    } else {
      node->top_->right_ = child;
      child->top_ = node->top_;
    }
  } else {
    root_ = child;
    root_->top_ = nullptr;
  }
  delete node;
}

template <typename T>
void multiset<T>::EraseNodeTwoChildren(pointer_to_node node) {
  pointer_to_node prev = node->PreviousNode();
  pointer_to_node& parent_pointer =
      (prev == prev->top_->left_) ? prev->top_->left_ : prev->top_->right_;
  if (prev->left_) {
    prev->left_->top_ = prev->top_;
    parent_pointer = prev->left_;
  } else {
    parent_pointer = nullptr;
  }
  node->value_ = prev->value_;
  delete prev;
}

template <typename T>
void multiset<T>::WhileLoopForInsert(pointer_to_node node) {
  pointer_to_node current = root_;
  while (true) {
    if (node->value_ < current->value_) {
      if (current->left_ == nullptr) {
        current->left_ = node;
        node->top_ = current;
        break;
      } else {
        current = current->left_;
      }
    } else if ((node->value_ > current->value_) && current != fake_node_) {
      if (current->right_ == nullptr) {
        current->right_ = node;
        node->top_ = current;
        break;
      } else {
        current = current->right_;
      }
    } else if (current == fake_node_) {
      fake_node_->top_->right_ = node;
      node->top_ = fake_node_->top_;
      node->right_ = fake_node_;
      fake_node_->top_ = node;
      break;
    } else {
      if (current->left_) {
        node->top_ = current->left_->top_;
        node->left_ = current->left_;
        current->left_->top_ = node;
        current->left_ = node;
      } else {
        current->left_ = node;
        node->top_ = current;
      }
      break;
    }
  }
}

template <typename T>
void multiset<T>::EraseLogicForMerge(multiset& other, pointer_to_node node) {
  pointer_to_node current = node;
  if (!current->left_ &&
      (!current->right_ || current->right_ == other.fake_node_)) {
    EraseLogicForLeafNode(other, current);
  } else if ((current->left_ && !current->right_) ||
             (!current->left_ && current->right_)) {
    EraseLogicForOneChildrenNode(other, current);
  }
  --other.size_;
  other.fake_node_->value_ = other.size_;
}

template <typename T>
void multiset<T>::EraseLogicForLeafNode(multiset& other,
                                        pointer_to_node node_to_erase) {
  if (node_to_erase == other.root_ &&
      node_to_erase->right_ == other.fake_node_) {
    other.root_ = new node();
    other.root_->right_ = other.fake_node_;
    other.fake_node_->top_ = other.root_;
  } else {
    node_to_erase->top_->left_ = nullptr;
  }
}

template <typename T>
void multiset<T>::EraseLogicForOneChildrenNode(multiset& other,
                                               pointer_to_node node) {
  pointer_to_node child = (node->left_) ? node->left_ : node->right_;
  if (node != other.root_) {
    node->top_->left_ = child;
    child->top_ = node->top_;
  } else {
    other.root_ = child;
    other.root_->top_ = nullptr;
  }
}

template <typename T>
void multiset<T>::RecursiveCopyWholeSet(pointer_to_node node,
                                        const multiset& other) {
  if (empty()) insert(node->value_);
  if (node->left_) insert(node->left_->value_);
  if (node->right_ && node->right_ != other.fake_node_)
    insert(node->right_->value_);
  if (node->left_) RecursiveCopyWholeSet(node->left_, other);
  if (node->right_ && node->right_ != other.fake_node_)
    RecursiveCopyWholeSet(node->right_, other);
}

template <typename T>
typename multiset<T>::iterator multiset<T>::LowerBoundHelper(
    iterator& result, const value_type& key) const {
  pointer_to_node current = root_;
  while (true) {
    if (current->value_ < key) {
      if (current->right_) {
        current = current->right_;
      } else {
        break;
      }
    } else {
      result.ptr_ = current;
      if (current->left_) {
        current = current->left_;
      } else {
        break;
      }
    }
  }
  return result;
}

template <typename T>
typename multiset<T>::iterator multiset<T>::UpperBoundHelper(
    iterator& result, const value_type& key) const {
  pointer_to_node current = root_;
  while (true) {
    if (current->value_ <= key) {
      if (current->right_) {
        current = current->right_;
      } else {
        break;
      }
    } else {
      result.ptr_ = current;
      if (current->left_) {
        current = current->left_;
      } else {
        break;
      }
    }
  }
  return result;
}

template <typename T>
std::pair<typename multiset<T>::iterator, bool> multiset<T>::InsertForEmplace(
    const value_type& value) {
  auto result = insert(value);
  return std::pair<iterator, bool>(result, true);
}

template <typename T>
void multiset<T>::CopySwapWithStd(multiset& one, multiset& two) noexcept {
  std::swap(one.root_, two.root_);
  std::swap(one.fake_node_, two.fake_node_);
  std::swap(one.size_, two.size_);
}

}  // namespace s21

#endif  // SRC_S21_MULTISET_H_
