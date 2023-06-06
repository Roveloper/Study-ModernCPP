#include <iostream>

template <int N>
struct A {
  int operator()() { return N; }
};

int main() {
  constexpr int size = 3;
  int arr[size];

  constexpr int N = 10;
  A<N> a;
  std::cout << a() << std::endl;

  constexpr int number = 3;
  enum B { x = number, y, z };
  std::cout << B::x << std::endl;

  // constexpr은 const이지만,
  // const는 constexpr이 아닙니다.
  // constexpr은 값이 컴파일 타임에 지정되지만
  // const는 컴파일 타임에 꼭 값을 알지 못해도 상관 없습니다.
}