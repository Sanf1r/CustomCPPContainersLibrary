#ifndef SRC_S21_QUEUE_H_
#define SRC_S21_QUEUE_H_

namespace s21 {
template <typename T>
class queue {
 public:
  // Member type definitions
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  queue();
  queue(std::initializer_list<T> const& items);
  queue(const queue& q);
  queue(queue&& q);
  ~queue();

  queue& operator=(queue&& q);
  queue& operator=(const queue& q);

  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;

  bool empty() const;
  size_type size() const;

  void push(const_reference value);
  void pop();
  void swap(queue& other);

  template <typename... Args>
  void emplace_back(Args&&... args);

 private:
  // Node definition for the doubly linked list
  struct Node {
    value_type data_;
    Node* next_;
    Node* prev_;
    Node(const_reference value, Node* next = nullptr, Node* prev = nullptr)
        : data_(value), next_(next), prev_(prev) {}
  };

  Node* head_;
  Node* tail_;
  size_type size_;
};

// Constructors and destructor
template <typename T>
queue<T>::queue() : head_(nullptr), tail_(nullptr), size_(0) {}

template <typename T>
queue<T>::queue(std::initializer_list<T> const& items)
    : head_(nullptr), tail_(nullptr), size_(0) {
  for (auto const& item : items) {
    push(item);
  }
}

template <typename T>
queue<T>::queue(const queue& q) : head_(nullptr), tail_(nullptr), size_(0) {
  Node* current = q.head_;
  while (current != nullptr) {
    push(current->data_);
    current = current->next_;
  }
}

template <typename T>
queue<T>::queue(queue&& q) : head_(q.head_), tail_(q.tail_), size_(q.size_) {
  q.head_ = nullptr;
  q.tail_ = nullptr;
  q.size_ = 0;
}

template <typename T>
queue<T>::~queue() {
  while (!empty()) {
    pop();
  }
}

// Assignment operator
template <typename T>
queue<T>& queue<T>::operator=(queue&& q) {
  if (this != &q) {
    queue tmp(std::move(q));
    swap(tmp);
  }
  return *this;
}

template <typename T>
queue<T>& queue<T>::operator=(const queue& q) {
  if (this != &q) {
    queue tmp(q);
    swap(tmp);
  }
  return *this;
}

template <typename T>
typename queue<T>::reference queue<T>::front() {
  if (empty()) {
    throw std::out_of_range("queue is empty");
  }
  return head_->data_;
}

// Element access
template <typename T>
typename queue<T>::const_reference queue<T>::front() const {
  if (empty()) {
    throw std::out_of_range("queue is empty");
  }
  return head_->data_;
}

template <typename T>
typename queue<T>::reference queue<T>::back() {
  if (empty()) {
    throw std::out_of_range("queue is empty");
  }
  return tail_->data_;
}

template <typename T>
typename queue<T>::const_reference queue<T>::back() const {
  if (empty()) {
    throw std::out_of_range("queue is empty");
  }
  return tail_->data_;
}

// Capacity
template <typename T>
bool queue<T>::empty() const {
  return size_ == 0;
}

template <typename T>
typename queue<T>::size_type queue<T>::size() const {
  return size_;
}

// Modifiers
template <typename T>
void queue<T>::push(const_reference value) {
  Node* new_node = new Node(value, nullptr, tail_);
  if (tail_ != nullptr) {
    tail_->next_ = new_node;
  }
  tail_ = new_node;
  if (head_ == nullptr) {
    head_ = new_node;
  }
  ++size_;
}

template <typename T>
void queue<T>::pop() {
  if (empty()) {
    throw std::out_of_range("queue is empty");
  }
  Node* old_head_ = head_;
  head_ = old_head_->next_;
  if (head_ != nullptr) {
    head_->prev_ = nullptr;
  } else {
    tail_ = nullptr;
  }
  delete old_head_;
  --size_;
}

template <typename T>
void queue<T>::swap(queue& other) {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

template <typename T>
template <typename... Args>
void queue<T>::emplace_back(Args&&... args) {
  for (auto value : {std::forward<Args>(args)...}) {
    push(value);
  }
}

}  // namespace s21

#endif  // SRC_S21_QUEUE_H_