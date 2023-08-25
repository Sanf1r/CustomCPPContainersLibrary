#ifndef SRC_S21_VECTOR_H_
#define SRC_S21_VECTOR_H_

namespace s21 {
template <typename T>
class vector {
 public:
  class ConstIterator;

  // Public class Iterator
  class Iterator {
    friend class vector;

   public:
    using pointer = T *;
    using reference = T &;

   public:
    Iterator(pointer ptr);
    Iterator &operator++();
    Iterator operator++(int);
    Iterator &operator--();
    Iterator operator--(int);
    bool operator==(const Iterator &other);
    bool operator!=(const Iterator &other);
    reference operator*();
    operator ConstIterator() const;

   private:
    pointer ptr_;
  };

  // Public class ConstIterator
 public:
  class ConstIterator {
    friend class vector;

   public:
    using const_pointer = const T *;
    using const_reference = const T &;

   public:
    ConstIterator(const_pointer ptr);
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

  // Vector Member type
  using value_type = T;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using reference = T &;
  using const_reference = const T &;
  using iterator = Iterator;
  using const_iterator = const ConstIterator;
  using size_type = size_t;

  // Vector Member functions
  vector();
  explicit vector(size_type num);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &other);
  vector(vector &&other);
  ~vector();
  vector &operator=(const vector &other);
  vector &operator=(vector &&other) noexcept;

  // Vector Element access
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

  // Vector Iterators
  // begin() returns an iterator to the beginning
  iterator begin();
  const_iterator begin() const;
  // end() returns an iterator to the end
  iterator end();
  const_iterator end() const;

  // Vector Capacity
  // empty() checks whether the container is empty
  bool empty() const;
  // size() returns the number of elements
  size_type size() const;
  // max_size() returns the maximum possible number of elements
  size_type max_size() const;
  // reserve() allocate storage of size elements and copies current array
  // elements to a newely allocated array
  void reserve(size_type n);
  // capacity() returns the number of elements that can be held in currently
  // allocated storage
  size_type capacity() const;
  // shrink_to_fit() reduces memory usage by freeing unused memory
  void shrink_to_fit();

  // Vector Modifiers
  // clear() clears the contents
  void clear();
  // insert() inserts elements into concrete pos and returns the iterator that
  // points to the new element
  iterator insert(iterator pos, const_reference value);
  // erase() erases element at pos
  void erase(iterator pos);
  // push_back() adds an element to the end
  void push_back(const_reference element);
  // pop_back() removes the last element
  void pop_back();
  // swap() swaps the contents
  void swap(vector &other);
  // emplace() inserts new elements into the container directly before pos
  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args);
  // emplace_back() appends new elements to the end of the container
  template <typename... Args>
  void emplace_back(Args &&...args);

 private:
  pointer vect_;
  size_type size_;
  size_type cap_;

  // Vector Helper Methods
  void CopySwapWithStd(vector &one, vector &two) noexcept;
};

// Iterator class implementation

template <typename T>
vector<T>::Iterator::Iterator(pointer ptr) : ptr_(ptr) {}

template <typename T>
typename vector<T>::Iterator &vector<T>::Iterator::operator++() {
  ++ptr_;
  return *this;
}

template <typename T>
typename vector<T>::Iterator vector<T>::Iterator::operator++(int) {
  Iterator temp = *this;
  ++(*this);
  return temp;
}

template <typename T>
typename vector<T>::Iterator &vector<T>::Iterator::operator--() {
  --ptr_;
  return *this;
}

template <typename T>
typename vector<T>::Iterator vector<T>::Iterator::operator--(int) {
  Iterator temp = *this;
  --(*this);
  return temp;
}

template <typename T>
bool vector<T>::Iterator::operator==(const Iterator &other) {
  return ptr_ == other.ptr_;
}

template <typename T>
bool vector<T>::Iterator::operator!=(const Iterator &other) {
  return !(ptr_ == other.ptr_);
}

template <typename T>
typename vector<T>::Iterator::reference vector<T>::Iterator::operator*() {
  return *(this->ptr_);
}

template <typename T>
vector<T>::Iterator::operator ConstIterator() const {
  return ConstIterator(ptr_);
}

// ConstIterator class implementation

template <typename T>
vector<T>::ConstIterator::ConstIterator(const_pointer ptr) : ptr_(ptr) {}

template <typename T>
typename vector<T>::ConstIterator &vector<T>::ConstIterator::operator++() {
  ++ptr_;
  return *this;
}

template <typename T>
typename vector<T>::ConstIterator vector<T>::ConstIterator::operator++(int) {
  ConstIterator temp = *this;
  ++(*this);
  return temp;
}

template <typename T>
typename vector<T>::ConstIterator &vector<T>::ConstIterator::operator--() {
  --ptr_;
  return *this;
}

template <typename T>
typename vector<T>::ConstIterator vector<T>::ConstIterator::operator--(int) {
  ConstIterator temp = *this;
  --(*this);
  return temp;
}

template <typename T>
typename vector<T>::ConstIterator::const_reference
vector<T>::ConstIterator::operator*() const {
  return *(this->ptr_);
}

template <typename T>
bool vector<T>::ConstIterator::operator==(const ConstIterator &other) {
  return ptr_ == other.ptr_;
}

template <typename T>
bool vector<T>::ConstIterator::operator!=(const ConstIterator &other) {
  return !(ptr_ == other.ptr_);
}

// Vector class implementation

template <typename T>
vector<T>::vector() {
  size_ = cap_ = 0;
  vect_ = nullptr;
}

template <typename T>
vector<T>::vector(size_type num) {
  if (num > max_size())
    throw std::length_error("Cannot create vector larger than max_size()");
  size_ = cap_ = num;
  vect_ = reinterpret_cast<pointer>(new int8_t[size_ * sizeof(value_type)]);
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items)
    : vector(items.size()) {
  auto ptr = items.begin();
  std::uninitialized_copy(ptr, ptr + items.size(), vect_);
}

template <typename T>
vector<T>::vector(const vector &other) {
  size_ = other.size_;
  cap_ = other.cap_;
  vect_ = reinterpret_cast<pointer>(new int8_t[size_ * sizeof(value_type)]);
  std::uninitialized_copy(other.vect_, other.vect_ + other.size_, vect_);
}

template <typename T>
vector<T>::vector(vector &&other) {
  CopySwapWithStd(*this, other);
  other.size_ = other.cap_ = 0;
  other.vect_ = nullptr;
}

template <typename T>
vector<T>::~vector() {
  clear();
  delete[] reinterpret_cast<int8_t *>(vect_);
}

template <typename T>
typename vector<T>::vector &vector<T>::operator=(const vector &other) {
  if (this != &other) {
    vector temp(other);
    CopySwapWithStd(*this, temp);
  }
  return *this;
}

template <typename T>
typename vector<T>::vector &vector<T>::operator=(vector &&other) noexcept {
  if (this != &other) {
    vector temp(std::move(other));
    CopySwapWithStd(*this, temp);
  }
  return *this;
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("Position is out_of_range\n");
  }
  return vect_[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::at(size_type pos) const {
  if (pos >= size_) {
    throw std::out_of_range("Position is out_of_range\n");
  }
  return vect_[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return vect_[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::operator[](size_type pos) const {
  return vect_[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::front() {
  return vect_[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() const {
  return vect_[0];
}

template <typename T>
typename vector<T>::reference vector<T>::back() {
  return vect_[size_ - 1];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() const {
  return vect_[size_ - 1];
}

template <typename T>
typename vector<T>::pointer vector<T>::data() {
  return vect_;
}

template <typename T>
typename vector<T>::const_pointer vector<T>::data() const {
  return vect_;
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  return iterator(vect_);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::begin() const {
  return const_iterator(vect_);
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
  return iterator(vect_ + size_);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::end() const {
  return const_iterator(vect_ + size_);
}

template <typename T>
bool vector<T>::empty() const {
  return size_ == 0;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() const {
  return size_;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() const {
  return SIZE_MAX / sizeof(value_type) / 2;
}

template <typename T>
void vector<T>::reserve(size_type n) {
  if (n <= cap_) return;
  pointer newarr =
      reinterpret_cast<pointer>(new int8_t[n * sizeof(value_type)]);
  std::uninitialized_copy(vect_, vect_ + size_, newarr);
  for (size_type i = 0; i < size_; ++i) {
    vect_[i].~value_type();
  }
  delete[] reinterpret_cast<int8_t *>(vect_);
  vect_ = newarr;
  cap_ = n;
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const {
  return cap_;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (cap_ > size_) {
    pointer newarr =
        reinterpret_cast<pointer>(new int8_t[size_ * sizeof(value_type)]);
    std::uninitialized_copy(vect_, vect_ + size_, newarr);
    delete[] reinterpret_cast<int8_t *>(vect_);
    vect_ = newarr;
    cap_ = size_;
  }
}

template <typename T>
void vector<T>::clear() {
  for (size_type i = 0; i < size_; ++i) {
    vect_[i].~value_type();
  }
  size_ = 0;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  if (size_ == 0) {
    push_back(value);
    return begin();
  }
  if (size_ + 1 <= cap_) {
    vector<value_type> temp(*this);
    *pos.ptr_ = value;
    for (size_type i = pos.ptr_ - vect_, j = 1; i < size_; ++i, ++j) {
      *(pos.ptr_ + j) = temp[i];
    }
    ++size_;
  } else {
    cap_ = size_ * 2 + 1;
    pointer newarr =
        reinterpret_cast<pointer>(new int8_t[cap_ * sizeof(value_type)]);
    for (size_type i = 0, j = 0; i < size_; ++i, ++j) {
      if (pos.ptr_ == vect_ + i) {
        new (newarr + j) value_type(value);
        pos.ptr_ = newarr + j;
        ++j;
      }
      new (newarr + j) value_type(vect_[i]);
    }
    delete[] reinterpret_cast<int8_t *>(vect_);
    vect_ = newarr;
    ++size_;
  }
  return pos;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  if (pos == end()) {
    throw std::logic_error(
        "The end() iterator cannot be used as a value for pos\n");
  }
  vector<value_type> temp(*this);
  size_type erase = pos.ptr_ - vect_;
  for (size_type i = erase, j = erase + 1; j < temp.size_;) {
    vect_[i++] = temp[j++];
  }
  --size_;
}

template <typename T>
void vector<T>::push_back(const_reference element) {
  if (size_ == cap_) {
    reserve(size_ + 5);
  }
  new (vect_ + size_) value_type(element);
  ++size_;
}

template <typename T>
void vector<T>::pop_back() {
  if (size_ > 0) {
    --size_;
    (vect_ + size_)->~value_type();
  }
}

template <typename T>
void vector<T>::swap(vector &other) {
  CopySwapWithStd(*this, other);
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::emplace(const_iterator pos,
                                                Args &&...args) {
  iterator result(const_cast<value_type *>(pos.ptr_));
  for (auto value : {std::forward<Args>(args)...}) {
    result = insert(result, value);
    ++result;
  }
  return --result;
}

template <typename T>
template <typename... Args>
void vector<T>::emplace_back(Args &&...args) {
  for (auto value : {std::forward<Args>(args)...}) {
    push_back(value);
  }
}

template <typename T>
void vector<T>::CopySwapWithStd(vector &one, vector &two) noexcept {
  std::swap(one.size_, two.size_);
  std::swap(one.cap_, two.cap_);
  std::swap(one.vect_, two.vect_);
}

}  // namespace s21

#endif  // SRC_S21_VECTOR_H_
