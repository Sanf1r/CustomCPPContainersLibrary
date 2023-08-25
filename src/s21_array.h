#ifndef SRC_S21_ARRAY_H_
#define SRC_S21_ARRAY_H_

namespace s21 {
template <typename T, std::size_t S>
class array {
 public:
  // Public class Iterator
  class Iterator {
   public:
    using pointer = T *;
    using reference = T &;

   public:
    explicit Iterator(pointer ptr);
    Iterator &operator++();
    Iterator operator++(int);
    Iterator &operator--();
    Iterator operator--(int);
    bool operator==(const Iterator &other);
    bool operator!=(const Iterator &other);
    reference operator*();

   private:
    pointer ptr_;
  };

  // Public class ConstIterator
  class ConstIterator {
   public:
    using const_pointer = const T *;
    using const_reference = const T &;

   public:
    explicit ConstIterator(const_pointer ptr);
    ConstIterator &operator++();
    ConstIterator operator++(int);
    ConstIterator &operator--();
    ConstIterator operator--(int);
    const_reference operator*() const;
    bool operator==(const ConstIterator &other);
    bool operator!=(const ConstIterator &other);

   private:
    const_pointer ptr_;
  };

  // Array Member type
  using value_type = T;
  using reference = T &;
  using pointer = T *;
  using const_pointer = const T *;
  using iterator = Iterator;
  using const_iterator = const ConstIterator;
  using const_reference = const T &;
  using size_type = size_t;

  // Array Member functions
  array();
  array(std::initializer_list<value_type> const &items);
  array(const array &other);
  array(array &&other);
  ~array();
  array &operator=(const array &other);
  array &operator=(array &&other) noexcept;

  // Array Element access
  // at() access specified element with bounds checking
  reference at(size_type pos);
  const_reference at(size_type pos) const;
  // operator[] access specified element
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  // front() access the first element
  reference front();
  const_reference front() const;
  // back() access the last element
  reference back();
  const_reference back() const;
  // data() direct access to the underlying array
  pointer data();
  const_pointer data() const;

  // Array Iterators
  // begin() returns an iterator to the beginning
  iterator begin();
  const_iterator begin() const;
  // end() returns an iterator to the end
  iterator end();
  const_iterator end() const;

  // Array Capacity
  // empty() checks whether the container is empty
  bool empty() const;
  // size() returns the number of elements
  constexpr size_type size() const;
  // max_size() returns the maximum possible number of elements
  constexpr size_type max_size() const;

  // Array Modifiers
  // swap() swaps the contents
  void swap(array &other);
  // fill() assigns the given value value to all elements in the container
  void fill(const_reference value);

 private:
  size_type size_ = S;
  value_type arr_[S];

  // Array Helper Methods
  void CopySwapWithStd(array &one, array &two) noexcept;
};

// Template for array with size = 0
template <typename T>
class array<T, 0> {
 public:
  T *begin() const noexcept { return nullptr; }
  T *end() const noexcept { return nullptr; }
  T *data() const noexcept { return nullptr; }
  bool empty() const noexcept { return true; }
  size_t size() const noexcept { return 0; }
  size_t max_size() const noexcept { return 0; }
};

// Iterator class implementation

template <typename T, std::size_t S>
array<T, S>::Iterator::Iterator(pointer ptr) : ptr_(ptr) {}

template <typename T, std::size_t S>
typename array<T, S>::Iterator &array<T, S>::Iterator::operator++() {
  ++ptr_;
  return *this;
}

template <typename T, std::size_t S>
typename array<T, S>::Iterator array<T, S>::Iterator::operator++(int) {
  Iterator temp = *this;
  ++(*this);
  return temp;
}

template <typename T, std::size_t S>
typename array<T, S>::Iterator &array<T, S>::Iterator::operator--() {
  --ptr_;
  return *this;
}

template <typename T, std::size_t S>
typename array<T, S>::Iterator array<T, S>::Iterator::operator--(int) {
  Iterator temp = *this;
  --(*this);
  return temp;
}

template <typename T, std::size_t S>
bool array<T, S>::Iterator::operator==(const Iterator &other) {
  return ptr_ == other.ptr_;
}

template <typename T, std::size_t S>
bool array<T, S>::Iterator::operator!=(const Iterator &other) {
  return !(ptr_ == other.ptr_);
}

template <typename T, std::size_t S>
typename array<T, S>::Iterator::reference array<T, S>::Iterator::operator*() {
  return *(this->ptr_);
}

// ConstIterator class implementation

template <typename T, std::size_t S>
array<T, S>::ConstIterator::ConstIterator(const_pointer ptr) : ptr_(ptr) {}

template <typename T, std::size_t S>
typename array<T, S>::ConstIterator &array<T, S>::ConstIterator::operator++() {
  ++ptr_;
  return *this;
}

template <typename T, std::size_t S>
typename array<T, S>::ConstIterator array<T, S>::ConstIterator::operator++(
    int) {
  ConstIterator temp = *this;
  ++(*this);
  return temp;
}

template <typename T, std::size_t S>
typename array<T, S>::ConstIterator &array<T, S>::ConstIterator::operator--() {
  --ptr_;
  return *this;
}

template <typename T, std::size_t S>
typename array<T, S>::ConstIterator::ConstIterator
array<T, S>::ConstIterator::operator--(int) {
  ConstIterator temp = *this;
  --(*this);
  return temp;
}

template <typename T, std::size_t S>
typename array<T, S>::const_reference array<T, S>::ConstIterator::operator*()
    const {
  return *(this->ptr_);
}

template <typename T, std::size_t S>
bool array<T, S>::ConstIterator::operator==(const ConstIterator &other) {
  return ptr_ == other.ptr_;
}

template <typename T, std::size_t S>
bool array<T, S>::ConstIterator::operator!=(const ConstIterator &other) {
  return !(ptr_ == other.ptr_);
}

// Array class implementation

template <typename T, std::size_t S>
array<T, S>::array() = default;

template <typename T, std::size_t S>
array<T, S>::array(std::initializer_list<value_type> const &items) {
  if (items.size() != size_) throw std::out_of_range("Too many initializers\n");
  auto ptr = items.begin();
  for (size_type i = 0; i < S; ++i) {
    arr_[i] = *ptr;
    ++ptr;
  }
}

template <typename T, std::size_t S>
array<T, S>::array(const array &other) = default;

template <typename T, std::size_t S>
array<T, S>::array(array &&other) = default;

template <typename T, std::size_t S>
array<T, S>::~array() = default;

template <typename T, std::size_t S>
typename array<T, S>::array &array<T, S>::operator=(const array &other) {
  if (this != &other) {
    array temp(other);
    CopySwapWithStd(*this, temp);
  }
  return *this;
}

template <typename T, std::size_t S>
typename array<T, S>::array &array<T, S>::operator=(array &&other) noexcept {
  if (this != &other) {
    array temp(std::move(other));
    CopySwapWithStd(*this, temp);
  }
  return *this;
}

template <typename T, std::size_t S>
typename array<T, S>::reference array<T, S>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("Position is out_of_range\n");
  }
  return arr_[pos];
}

template <typename T, std::size_t S>
typename array<T, S>::const_reference array<T, S>::at(size_type pos) const {
  if (pos >= size_) {
    throw std::out_of_range("Position is out_of_range\n");
  }
  return arr_[pos];
}

template <typename T, std::size_t S>
typename array<T, S>::reference array<T, S>::operator[](size_type pos) {
  return arr_[pos];
}

template <typename T, std::size_t S>
typename array<T, S>::const_reference array<T, S>::operator[](
    size_type pos) const {
  return arr_[pos];
}

template <typename T, std::size_t S>
typename array<T, S>::reference array<T, S>::front() {
  return arr_[0];
}

template <typename T, std::size_t S>
typename array<T, S>::const_reference array<T, S>::front() const {
  return arr_[0];
}

template <typename T, std::size_t S>
typename array<T, S>::reference array<T, S>::back() {
  return arr_[size_ - 1];
}

template <typename T, std::size_t S>
typename array<T, S>::const_reference array<T, S>::back() const {
  return arr_[size_ - 1];
}

template <typename T, std::size_t S>
typename array<T, S>::pointer array<T, S>::data() {
  return arr_;
}

template <typename T, std::size_t S>
typename array<T, S>::const_pointer array<T, S>::data() const {
  return arr_;
}

template <typename T, std::size_t S>
typename array<T, S>::iterator array<T, S>::begin() {
  return iterator(arr_);
}

template <typename T, std::size_t S>
typename array<T, S>::const_iterator array<T, S>::begin() const {
  return const_iterator(arr_);
}

template <typename T, std::size_t S>
typename array<T, S>::iterator array<T, S>::end() {
  return iterator(arr_ + size_);
}

template <typename T, std::size_t S>
typename array<T, S>::const_iterator array<T, S>::end() const {
  return const_iterator(arr_ + size_);
}

template <typename T, std::size_t S>
bool array<T, S>::empty() const {
  return false;
}

template <typename T, std::size_t S>
constexpr typename array<T, S>::size_type array<T, S>::size() const {
  return S;
}

template <typename T, std::size_t S>
constexpr typename array<T, S>::size_type array<T, S>::max_size() const {
  return S;
}

template <typename T, std::size_t S>
void array<T, S>::swap(array &other) {
  CopySwapWithStd(*this, other);
}

template <typename T, std::size_t S>
void array<T, S>::fill(const_reference value) {
  for (auto i = begin(); i != end(); ++i) {
    *i = value;
  }
}

template <typename T, std::size_t S>
void array<T, S>::CopySwapWithStd(array &one, array &two) noexcept {
  std::swap(one.arr_, two.arr_);
  std::swap(one.size_, two.size_);
}

}  // namespace s21

#endif  // SRC_S21_ARRAY_H_
