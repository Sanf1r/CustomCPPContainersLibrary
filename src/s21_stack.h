#ifndef SRC_S21_STACK_H_
#define SRC_S21_STACK_H_

namespace s21 {
template <typename T>
class stack {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  stack();
  stack(std::initializer_list<value_type> const& items);
  stack(const stack& s);
  stack(stack&& s);
  ~stack();

  stack& operator=(stack&& s);
  stack& operator=(const stack& s);

  reference top();
  const_reference top() const;

  void push(const_reference value);
  void pop();
  void swap(stack& other);

  size_type size() const;
  bool empty() const;

  template <typename... Args>
  void emplace_front(Args&&... args);

 private:
  struct Node {
    value_type data_;
    Node* next_;
    Node(const T& value) : data_(value), next_(nullptr) {}
  };
  Node* top_node_;
  size_t size_;
};

template <typename T>
stack<T>::stack() : top_node_(nullptr), size_(0) {}

template <typename T>
stack<T>::stack(std::initializer_list<value_type> const& items)
    : top_node_(nullptr), size_(0) {
  for (const auto& item : items) {
    push(item);
  }
}

template <typename T>
stack<T>::stack(const stack& s) : top_node_(nullptr), size_(0) {
  if (!s.empty()) {
    Node* target_node = new Node(s.top());
    top_node_ = target_node;
    Node* source_node = s.top_node_->next_;
    while (source_node != nullptr) {
      target_node->next_ = new Node(source_node->data_);
      target_node = target_node->next_;
      source_node = source_node->next_;
    }
    size_ = s.size_;
  }
}

template <typename T>
stack<T>::stack(stack&& s) : top_node_(s.top_node_), size_(s.size_) {
  s.top_node_ = nullptr;
  s.size_ = 0;
}

template <typename T>
stack<T>::~stack() {
  while (!empty()) {
    pop();
  }
}

template <typename T>
stack<T>& stack<T>::operator=(stack<T>&& s) {
  if (this != &s) {
    stack tmp(std::move(s));
    swap(tmp);
  }
  return *this;
}

template <typename T>
stack<T>& stack<T>::operator=(const stack<T>& s) {
  if (this != &s) {
    stack tmp(s);
    swap(tmp);
  }
  return *this;
}

template <typename T>
typename stack<T>::reference stack<T>::top() {
  if (empty()) throw std::out_of_range("Stack is empty");
  return top_node_->data_;
}

template <typename T>
typename stack<T>::const_reference stack<T>::top() const {
  if (empty()) throw std::out_of_range("Stack is empty");
  return top_node_->data_;
}

template <typename T>
bool stack<T>::empty() const {
  return top_node_ == nullptr;
}

template <typename T>
typename stack<T>::size_type stack<T>::size() const {
  return size_;
}

template <typename T>
void stack<T>::push(const_reference value) {
  Node* new_node = new Node(value);
  new_node->next_ = top_node_;
  top_node_ = new_node;
  size_++;
}
template <typename T>
void stack<T>::pop() {
  if (empty()) {
    throw std::out_of_range("stack is empty");
  }
  Node* old_top_node_ = top_node_;
  top_node_ = top_node_->next_;
  delete old_top_node_;
  size_--;
}

template <typename T>
void stack<T>::swap(stack& other) {
  std::swap(top_node_, other.top_node_);
  std::swap(size_, other.size_);
}

template <typename T>
template <typename... Args>
void stack<T>::emplace_front(Args&&... args) {
  Node* new_node = new Node(std::forward<Args>(args)...);
  new_node->next_ = top_node_;
  this->top_node_ = new_node;
  this->size_++;
}

}  // namespace s21

#endif  // SRC_S21_STACK_H_