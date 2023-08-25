#ifndef SRC_S21_SET_H_
#define SRC_S21_SET_H_

#include "s21_vector.h"

namespace s21 {
template <typename Key>
class set {
  class BinaryTreeNode;

 public:
  // Set Member Type
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

  // Public class TreeIterator
  class TreeIterator {
    friend class set;

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

  // Set Member functions
  set();
  set(std::initializer_list<value_type> const& items);
  set(const set& other);
  set(set&& other);
  ~set();
  set& operator=(const set& other);
  set& operator=(set&& other);

  // Set Iterators
  // begin() returns an iterator to the beginning
  iterator begin();
  const_iterator begin() const;
  // end() returns an iterator to the end
  iterator end();
  const_iterator end() const;

  // Set Capacity
  // empty() checks whether the container is empty
  bool empty() const;
  // size() returns the number of elements
  size_type size() const;
  // max_size() returns the maximum possible number of elements
  size_type max_size() const;

  // Set Modifiers
  // // clear() clears the contents
  void clear();
  // insert() inserts node and returns iterator to where the element is in the
  // container
  std::pair<iterator, bool> insert(const value_type& value);
  // erase() erases element at pos
  void erase(iterator pos);
  // swap() swaps the contents
  void swap(set& other);
  // merge() splices nodes from another container
  void merge(set& other);

  // Set Lookup
  // // find() finds element with specific key
  iterator find(const value_type& key);
  const_iterator find(const value_type& key) const;
  // // contains() checks if the container contains element with specific key
  bool contains(const value_type& key) const;

  // Set Emplace
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
    BinaryTreeNode(const BinaryTreeNode& other);
    BinaryTreeNode(BinaryTreeNode&& other);
    ~BinaryTreeNode();
    BinaryTreeNode& operator=(const BinaryTreeNode& other);
    BinaryTreeNode& operator=(BinaryTreeNode&& other);
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

  // Set Helper Methods
  void DeleteNodes(pointer_to_node node);
  bool HelperForInsert(pointer_to_node node);
  pointer_to_node RecursiveFind(const value_type& value,
                                pointer_to_node node) const;
  void InsertForMerge(pointer_to_node node);
  void EraseLeafNode(pointer_to_node node_to_erase);
  void EraseNodeOneChildren(pointer_to_node node);
  void EraseNodeTwoChildren(pointer_to_node node);
  void WhileLoopForInsert(pointer_to_node node, bool& code);
  void EraseLogicForMerge(set& other, pointer_to_node node);
  void EraseLogicForLeafNode(set& other, pointer_to_node node_to_erase);
  void EraseLogicForOneChildrenNode(set& other, pointer_to_node node);
  void EraseLogicForTwoChildrenNode(set& other, pointer_to_node node_to_erase);
  void RecursiveCopyWholeSet(pointer_to_node node, const set& other);
  void CopySwapWithStd(set& one, set& two) noexcept;
};

// TreeIterator class implementation

template <typename T>
set<T>::TreeIterator::TreeIterator() : ptr_(nullptr) {}

template <typename T>
set<T>::TreeIterator::TreeIterator(pointer_to_node ptr) : ptr_(ptr) {}

template <typename T>
typename set<T>::TreeIterator& set<T>::TreeIterator::operator++() {
  if (ptr_ == ptr_->FarTop()->FarRight()) {
    --(*this);
  } else {
    ptr_ = ptr_->NextNode();
  }
  return *this;
}

template <typename T>
typename set<T>::TreeIterator set<T>::TreeIterator::operator++(int) {
  TreeIterator temp = *this;
  ++(*this);
  return temp;
}

template <typename T>
typename set<T>::TreeIterator& set<T>::TreeIterator::operator--() {
  if (ptr_ == ptr_->FarTop()->FarLeft()) {
    ptr_ = ptr_->FarTop()->FarRight();
  } else {
    ptr_ = ptr_->PreviousNode();
  }
  return *this;
}

template <typename T>
typename set<T>::TreeIterator::TreeIterator set<T>::TreeIterator::operator--(
    int) {
  TreeIterator temp = *this;
  --(*this);
  return temp;
}

template <typename T>
typename set<T>::TreeIterator::const_reference set<T>::TreeIterator::operator*()
    const {
  return ptr_->value_;
}

template <typename T>
bool set<T>::TreeIterator::operator==(const TreeIterator& other) {
  return ptr_ == other.ptr_;
}

template <typename T>
bool set<T>::TreeIterator::operator!=(const TreeIterator& other) {
  return !(ptr_ == other.ptr_);
}

// BinaryNodeTree class implementation

template <typename T>
set<T>::BinaryTreeNode::BinaryTreeNode()
    : top_(nullptr), left_(nullptr), right_(nullptr) {}

template <typename T>
set<T>::BinaryTreeNode::BinaryTreeNode(value_type data, pointer_to_node top,
                                       pointer_to_node left,
                                       pointer_to_node right)
    : value_(data), top_(top), left_(left), right_(right) {}

template <typename T>
set<T>::BinaryTreeNode::BinaryTreeNode(const BinaryTreeNode& other) {
  *this = other;
}

template <typename T>
set<T>::BinaryTreeNode::BinaryTreeNode(BinaryTreeNode&& other) = default;

template <typename T>
set<T>::BinaryTreeNode::~BinaryTreeNode() = default;

template <typename T>
typename set<T>::BinaryTreeNode& set<T>::BinaryTreeNode::operator=(
    const BinaryTreeNode& other) {
  if (this != &other) {
    value_ = other.value_;
    top_ = other.top_;
    left_ = other.left_;
    right_ = other.right_;
  }
  return *this;
}

template <typename T>
typename set<T>::BinaryTreeNode& set<T>::BinaryTreeNode::operator=(
    BinaryTreeNode&& other) = default;

template <typename T>
typename set<T>::BinaryTreeNode::pointer_to_node
set<T>::BinaryTreeNode::NextNode() {
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
typename set<T>::BinaryTreeNode::pointer_to_node
set<T>::BinaryTreeNode::PreviousNode() {
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
typename set<T>::BinaryTreeNode::pointer_to_node
set<T>::BinaryTreeNode::FarLeft() {
  pointer_to_node temp(this);
  while (temp->left_) temp = temp->left_;
  return temp;
}

template <typename T>
typename set<T>::BinaryTreeNode::pointer_to_node
set<T>::BinaryTreeNode::FarRight() {
  pointer_to_node temp(this);
  while (temp->right_) temp = temp->right_;
  return temp;
}

template <typename T>
typename set<T>::BinaryTreeNode::pointer_to_node
set<T>::BinaryTreeNode::FarTop() {
  pointer_to_node temp(this);
  while (temp->top_) temp = temp->top_;
  return temp;
}

template <typename T>
void set<T>::BinaryTreeNode::CleanNodePointers() {
  top_ = nullptr;
  left_ = nullptr;
  right_ = nullptr;
}

// Set class implementation

template <typename T>
set<T>::set() {
  root_ = new node();
  fake_node_ = new node();
  root_->right_ = fake_node_;
  fake_node_->top_ = root_;
}

template <typename T>
set<T>::set(std::initializer_list<value_type> const& items) : set() {
  for (auto ptr = items.begin(); ptr != items.end(); ++ptr) {
    insert(*ptr);
  }
}

template <typename T>
set<T>::set(const set& other) : set() {
  if (other.size_ > 0) {
    RecursiveCopyWholeSet(other.root_, other);
    size_ = other.size_;
  }
}

template <typename T>
set<T>::set(set&& other) : set() {
  CopySwapWithStd(*this, other);
  other.size_ = 0;
}

template <typename T>
set<T>::~set() {
  clear();
  delete fake_node_;
  delete root_;
}

template <typename T>
set<T>& set<T>::operator=(const set& other) {
  if (this != &other) {
    set<value_type> temp(other);
    CopySwapWithStd(*this, temp);
  }
  return *this;
}

template <typename T>
set<T>& set<T>::operator=(set&& other) {
  if (this != &other) {
    set<value_type> temp(std::move(other));
    CopySwapWithStd(*this, temp);
  }
  return *this;
}

template <typename T>
typename set<T>::iterator set<T>::begin() {
  return empty() ? end() : iterator(root_->FarLeft());
}

template <typename T>
typename set<T>::const_iterator set<T>::begin() const {
  return empty() ? end() : iterator(root_->FarLeft());
}

template <typename T>
typename set<T>::iterator set<T>::end() {
  return iterator(root_->FarRight());
}

template <typename T>
typename set<T>::const_iterator set<T>::end() const {
  return iterator(root_->FarRight());
}

template <typename T>
bool set<T>::empty() const {
  return size_ == 0;
}

template <typename T>
typename set<T>::size_type set<T>::size() const {
  return size_;
}

template <typename T>
typename set<T>::size_type set<T>::max_size() const {
  return SIZE_MAX / sizeof(value_type) / 20;
}

template <typename T>
void set<T>::clear() {
  DeleteNodes(root_);
  root_->left_ = nullptr;
  root_->right_ = fake_node_;
  fake_node_->top_ = root_;
  size_ = 0;
  fake_node_->value_ = size_;
}

template <typename T>
std::pair<typename set<T>::iterator, bool> set<T>::insert(
    const value_type& value) {
  pointer_to_node temp = new node(value);
  iterator result;
  bool code = true;
  if (empty()) {
    root_->value_ = value;
    ++size_;
    fake_node_->value_ = size_;
    result.ptr_ = root_;
    delete temp;
  } else if (HelperForInsert(temp)) {
    ++size_;
    fake_node_->value_ = size_;
    result.ptr_ = temp;
  } else {
    result.ptr_ = find(value).ptr_;
    code = false;
  }
  return std::pair<iterator, bool>(result, code);
}

template <typename T>
void set<T>::erase(iterator pos) {
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
void set<T>::swap(set& other) {
  CopySwapWithStd(*this, other);
}

template <typename T>
void set<T>::merge(set& other) {
  for (auto i = other.root_->FarLeft(); i != other.root_->FarRight();) {
    pointer_to_node to_merge = i;
    if (!contains(to_merge->value_)) {
      i = i->NextNode();
      EraseLogicForMerge(other, to_merge);
      InsertForMerge(to_merge);
      ++size_;
      fake_node_->value_ = size_;
    } else {
      i = i->NextNode();
    }
  }
}

template <typename T>
typename set<T>::iterator set<T>::find(const value_type& key) {
  iterator result(RecursiveFind(key, root_));
  return result;
}

template <typename T>
typename set<T>::const_iterator set<T>::find(const value_type& key) const {
  const_iterator result(RecursiveFind(key, root_));
  return result;
}

template <typename T>
bool set<T>::contains(const value_type& key) const {
  bool result = false;
  if (RecursiveFind(key, root_) != end().ptr_) {
    result = true;
  }
  return result;
}

template <typename T>
template <typename... Args>
vector<std::pair<typename set<T>::iterator, bool>> set<T>::emplace(
    Args&&... args) {
  vector<std::pair<iterator, bool>> result = {(insert(args))...};
  return result;
}

template <typename T>
void set<T>::DeleteNodes(pointer_to_node node) {
  if (node) {
    DeleteNodes(node->left_);
    DeleteNodes(node->right_);
    if (node != root_ && node != fake_node_) {
      delete node;
    }
  }
}

template <typename T>
bool set<T>::HelperForInsert(pointer_to_node node) {
  bool code = true;
  WhileLoopForInsert(node, code);
  return code;
}

template <typename T>
typename set<T>::pointer_to_node set<T>::RecursiveFind(
    const value_type& value, pointer_to_node node) const {
  if (node == fake_node_ || size_ == 0 || !node) return end().ptr_;
  if (value == node->value_) {
    return node;
  } else {
    return (value < node->value_) ? RecursiveFind(value, node->left_)
                                  : RecursiveFind(value, node->right_);
  }
}

template <typename T>
void set<T>::InsertForMerge(pointer_to_node node) {
  if (empty()) {
    delete root_;
    root_ = node;
    root_->right_ = fake_node_;
    fake_node_->top_ = root_;
  } else {
    bool flag;
    node->CleanNodePointers();
    WhileLoopForInsert(node, flag);
  }
}

template <typename T>
void set<T>::EraseLeafNode(pointer_to_node node_to_erase) {
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
void set<T>::EraseNodeOneChildren(pointer_to_node node) {
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
void set<T>::EraseNodeTwoChildren(pointer_to_node node) {
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
void set<T>::WhileLoopForInsert(pointer_to_node node, bool& code) {
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
      code = false;
      delete node;
      break;
    }
  }
}

template <typename T>
void set<T>::EraseLogicForMerge(set& other, pointer_to_node node) {
  pointer_to_node current = node;
  if (!current->left_ &&
      (!current->right_ || current->right_ == other.fake_node_)) {
    EraseLogicForLeafNode(other, current);
  } else if ((current->left_ && !current->right_) ||
             (!current->left_ && current->right_)) {
    EraseLogicForOneChildrenNode(other, current);
  } else if (current->left_ && current->right_) {
    EraseLogicForTwoChildrenNode(other, current);
  }
  --other.size_;
  other.fake_node_->value_ = other.size_;
}

template <typename T>
void set<T>::EraseLogicForLeafNode(set& other, pointer_to_node node_to_erase) {
  if (node_to_erase == other.root_ &&
      node_to_erase->right_ == other.fake_node_) {
    other.root_ = new node();
    other.root_->right_ = other.fake_node_;
    other.fake_node_->top_ = other.root_;
    return;
  }
  if (node_to_erase->top_->left_ == node_to_erase) {
    node_to_erase->top_->left_ = nullptr;
  } else {
    if (node_to_erase->right_ == other.fake_node_) {
      node_to_erase->top_->right_ = other.fake_node_;
    } else {
      node_to_erase->top_->right_ = nullptr;
    }
  }
}

template <typename T>
void set<T>::EraseLogicForOneChildrenNode(set& other, pointer_to_node node) {
  pointer_to_node child = (node->left_) ? node->left_ : node->right_;
  if (node != other.root_) {
    if (node == node->top_->left_) {
      node->top_->left_ = child;
      child->top_ = node->top_;
    } else {
      node->top_->right_ = child;
      child->top_ = node->top_;
    }
  } else {
    other.root_ = child;
    other.root_->top_ = nullptr;
  }
}

template <typename T>
void set<T>::EraseLogicForTwoChildrenNode(set& other,
                                          pointer_to_node node_to_erase) {
  pointer_to_node replace = new node();
  if (node_to_erase->top_) {
    if (node_to_erase->top_->left_ == node_to_erase) {
      node_to_erase->top_->left_ = replace;
    } else {
      node_to_erase->top_->right_ = replace;
    }
  } else {
    other.root_ = replace;
  }
  if (node_to_erase->left_) node_to_erase->left_->top_ = replace;
  if (node_to_erase->right_) node_to_erase->right_->top_ = replace;
  *replace = *node_to_erase;
  pointer_to_node prev = replace->PreviousNode();
  pointer_to_node& parent_pointer =
      (prev == prev->top_->left_) ? prev->top_->left_ : prev->top_->right_;
  if (prev->left_) {
    prev->left_->top_ = prev->top_;
    parent_pointer = prev->left_;
  } else {
    parent_pointer = nullptr;
  }
  replace->value_ = prev->value_;
  delete prev;
}

template <typename T>
void set<T>::RecursiveCopyWholeSet(pointer_to_node node, const set& other) {
  if (empty()) insert(node->value_);
  if (node->left_) insert(node->left_->value_);
  if (node->right_ && node->right_ != other.fake_node_)
    insert(node->right_->value_);
  if (node->left_) RecursiveCopyWholeSet(node->left_, other);
  if (node->right_ && node->right_ != other.fake_node_)
    RecursiveCopyWholeSet(node->right_, other);
}

template <typename T>
void set<T>::CopySwapWithStd(set& one, set& two) noexcept {
  std::swap(one.root_, two.root_);
  std::swap(one.fake_node_, two.fake_node_);
  std::swap(one.size_, two.size_);
}

}  // namespace s21

#endif  // SRC_S21_SET_H_