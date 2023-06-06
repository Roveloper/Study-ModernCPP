#include <iostream>

template <typename T>
void show_value(T t) {
  std::cout << "Not Pointer : " << t << std::endl;
}

template <typename T>
void show_value(T* t) {
  std::cout << "Pointer : " << *t << std::endl;
}

template <typename T>
void show_value_type_traits(T t) {
  if constexpr (std::is_pointer<T>::value) { // constexpr이 없으면 오류 발생함
    // True인 부분만 컴파일되고, 그렇지 않은 부분은 컴파일 되지 않으므로, 오류가 발생하지 않음!
    std::cout << "this is Pointer : " << *t << std::endl;
  } else {
    std::cout << "this is Not Pointer : " << t << std::endl;
  }
  // std::is_pointer_v<T>로도 사용이 가능함
}

int main() {
  int x = 3;
  show_value(x);

  int* p = &x;
  show_value(p);

  show_value_type_traits(x);
  show_value_type_traits(p);
}