#include <iostream>
#include <string>

template <typename T>
T max(T& a, T& b) {
  return a > b ? a : b;
}

int main() {
  int a = 1, b = 2;
  std::cout << "Max (" << a << ", " << b << ") = " << max(a, b) << std::endl;
  // 함수 호출 시, 굳이 max<int>(a, b)라고 쓰지 않았음!

  std::string s = "hello", t = "world";
  std::cout << "Max (" << s << ", " << t << ") = " << max(s, t) << std::endl;
  // 마찬가지로, 굳이 max<std::string>(a, b)라고 쓰지 않았음!
  // 이는 컴파일러가 알아서 타입을 추론해줍니다. (type deduction)

  return 0;
}