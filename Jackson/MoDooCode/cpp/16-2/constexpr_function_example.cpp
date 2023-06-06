#include <iostream>

int factorial(int N) {
  int total = 1;
  for (int i = 1; i <= N; ++i) {
    total *= i;
  }
  return total;
}

constexpr int factorial_constexpr(int N) {
  int total = 1;
  for (int i = 1; i <= N; ++i) {
    total *= i;
  }
  return total;
}

// constexpr 함수는 다음 내용을 사용할 수 없습니다.
// goto문 사용 (이런걸 누가 써...)
// 예외 처리 (C++20부터는 사용이 가능해졌습니다.)
// 리터럴 타입이 아닌 변수의 정의
// 리터럴 타입은 컴파일 타임에 정의할 수 있는 변수 타입을 의미하며
// void, char, int, bool, long, float, double, &, array
// 위의 타입 + 특정한 조건을 만족하는 타입만 사용이 가능합니다.
// 초기화 되지 않는 변수의 정의
// constexpr이 아닌 함수의 호출

template <int N>
struct A {
  int operator()() { return N; }
};

int main() {
  // A<factorial(5)> a; // 이런건 불가능함
  // 왜냐면 factorial(5)라는 값이 컴파일 타임에 계산될 수 있는 값이 아니기 때문
  A<factorial_constexpr(5)> a; // 얘는 return 값이 constexpr이므로, 가능!
  std::cout << a() << std::endl;

}