#include <iostream>

int sum_all() { return 0; }

template <typename... Ints>
int sum_all(int num, Ints... nums) {
  return num + sum_all(nums...);
}

template <typename... Ints>
double average(Ints... nums) {
  std::cout << sizeof...(nums) << std::endl;
  return static_cast<double>(sum_all(nums...)) / sizeof...(nums); // sizeof... 은 가변 템플릿에서만 사용할 수 있으며, 가변 인자의 개수를 반환합니다.
}

int main() {
  std::cout << average(1, 4, 2, 3, 10) << std::endl;
  std::cout << sizeof(1) << std::endl;
  std::cout << sizeof(int) << std::endl;
  return 0;
}