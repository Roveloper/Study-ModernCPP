#include <iostream>
#include <string>

template <typename T> class Vector {
    T *data_;
    int capacity_;
    int length_;

  public:
    Vector(int n = 1);

    void push_back(const T value);

    const T &operator[](int i);
    T operator[](int i) const;

    void remove(int x); // 삭제가 아니라, 한 칸씩 앞으로 당기고 사이즈를 줄임

    int size();

    ~Vector();
};

template<>
class Vector<bool> {
  unsigned int* data_;
  int capacity_;
  int length_;

  public:
    typedef bool value_type;

    Vector(int n = 1);
    void push_back(bool s);
    bool operator[](int i);
    void remove(int x);
    int size();
    ~Vector();
};

#include "myvector_impl.hpp"
