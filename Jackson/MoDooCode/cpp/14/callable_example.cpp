#include <iostream>

struct S {
  void operator()(int a, int b) {
    std::cout << "a + b = " <<  a + b << std::endl;
  }
};

int main() {
  S some_obj; // 이것은 함수? 객체? --> 객체입니다. But, operator()를 통해서 함수처럼 사용할 수 있습니다.

  some_obj(3, 5); // some_obj.operator()(3, 5)입니다.

  auto f = [](int a, int b) { // 그렇다면 이것은? 함수? 객체? --> 람다 `함수` 입니다.
    std::cout << "a + b = " << a + b << std::endl;
  };
  f(3, 5);

  // 이와 같이 ()를 통해서 호출 할 수 있는 값들을 모두 Callable이라고 합니다.
}