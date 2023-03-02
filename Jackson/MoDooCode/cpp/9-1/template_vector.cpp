#include <iostream>
#include <string>

// template <typename T> == template <class T> 동일한 의미 but, typename T를 권장

template <typename T> class Vector {
    T *data_; // array list를 구현
    int capacity_;
    int length_;

  public:
    Vector(int n = 1) : data_(new T[n]), capacity_(n), length_(0) {}

    void push_back(const T value) {
        if (length_ == capacity_) {
            auto tmp = data_;
            data_ = new T[capacity_ * 2];
            for (int i = 0; i < length_; ++i) {
                data_[i] = tmp[i];
            }
            delete[] tmp;
            capacity_ *= 2;
        }
        data_[length_++] = value;
    }

    const T &operator[](int i) { return data_[i]; }
    T operator[](int i) const { return data_[i]; }

    void remove(int x) {
        for (int i = x + 1; i < length_; ++i) {
            data_[i - 1] = data_[i];
        }
        --length_;
    }

    int size() { return length_; }

    ~Vector() { delete[] data_; }
};

int main() {
  Vector<int> vec_int;
  vec_int.push_back(1);
  vec_int.push_back(2);

  std::cout << vec_int[0] << ", " << vec_int[1] << std::endl;

  Vector<std::string> vec_str;
  vec_str.push_back("Hello");
  vec_str.push_back("World");
  std::cout << vec_str[0] << ", " << vec_str[1] << std::endl;

  return 0;
}
