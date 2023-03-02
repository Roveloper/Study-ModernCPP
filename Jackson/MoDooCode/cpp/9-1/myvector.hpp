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

    void remove(int x);

    int size();

    ~Vector();
};

#include "myvector_impl.hpp"
