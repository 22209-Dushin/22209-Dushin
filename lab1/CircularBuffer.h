#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

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
  CircularBuffer();
  explicit CircularBuffer(int capacity);
  CircularBuffer(int capacity, const T& elem);
  CircularBuffer(const CircularBuffer& cb);
  ~CircularBuffer();
  int getIndex(int i);
  T& operator[](int i);
  const T& operator[](int i) const;
  T& at(int i);
  const T& at(int i) const;
  T& front();
  T& back();
  const T& front() const;
  const T& back() const;
  T* linearized();
  bool is_linearized() const;
  void rotate(int new_begin);
  int size() const;
  bool empty() const;
  bool full() const;
  int reserve() const;
  int capacity() const;
  void set_capacity(int new_capacity);
  void resize(int new_size, const T& item = T());
  CircularBuffer& operator=(const CircularBuffer& cb);
  void swap(CircularBuffer& cb);
  void push_back(const T& item = T());
  void push_front(const T& item = 0);
  void pop_back();
  void pop_front();
  void clear();
  void insert(int pos, const T& item);
  void erase(int first, int last);
};

bool operator==(const CircularBuffer& a, const CircularBuffer& b);
bool operator!=(const CircularBuffer& a, const CircularBuffer& b);

#endif
