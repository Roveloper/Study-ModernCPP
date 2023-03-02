#include <iostream>
#include <string>

// template <typename T> == template <class T> 동일한 의미 but, typename T를 권장

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
