#ifndef SRC_S21_MAP_H_
#define SRC_S21_MAP_H_

#include "s21_vector.h"

namespace s21 {
template <typename Key, typename T>
class Map {
  class BinaryTreeNode;

 public:
  // Map Member Type
  class TreeIterator;
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = TreeIterator;
  using const_iterator = TreeIterator;
  using node = BinaryTreeNode;
  using size_type = size_t;
  using pointer_to_node = BinaryTreeNode *;

  // Public class TreeIterator
  class TreeIterator {
    friend class Map;

   public:
    using value_type = std::pair<Key, T>;
    using pointer_to_node = BinaryTreeNode *;
    using const_reference = const value_type &;

   public:
    TreeIterator();
    explicit TreeIterator(pointer_to_node ptr);
    TreeIterator &operator++();
    TreeIterator operator++(int);
    TreeIterator &operator--();
    TreeIterator operator--(int);
    const_reference operator*() const;
    bool operator==(const TreeIterator &other);
    bool operator!=(const TreeIterator &other);

   private:
    pointer_to_node ptr_;
  };
  // Map Member func
  Map();
  Map(std::initializer_list<value_type> const &items);
  Map(const Map &m);
  Map(Map &&m);
  ~Map();
  Map &operator=(const Map &m);
  Map &operator=(Map &&m);

  // Map Element access
  // Access specified element with bounds checkin
  T &operator[](const Key &key);
  // Access or insert specified element
  T &at(const Key &key);
  const T &at(const Key &key) const;

  // Map Iteraitors
  // Returns an iterator to the beginning
  iterator begin();
  const_iterator begin() const;
  // Returns an iterator to the end
  iterator end();
  const_iterator end() const;

  // Map Capacity
  // Checks whether the container is empty
  bool empty() const;
  // Returns the number of elements
  size_type size() const;
  // Returns the maximum possible number of elements
  size_type max_size() const;

  // Map Modifiers
  // Clears the contents
  void clear();
  // Inserts node and returns iterator to where the element is in the container
  // and bool denoting whether the insertion took place
  std::pair<iterator, bool> insert(const Key &key, const T &obj);
  // Inserts value by key and returns iterator to where the element is in the
  // container and bool denoting whether the insertion took place
  std::pair<iterator, bool> insert(const value_type &value);
  // Inserts an element or assigns to the current element if the key already
  // exists
  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj);
  // Erases element at pos
  void erase(iterator pos);
  // Swaps the contents
  void swap(Map &other);
  // Splices nodes from another container
  void merge(Map &other);

  // Map Lookup
  // Checks if there is an element with key equivalent to key in the container
  bool contains(const Key &key) const;

  // Map Emplace
  // emplace() inserts new elements into the container
  template <typename... Args>
  vector<std::pair<iterator, bool>> emplace(Args &&...args);

 private:
  pointer_to_node root_;
  pointer_to_node fake_node_;
  size_type size_ = 0;

  // Private Node class
  class BinaryTreeNode {
   public:
    using value_type = std::pair<Key, T>;
    using pointer_to_node = BinaryTreeNode *;

   public:
    BinaryTreeNode();
    BinaryTreeNode(value_type data, pointer_to_node top = nullptr,
                   pointer_to_node left = nullptr,
                   pointer_to_node right = nullptr);
    BinaryTreeNode(const BinaryTreeNode &other);
    BinaryTreeNode(BinaryTreeNode &&other);
    ~BinaryTreeNode();
    BinaryTreeNode &operator=(const BinaryTreeNode &other);
    BinaryTreeNode &operator=(BinaryTreeNode &&other);
    pointer_to_node NextNode();
    pointer_to_node PreviousNode();
    pointer_to_node FarLeft();
    pointer_to_node FarRight();
    pointer_to_node FarTop();
    void CleanNodePointers();

    value_type values_;
    pointer_to_node top_;
    pointer_to_node left_;
    pointer_to_node right_;
  };

  // Map Helper Methods
  void DeleteNodes(pointer_to_node node);
  bool HelperForInsert(pointer_to_node node);
  pointer_to_node RecursiveFind(const Key &key, pointer_to_node node) const;
  void InsertForMerge(pointer_to_node node);
  void erase_helper(pointer_to_node node);
  void erase_helper_2(pointer_to_node node);
  void erase_helper_3(pointer_to_node node);
  void EraseLeafNode(pointer_to_node node_to_erase);
  void EraseNodeOneChildren(pointer_to_node node);
  void EraseNodeTwoChildren(pointer_to_node node);
  void while_for_insert(pointer_to_node node, bool &code);
  void EraseLogicForMerge(Map &other, pointer_to_node node);
  void EraseLogicForLeafNode(Map &other, pointer_to_node node_to_erase);
  void EraseLogicForOneChildrenNode(Map &other, pointer_to_node node);
  void EraseLogicForTwoChildrenNode(Map &other, pointer_to_node node_to_erase);
  void RecursiveCopyWholeSet(pointer_to_node node, const Map &other);
  void CopySwap(Map &one, Map &two) noexcept;
  std::pair<iterator, bool> InsertResult(std::pair<Key, T> val);
};

// TreeIterator class implementation
template <typename Key, typename T>
Map<Key, T>::TreeIterator::TreeIterator() : ptr_(nullptr) {}

template <typename Key, typename T>
Map<Key, T>::TreeIterator::TreeIterator(pointer_to_node ptr) : ptr_(ptr) {}

template <typename Key, typename T>
typename Map<Key, T>::TreeIterator &Map<Key, T>::TreeIterator::operator++() {
  if (ptr_ == ptr_->FarTop()->FarRight()) {
    --(*this);
  } else {
    ptr_ = ptr_->NextNode();
  }
  return *this;
}

template <typename Key, typename T>
typename Map<Key, T>::TreeIterator Map<Key, T>::TreeIterator::operator++(int) {
  TreeIterator temp = *this;
  ++(*this);
  return temp;
}

template <typename Key, typename T>
typename Map<Key, T>::TreeIterator &Map<Key, T>::TreeIterator::operator--() {
  if (ptr_ == ptr_->FarTop()->FarLeft()) {
    ptr_ = ptr_->FarTop()->FarRight();
  } else {
    ptr_ = ptr_->PreviousNode();
  }
  return *this;
}

template <typename Key, typename T>
typename Map<Key, T>::TreeIterator::TreeIterator
Map<Key, T>::TreeIterator::operator--(int) {
  TreeIterator temp = *this;
  --(*this);
  return temp;
}

template <typename Key, typename T>
typename Map<Key, T>::TreeIterator::const_reference
Map<Key, T>::TreeIterator::operator*() const {
  return ptr_->values_;
}

template <typename Key, typename T>
bool Map<Key, T>::TreeIterator::operator==(const TreeIterator &other) {
  return ptr_ == other.ptr_;
}

template <typename Key, typename T>
bool Map<Key, T>::TreeIterator::operator!=(const TreeIterator &other) {
  return !(ptr_ == other.ptr_);
}

// BinaryNodeTree class implementation

template <typename Key, typename T>
Map<Key, T>::BinaryTreeNode::BinaryTreeNode()
    : top_(nullptr), left_(nullptr), right_(nullptr) {}

template <typename Key, typename T>
Map<Key, T>::BinaryTreeNode::BinaryTreeNode(value_type data,
                                            pointer_to_node top,
                                            pointer_to_node left,
                                            pointer_to_node right)
    : values_(data), top_(top), left_(left), right_(right) {}

template <typename Key, typename T>
Map<Key, T>::BinaryTreeNode::BinaryTreeNode(const BinaryTreeNode &other) {
  *this = other;
}

template <typename Key, typename T>
Map<Key, T>::BinaryTreeNode::BinaryTreeNode(BinaryTreeNode &&other) = default;

template <typename Key, typename T>
Map<Key, T>::BinaryTreeNode::~BinaryTreeNode() = default;

template <typename Key, typename T>
typename Map<Key, T>::BinaryTreeNode &Map<Key, T>::BinaryTreeNode::operator=(
    const BinaryTreeNode &other) {
  if (this != &other) {
    values_ = other.values_;
    top_ = other.top_;
    left_ = other.left_;
    right_ = other.right_;
  }
  return *this;
}

template <typename Key, typename T>
typename Map<Key, T>::BinaryTreeNode &Map<Key, T>::BinaryTreeNode::operator=(
    BinaryTreeNode &&other) = default;

template <typename Key, typename T>
typename Map<Key, T>::BinaryTreeNode::pointer_to_node
Map<Key, T>::BinaryTreeNode::NextNode() {
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

template <typename Key, typename T>
typename Map<Key, T>::BinaryTreeNode::pointer_to_node
Map<Key, T>::BinaryTreeNode::PreviousNode() {
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

template <typename Key, typename T>
typename Map<Key, T>::BinaryTreeNode::pointer_to_node
Map<Key, T>::BinaryTreeNode::FarLeft() {
  pointer_to_node temp(this);
  while (temp->left_) temp = temp->left_;
  return temp;
}

template <typename Key, typename T>
typename Map<Key, T>::BinaryTreeNode::pointer_to_node
Map<Key, T>::BinaryTreeNode::FarRight() {
  pointer_to_node temp(this);
  while (temp->right_) temp = temp->right_;
  return temp;
}

template <typename Key, typename T>
typename Map<Key, T>::BinaryTreeNode::pointer_to_node
Map<Key, T>::BinaryTreeNode::FarTop() {
  pointer_to_node temp(this);
  while (temp->top_) temp = temp->top_;
  return temp;
}

template <typename Key, typename T>
void Map<Key, T>::BinaryTreeNode::CleanNodePointers() {
  top_ = nullptr;
  left_ = nullptr;
  right_ = nullptr;
}

// Map class implementation

template <typename Key, typename T>
Map<Key, T>::Map() {
  root_ = new node();
  fake_node_ = new node();
  root_->right_ = fake_node_;
  fake_node_->top_ = root_;
}

template <typename Key, typename T>
Map<Key, T>::Map(std::initializer_list<value_type> const &items) : Map() {
  for (auto const &item : items) {
    insert(item);
  }
}

template <typename Key, typename T>
Map<Key, T>::Map(const Map &m) : Map() {
  if (m.size_ > 0) {
    RecursiveCopyWholeSet(m.root_, m);
    size_ = m.size_;
  }
}

template <typename Key, typename T>
Map<Key, T>::Map(Map &&m) : Map() {
  CopySwap(*this, m);
  m.size_ = 0;
}

template <typename Key, typename T>
Map<Key, T>::~Map() {
  clear();
  delete fake_node_;
  delete root_;
}

template <typename Key, typename T>
Map<Key, T> &Map<Key, T>::operator=(Map<Key, T> &&m) {
  if (this != &m) {
    m->root_ = nullptr;
    root_ = m->root_;
    size_ = m->size;
  }
  return *this;
}

template <typename Key, typename T>
typename Map<Key, T>::mapped_type &Map<Key, T>::operator[](const Key &key) {
  node *findNode = RecursiveFind(key, root_);
  if (findNode == fake_node_) {
    insert(key, mapped_type());
    findNode = RecursiveFind(key, root_);
  }

  return findNode->values_.second;
}

template <typename Key, typename T>
typename Map<Key, T>::mapped_type &Map<Key, T>::at(const Key &key) {
  node *findNode = RecursiveFind(key, root_);
  if (findNode == fake_node_) {
    throw std::out_of_range("No such element");
  }
  return findNode->values_.second;
}

template <typename Key, typename T>
const typename Map<Key, T>::mapped_type &Map<Key, T>::at(const Key &key) const {
  node *findNode = RecursiveFind(key, root_);
  if (findNode == fake_node_) {
    throw std::out_of_range("No such element");
  }
  return findNode->values_.second;
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::begin() {
  return empty() ? end() : iterator(root_->FarLeft());
}

template <typename Key, typename T>
typename Map<Key, T>::const_iterator Map<Key, T>::begin() const {
  return empty() ? end() : iterator(root_->FarLeft());
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::end() {
  return iterator(root_->FarRight());
}

template <typename Key, typename T>
typename Map<Key, T>::const_iterator Map<Key, T>::end() const {
  return iterator(root_->FarRight());
}

template <typename Key, typename T>
bool Map<Key, T>::empty() const {
  return size_ == 0;
}

template <typename Key, typename T>
typename Map<Key, T>::size_type Map<Key, T>::size() const {
  return size_;
}

template <typename Key, typename T>
typename Map<Key, T>::size_type Map<Key, T>::max_size() const {
  std::allocator<std::pair<Key, T>> Alloc;
  return Alloc.max_size() / 5;
}

template <typename Key, typename T>
void Map<Key, T>::clear() {
  DeleteNodes(root_);
  root_->left_ = nullptr;
  root_->right_ = fake_node_;
  fake_node_->top_ = root_;
  size_ = 0;
  fake_node_->values_.first = size_;
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert(
    const value_type &value) {
  std::pair<Key, T> val = {value.first, value.second};
  return InsertResult(val);
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert(
    const key_type &key, const mapped_type &obj) {
  std::pair<Key, T> val = {key, obj};
  return InsertResult(val);
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert_or_assign(
    const Key &key, const T &obj) {
  std::pair<Key, T> val = {key, obj};
  bool result = false;
  typename Map<Key, T>::pointer_to_node findNode =
      RecursiveFind(key, Map<Key, T>::root_);
  if (findNode == Map<Key, T>::fake_node_) {
    insert(val);
    result = true;
    typename Map<Key, T>::pointer_to_node resNode =
        RecursiveFind(key, Map<Key, T>::root_);
    return std::make_pair(typename Map<Key, T>::iterator(resNode), result);
  } else {
    findNode->values_.second = val.second;
  }

  return std::make_pair(typename Map<Key, T>::iterator(findNode), result);
}

template <typename Key, typename T>
void Map<Key, T>::erase(iterator pos) {
  pointer_to_node current = pos.ptr_;
  if (current == end().ptr_) {
    throw std::logic_error(
        "The end() iterator cannot be used as a value for pos\n");
  } else if (!current->left_ &&
             (!current->right_ || current->right_ == fake_node_)) {
    erase_helper(current);
  } else if ((current->left_ && !current->right_) ||
             (!current->left_ && current->right_)) {
    erase_helper_2(current);
  } else if (current->left_ && current->right_) {
    erase_helper_3(current);
  }
  --size_;
  fake_node_->values_.first = size_;
}

template <typename Key, typename T>
void Map<Key, T>::merge(Map &other) {
  for (auto i = other.root_->FarLeft(); i != other.root_->FarRight();) {
    pointer_to_node to_merge = i;
    if (!contains(to_merge->values_.first)) {
      i = i->NextNode();
      EraseLogicForMerge(other, to_merge);
      InsertForMerge(to_merge);
      ++size_;
      fake_node_->values_.first = size_;
    } else {
      i = i->NextNode();
    }
  }
}

template <typename Key, typename T>
void Map<Key, T>::swap(Map &other) {
  CopySwap(*this, other);
}

template <typename Key, typename T>
bool Map<Key, T>::contains(const Key &key) const {
  return RecursiveFind(key, root_) == end().ptr_ ? false : true;
}

template <typename Key, typename T>
template <typename... Args>
vector<std::pair<typename Map<Key, T>::iterator, bool>> Map<Key, T>::emplace(
    Args &&...args) {
  vector<std::pair<iterator, bool>> result = {(insert(args))...};
  return result;
}

template <typename Key, typename T>
void Map<Key, T>::DeleteNodes(pointer_to_node node) {
  if (node) {
    DeleteNodes(node->left_);
    DeleteNodes(node->right_);
    if (node != root_ && node != fake_node_) {
      delete node;
    }
  }
}

template <typename Key, typename T>
typename Map<Key, T>::pointer_to_node Map<Key, T>::RecursiveFind(
    const Key &key, pointer_to_node node) const {
  if (node == fake_node_ || size_ == 0 || !node) return end().ptr_;
  if (key == node->values_.first) {
    return node;
  } else {
    return (key < node->values_.first) ? RecursiveFind(key, node->left_)
                                       : RecursiveFind(key, node->right_);
  }
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::InsertResult(
    std::pair<Key, T> val) {
  node *temp = new node(val);
  if (empty()) {
    root_->values_.second = val.second;
    root_->values_.first = val.first;
    ++size_;
    fake_node_->values_.first = size_;
    iterator res(root_);
    delete temp;
    return std::pair<Map<Key, T>::iterator, bool>(res, true);
  } else if (HelperForInsert(temp)) {
    ++size_;
    fake_node_->values_.first = size_;
    iterator res(temp);
    return std::pair<Map<Key, T>::iterator, bool>(res, true);
  }
  return std::make_pair(Map<Key, T>::iterator(RecursiveFind(val.first, root_)),
                        false);
}

template <typename Key, typename T>
bool Map<Key, T>::HelperForInsert(pointer_to_node node) {
  bool code = true;
  while_for_insert(node, code);
  return code;
}

template <typename Key, typename T>
void Map<Key, T>::while_for_insert(pointer_to_node node, bool &code) {
  pointer_to_node Current = root_;
  while (true) {
    if (node->values_.first < Current->values_.first) {
      if (Current->left_ == nullptr) {
        Current->left_ = node;
        node->top_ = Current;
        break;
      } else {
        Current = Current->left_;
      }
    } else if ((node->values_.first > Current->values_.first) &&
               Current != fake_node_) {
      if (Current->right_ == nullptr) {
        Current->right_ = node;
        node->top_ = Current;
        break;
      } else {
        Current = Current->right_;
      }
    } else if (Current == fake_node_) {
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

template <typename Key, typename T>
void Map<Key, T>::erase_helper(pointer_to_node node) {
  if (node == root_ && node->right_ == fake_node_) {
    delete root_;
    root_ = new BinaryTreeNode();
    root_->right_ = fake_node_;
    fake_node_->top_ = root_;
    return;
  }
  if (node->top_->left_ == node) {
    node->top_->left_ = nullptr;
  } else {
    if (node->right_ == fake_node_) {
      node->top_->right_ = fake_node_;
    } else {
      node->top_->right_ = nullptr;
    }
  }
  delete node;
}

template <typename Key, typename T>
void Map<Key, T>::erase_helper_2(pointer_to_node node) {
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

template <typename Key, typename T>
void Map<Key, T>::erase_helper_3(pointer_to_node node) {
  pointer_to_node prev = node->PreviousNode();
  pointer_to_node &parent_pointer =
      (prev == prev->top_->left_) ? prev->top_->left_ : prev->top_->right_;
  if (prev->left_) {
    prev->left_->top_ = prev->top_;
    parent_pointer = prev->left_;
  } else {
    parent_pointer = nullptr;
  }
  node->values_.first = prev->values_.first;
  node->values_.second = prev->values_.second;
  delete prev;
}

template <typename Key, typename T>
void Map<Key, T>::CopySwap(Map &one, Map &two) noexcept {
  using std::swap;
  swap(one.root_, two.root_);
  swap(one.fake_node_, two.fake_node_);
  swap(one.size_, two.size_);
}

template <typename Key, typename T>
void Map<Key, T>::RecursiveCopyWholeSet(pointer_to_node node,
                                        const Map &other) {
  if (empty()) insert(node->values_.first, node->values_.second);
  if (node->left_)
    insert(node->left_->values_.first, node->left_->values_.second);
  if (node->right_ && node->right_ != other.fake_node_)
    insert(node->right_->values_.first, node->right_->values_.second);
  if (node->left_) RecursiveCopyWholeSet(node->left_, other);
  if (node->right_ && node->right_ != other.fake_node_)
    RecursiveCopyWholeSet(node->right_, other);
}

template <typename Key, typename T>
void Map<Key, T>::EraseLogicForMerge(Map &other, pointer_to_node node) {
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
  other.fake_node_->values_.first = other.size_;
}

template <typename Key, typename T>
void Map<Key, T>::EraseLogicForLeafNode(Map &other,
                                        pointer_to_node node_to_erase) {
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

template <typename Key, typename T>
void Map<Key, T>::EraseLogicForOneChildrenNode(Map &other,
                                               pointer_to_node node) {
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

template <typename Key, typename T>
void Map<Key, T>::EraseLogicForTwoChildrenNode(Map &other,
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
  pointer_to_node &parent_pointer =
      (prev == prev->top_->left_) ? prev->top_->left_ : prev->top_->right_;
  if (prev->left_) {
    prev->left_->top_ = prev->top_;
    parent_pointer = prev->left_;
  } else {
    parent_pointer = nullptr;
  }
  replace->values_ = prev->values_;
  delete prev;
}

template <typename Key, typename T>
void Map<Key, T>::InsertForMerge(pointer_to_node node) {
  if (empty()) {
    delete root_;
    root_ = node;
    root_->right_ = fake_node_;
    fake_node_->top_ = root_;
  } else {
    node->CleanNodePointers();
    bool yes = true;
    while_for_insert(node, yes);
  }
}
}  // namespace s21

#endif  // SRC_S21_MAP_H_
