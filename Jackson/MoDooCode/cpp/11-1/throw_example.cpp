#include <iostream>
#include <stdexcept>

template <typename T>
class Vector {
  public:
    Vector(size_t size) : size_(size) {
      data_ = new T[size_];
      for (int i = 0; i < size_; ++i) {
        data_[i] = 3;
      }
    }

    const T& at(size_t index) const {
      if (index >= size_) {
        throw std::out_of_range("index out of range"); // return type과 상관없이 보낼 수 있으며, 객체를 던짐
        // 해당 위치에서 즉시 함수가 종료되며, 가장 가까운 예외를 받는 부분 (try-catch)으로 이동
        // 물론 추가적으로 객체를 순차적으로 모두 소멸시킴
        // out_of_range, overflow_error, length_error, runtime_error 등의 예외가 있음
      }
      return data_[index];
    }

    ~Vector() { delete[] data_; }

  private:
    T* data_;
    size_t size_;
};

int main() {
  Vector<int> v(3);

  int index, data = 0;
  std::cin >> index;

  try {
    data = v.at(index); // try 구문 안에서 throw가 발생하면, catch 구문으로 이동
  } catch (std::out_of_range& e) { // 입력으로 들어온 객체 타입과 비교하여, 일치하면 해당 catch가 동작
    std::cout << e.what() << std::endl;
  }

  std::cout << "read data: " << data << std::endl;
}