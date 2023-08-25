#ifndef SRC_S21_LIST_H_
#define SRC_S21_LIST_H_

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <stdexcept>

namespace s21 {

template <typename T>
class List {
  struct Node;

 public:
  // Forward declare iterator classes
  class ListIterator;
  class ListConstIterator;
  friend class ListIterator;
  friend class ListConstIterator;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  // Constructors and destructor
  List();
  List(const List &other);
  List(List &&other);
  List(std::initializer_list<value_type> const &items);
  List(size_type n);
  ~List();
  List<T> &operator=(const List &other);
  List<T> &operator=(List &&other) noexcept;

  // Public accessors
  const_reference front() const;
  const_reference back() const;
  reference back();
  reference front();

  // Iterator classes
  class ListIterator {
   public:
    friend class List;
    ListIterator(typename List<T>::Node *node);
    reference operator*() const;
    T *operator->() const;
    iterator &operator++();
    iterator operator++(int);
    iterator &operator--();
    iterator operator--(int);
    bool operator==(const iterator &other) const;
    bool operator!=(const iterator &other) const;

   private:
    typename List<T>::Node *node;
  };

  class ListConstIterator {
   public:
    friend class List;
    ListConstIterator(const typename List<T>::Node *node);
    ListConstIterator(const ListIterator &other) : node(other.node) {}
    const_reference operator*() const;
    const T *operator->() const;
    const_iterator &operator++();
    const_iterator operator++(int);
    const_iterator &operator--();
    const_iterator operator--(int);
    bool operator==(const const_iterator &other) const;
    bool operator!=(const const_iterator &other) const;

   private:
    const typename List<T>::Node *node;
  };

  // Iterator functions
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  // Modifiers
  void push_front(const_reference value);
  void push_back(const_reference value);
  void pop_front();
  void pop_back();
  void swap(List &other);
  void merge(List &other);
  void splice(const_iterator pos, List &other);
  void reverse();
  void unique();
  void sort();
  iterator insert(iterator pos, const_reference value);
  iterator erase(iterator pos);
  void clear();
  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args);
  template <typename... Args>
  void emplace_back(Args &&...args);
  template <typename... Args>
  void emplace_front(Args &&...args);

  // Capacity
  size_type size() const;
  size_type max_size() const;
  bool empty() const noexcept;

 private:
  struct Node {
    value_type data;
    Node *prev;
    Node *next;
    Node(const T &value) : data(value), prev(nullptr), next(nullptr) {}
  };

  Node *sentinel;
  size_type size_ = 0;
};

// Implementation

template <typename T>
List<T>::List() : sentinel(new Node(T())) {
  sentinel->next = sentinel;
  sentinel->prev = sentinel;
}

template <typename T>
List<T>::List(const List &other) : List() {
  for (Node *curr = other.sentinel->next; curr != other.sentinel;
       curr = curr->next) {
    push_back(curr->data);
  }
}

template <typename T>
List<T>::List(size_type n) : List() {
  for (size_type i = 0; i < n; ++i) {
    push_back(value_type());
  }
}

template <typename T>
List<T>::List(List &&other) : sentinel(other.sentinel), size_(other.size_) {
  other.sentinel = nullptr;
  other.size_ = 0;
}

template <typename T>
List<T>::List(std::initializer_list<value_type> const &items) : List() {
  for (const auto &item : items) {
    push_back(item);
  }
}

template <typename T>
List<T>::~List() {
  clear();
  delete sentinel;
}

template <typename T>
List<T> &List<T>::operator=(const List &other) {
  if (this != &other) {
    clear();
    for (Node *curr = other.sentinel->next; curr != other.sentinel;
         curr = curr->next) {
      push_back(curr->data);
    }
  }
  return *this;
}

template <typename T>
List<T> &List<T>::operator=(List<T> &&other) noexcept {
  if (this != &other) {
    clear();
    delete sentinel;
    sentinel = other.sentinel;
    size_ = other.size_;

    other.sentinel = nullptr;
    other.size_ = 0;
  }

  return *this;
}

template <typename T>
typename List<T>::const_reference List<T>::front() const {
  if (empty()) {
    throw std::out_of_range("List is empty.");
  }
  return sentinel->next->data;
}

template <typename T>
typename List<T>::const_reference List<T>::back() const {
  if (empty()) {
    throw std::out_of_range("List is empty.");
  }
  return sentinel->prev->data;
}

template <typename T>
typename List<T>::reference List<T>::front() {
  if (empty()) {
    throw std::out_of_range("List is empty.");
  }
  return sentinel->next->data;
}

template <typename T>
typename List<T>::reference List<T>::back() {
  if (empty()) {
    throw std::out_of_range("List is empty.");
  }
  return sentinel->prev->data;
}

// ListIterator implementation

template <typename T>
List<T>::ListIterator::ListIterator(typename List<T>::Node *node)
    : node(node) {}

template <typename T>
T &List<T>::ListIterator::operator*() const {
  return node->data;
}

template <typename T>
T *List<T>::ListIterator::operator->() const {
  return &node->data;
}

template <typename T>
typename List<T>::iterator &List<T>::ListIterator::operator++() {
  node = node->next;
  return *this;
}

template <typename T>
typename List<T>::iterator List<T>::ListIterator::operator++(int) {
  iterator old(*this);
  node = node->next;
  return old;
}

template <typename T>
typename List<T>::iterator &List<T>::ListIterator::operator--() {
  node = node->prev;
  return *this;
}

template <typename T>
typename List<T>::iterator List<T>::ListIterator::operator--(int) {
  iterator old(*this);
  node = node->prev;
  return old;
}

template <typename T>
bool List<T>::ListIterator::operator==(const iterator &other) const {
  return node == other.node;
}

template <typename T>
bool List<T>::ListIterator::operator!=(const iterator &other) const {
  return node != other.node;
}

// ListConstIterator implementation
template <typename T>
List<T>::ListConstIterator::ListConstIterator(
    const typename List<T>::Node *node)
    : node(node) {}

template <typename T>
const T &List<T>::ListConstIterator::operator*() const {
  return node->data;
}

template <typename T>
const T *List<T>::ListConstIterator::operator->() const {
  return &node->data;
}

template <typename T>
typename List<T>::const_iterator &List<T>::ListConstIterator::operator++() {
  node = node->next;
  return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::ListConstIterator::operator++(int) {
  const_iterator old(*this);
  node = node->next;
  return old;
}

template <typename T>
typename List<T>::const_iterator &List<T>::ListConstIterator::operator--() {
  node = node->prev;
  return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::ListConstIterator::operator--(int) {
  const_iterator old(*this);
  node = node->prev;
  return old;
}

template <typename T>
bool List<T>::ListConstIterator::operator==(const const_iterator &other) const {
  return node == other.node;
}

template <typename T>
bool List<T>::ListConstIterator::operator!=(const const_iterator &other) const {
  return node != other.node;
}

// Iterator functions
template <typename T>
typename List<T>::iterator List<T>::begin() {
  return iterator(sentinel->next);
}

template <typename T>
typename List<T>::iterator List<T>::end() {
  return iterator(sentinel);
}

template <typename T>
typename List<T>::const_iterator List<T>::begin() const {
  return const_iterator(sentinel->next);
}

template <typename T>
typename List<T>::const_iterator List<T>::end() const {
  return const_iterator(sentinel);
}

template <typename T>
typename List<T>::const_iterator List<T>::cbegin() const noexcept {
  return const_iterator(begin());
}

template <typename T>
typename List<T>::const_iterator List<T>::cend() const noexcept {
  return const_iterator(end());
}

// Modifiers
template <typename T>
void List<T>::push_front(const_reference value) {
  Node *newNode = new Node(value);
  newNode->next = sentinel->next;
  newNode->prev = sentinel;
  sentinel->next->prev = newNode;
  sentinel->next = newNode;
  ++size_;
}

template <typename T>
void List<T>::push_back(const_reference value) {
  Node *newNode = new Node(value);
  newNode->prev = sentinel->prev;
  newNode->next = sentinel;
  sentinel->prev->next = newNode;
  sentinel->prev = newNode;
  ++size_;
}

template <typename T>
void List<T>::pop_front() {
  if (empty()) {
    throw std::out_of_range("List is empty.");
  }
  Node *temp = sentinel->next;
  sentinel->next = temp->next;
  temp->next->prev = sentinel;
  delete temp;
  --size_;
}

template <typename T>
void List<T>::pop_back() {
  if (empty()) {
    throw std::out_of_range("List is empty.");
  }
  Node *temp = sentinel->prev;
  sentinel->prev = temp->prev;
  temp->prev->next = sentinel;
  delete temp;
  --size_;
}

// swap(), merge(), splice(), reverse(), unique() and sort() methods
template <typename T>
void List<T>::swap(List<T> &other) {
  std::swap(sentinel, other.sentinel);
  std::swap(size_, other.size_);
}

template <typename T>
void List<T>::merge(List<T> &other) {
  if (this == &other) return;
  iterator it1 = begin();
  iterator it2 = other.begin();
  if (empty()) {
    *this = std::move(other);
    return;
  } else if (other.empty()) {
    return;
  }
  while (it1 != end() && it2 != other.end()) {
    if (*it1 < *it2) {
      ++it1;
    } else {
      value_type value = *it2;
      iterator toErase = it2;
      ++it2;
      other.erase(toErase);
      insert(it1, value);
    }
  }
  splice(end(), other);
  other.size_ = 0;
}

template <typename T>
void List<T>::splice(const_iterator pos, List<T> &other) {
  if (other.empty()) return;

  Node *non_const_pos = const_cast<Node *>(pos.node);
  Node *before = non_const_pos->prev;
  Node *first = other.sentinel->next;
  Node *last = other.sentinel->prev;

  before->next = first;
  first->prev = before;

  non_const_pos->prev = last;
  last->next = non_const_pos;

  size_ += other.size_;
  other.size_ = 0;

  other.sentinel->next = other.sentinel;
  other.sentinel->prev = other.sentinel;
}

// reverse()
template <typename T>
void List<T>::reverse() {
  if (empty()) return;

  Node *current = sentinel;

  do {
    std::swap(current->next, current->prev);
    current = current->prev;
  } while (current != sentinel);
}

// unique()
template <typename T>
void List<T>::unique() {
  if (empty()) return;

  iterator it = begin();
  iterator next_it = it;
  ++next_it;

  while (next_it != end()) {
    if (*it == *next_it) {
      next_it = erase(next_it);
    } else {
      ++it;
      ++next_it;
    }
  }
}

// sort()
template <typename T>
void List<T>::sort() {
  if (size() < 2) return;

  List<T> left;
  List<T> right;
  size_type middle = size() / 2;
  auto it = begin();

  // Split the list into two parts
  for (size_type i = 0; i < middle; ++i) {
    left.push_back(*it);
    ++it;
  }
  for (; it != end(); ++it) {
    right.push_back(*it);
  }

  // Recursively sort the two parts
  left.sort();
  right.sort();

  // Merge the two sorted parts
  clear();
  auto left_it = left.begin();
  auto right_it = right.begin();

  while (left_it != left.end() && right_it != right.end()) {
    if (*left_it <= *right_it) {
      push_back(*left_it);
      ++left_it;
    } else {
      push_back(*right_it);
      ++right_it;
    }
  }

  while (left_it != left.end()) {
    push_back(*left_it);
    ++left_it;
  }

  while (right_it != right.end()) {
    push_back(*right_it);
    ++right_it;
  }
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator pos,
                                           const_reference value) {
  Node *newNode = new Node(value);
  Node *posNode = pos.node;  // node
  newNode->prev = posNode->prev;
  newNode->next = posNode;
  posNode->prev->next = newNode;
  posNode->prev = newNode;
  ++size_;
  return iterator(newNode);
}

template <typename T>
typename List<T>::iterator List<T>::erase(iterator pos) {
  if (pos == end()) {
    throw std::out_of_range("Cannot erase past the end.");
  }
  Node *toRemove = pos.node;  // node
  toRemove->prev->next = toRemove->next;
  toRemove->next->prev = toRemove->prev;
  iterator next(toRemove->next);
  delete toRemove;
  --size_;
  return next;
}

template <typename T>
void List<T>::clear() {
  while (!empty()) {
    pop_front();
  }
}

// Capacity
template <typename T>
typename List<T>::size_type List<T>::size() const {
  return size_;
}

template <typename T>
typename List<T>::size_type List<T>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(Node) / 2;
}

template <typename T>
bool List<T>::empty() const noexcept {
  return size_ == 0;
}

template <typename T>
template <typename... Args>
typename List<T>::iterator List<T>::emplace(const_iterator pos,
                                            Args &&...args) {
  iterator result(const_cast<Node *>(pos.node));
  for (auto value : {std::forward<Args>(args)...}) {
    result = insert(result, value);
    ++result;
  }
  return --result;
}

template <typename T>
template <typename... Args>
void List<T>::emplace_back(Args &&...args) {
  for (auto value : {std::forward<Args>(args)...}) {
    push_back(value);
  }
}

template <typename T>
template <typename... Args>
void List<T>::emplace_front(Args &&...args) {
  for (auto value : {std::forward<Args>(args)...}) {
    push_front(value);
  }
}

}  // namespace s21

#endif  // SRC_S21_LIST_H_
