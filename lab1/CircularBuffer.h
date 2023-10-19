#include <stdexcept>
#include <algorithm>
#include <cstring>

typedef int T;

class CircularBuffer {
private:
  T* buffer;
  int m_head; 
  int m_tail; 
  int m_count; 
  int m_capacity;

public:
  CircularBuffer() : buffer(nullptr), m_head(0), m_tail(-1), m_count(0), m_capacity(0) {}
  explicit CircularBuffer(int capacity) : m_head(0), m_tail(-1), m_count(0), m_capacity(capacity) {
    buffer = new T[capacity];
  }
  CircularBuffer(int capacity, const T& elem) : m_head(0), m_tail(capacity -1), m_count(capacity), m_capacity(capacity) {
    buffer = new T[capacity];
    std::fill(buffer, buffer + capacity, elem);
  }
  CircularBuffer(const CircularBuffer& cb) : m_head(cb.m_head), m_tail(cb.m_tail), m_count(cb.m_count), m_capacity(cb.m_capacity) {
    buffer = new T[cb.m_capacity];
    std::memcpy(buffer, cb.buffer, cb.m_count * sizeof(T));
  }
  ~CircularBuffer() {
    delete[] buffer;
    buffer = nullptr;
  }
  T& operator[](int i) {

    return buffer[(m_head + i) % m_count];
  }
  const T& operator[](int i) const {
    return buffer[(m_head + i) % m_count];
  }
  T& at(int i) {
    if (i >= m_count || i < 0) {
      throw std::out_of_range("The index is out of range!");
    }
    return (*this)[i];
  }
  const T& at(int i) const {
    if (i >= m_count || i < 0) {
      throw std::out_of_range("The index is out of range!");
    }
    return (*this)[i];
  }
  T& front() { 
    return (*this)[0];
  }
  T& back() { 
    return (*this)[m_count - 1];
  }
  const T& front() const { 
    return (*this)[0];
  }
  const T& back() const { 
    return (*this)[m_count - 1];
  }
  T* linearized() {
    if (!this->is_linearized()) {
      int* newBuffer = new int[m_capacity];
      for (int i = 0; i < m_count; ++i) {
        newBuffer[i] = (*this)[i];
      }
      delete[] buffer;
      buffer = newBuffer;
      m_head = 0;
      m_tail = m_count - 1;
    }
    return buffer;
  }

  bool is_linearized() const {
    return m_head == 0;
  }
  void rotate(int new_begin) { 
    if (!(this->is_linearized())) {
    	buffer = (*this).linearized();
    }
    m_head = (m_head + new_begin) % m_count;
    m_tail = (m_tail + new_begin) % m_count;
    buffer = (*this).linearized();
  }
  
  
  int size() const {
    return m_count;
  }
  bool empty() const {
    return m_count == 0;
  }
  bool full() const {
    return m_capacity == m_count;
  }
  int reserve() const {
    return m_capacity - m_count;
  }
  int capacity() const {
    return m_capacity;
  }
  void set_capacity(int new_capacity) {
    if (m_capacity != new_capacity) {
    	T* newBuffer = new T[new_capacity];
    	for (int i = 0; i < m_count; ++i) {
      		newBuffer[i] = (*this)[i];
    	}

    	delete[] buffer;
    	buffer = nullptr;

    	if (m_count > new_capacity) {
      		m_count = new_capacity;
    	}
    	buffer = newBuffer;
    	m_head = 0;
    	m_tail = m_count - 1;
    	m_capacity = new_capacity;
  	}
 }
  void resize(int new_size, const T& item = T()) {
	if (new_size > m_capacity) {
		set_capacity(new_size);
	}
	if (new_size < m_count){
		m_count = new_size;
	}
	else {
	for (int i = m_count; i < new_size; ++i) {
		push_back(item);
	}
	}
  }
  CircularBuffer& operator=(const CircularBuffer& cb) {
    if (this != &cb) {
      delete[] buffer;
      buffer = new T[cb.m_capacity];
      memcpy(buffer, cb.buffer, cb.m_capacity * sizeof(T));
      m_head = cb.m_head;
      m_capacity = cb.m_capacity;
      m_count = cb.m_count;
      m_tail = cb.m_tail;
    }
    return *this;
  }
  void swap(CircularBuffer& cb) {
    std::swap(buffer, cb.buffer);
    std::swap(m_head, cb.m_head);
    std::swap(m_tail, cb.m_tail);
    std::swap(m_count, cb.m_count);
    std::swap(m_capacity, cb.m_capacity);
  }
  
  void push_back(const T& item = T()) {
   if (this->full()) {
      buffer[m_head] = item;
      m_tail = m_head;
      m_head = (m_head + 1) % m_capacity;
   }
   else {
   	  ++m_count;
      m_tail = (m_tail + 1) % m_count;
      buffer[m_tail] = item;
   }
  }
 
  void push_front(const T& item = 0) {
  	if (this->empty()) {
  		buffer[0] = item;
        m_tail = m_head;
        ++m_count;
  	}
    else if (this->full()) {
      buffer[m_tail] = item;
      m_head = m_tail;
      m_tail = (m_tail - 1 + m_capacity) % m_capacity;
    }
    else {
      m_head = (m_head - 1 + m_capacity) % m_capacity;
      buffer[m_head] = item;
      ++m_count;
    }
  }
  void pop_back() {
    if (m_count != 0) {
      m_tail = (m_tail - 1 + m_capacity) % m_capacity;
      --m_count;
    }
  }
  void pop_front() {
    if (m_count != 0) {
      ++m_head;
      --m_count;
    }
  }
  void clear() {
    delete[] buffer;
    buffer = nullptr;
    m_head = 0;
    m_count = 0;
    m_tail = -1;
  }
  void insert(int pos, const T& item) {
    if (this->full()) {
      for (int i = m_head; i < pos; ++i) {
        buffer[i % m_capacity] = buffer[(i + 1) % m_capacity];
      }
      buffer[pos] = item;
    }
    else {
      if (pos > m_count) {
        pos = m_count;
      }
      for (size_t i = m_count; i > pos; --i) {
        buffer[(m_head + i) % m_capacity] = buffer[(m_head + i - 1) % m_capacity];
      }
      buffer[(m_head + pos) % m_capacity] = item;
      m_tail = (m_tail + 1) % m_capacity;
      m_count++;
    }
  }
  void erase(int first, int last) {
    for (int i = first; i < m_count - last + first; ++i) {
      (*this)[i] = (*this)[i + last - first];
    }
    m_count = m_count - last + first;
    m_tail = (m_head + m_count - 1) % m_capacity;
  }
};

bool operator==(const CircularBuffer& a, const CircularBuffer& b) {
  if (a.size() != b.size() || a.capacity() != b.capacity()) {
    return false;
  }
  for (int i = 0; i < a.size() && i < b.size(); ++i) {
    if (a[i] != b[i]) {
     return false;
    }
  }
   return true;
  } 
bool operator!=(const CircularBuffer& a, const CircularBuffer& b) {
  return !(a == b);
}



