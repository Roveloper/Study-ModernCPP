#include <iostream>

template <typename T>
void wrapper(T&& u) { // Template 인자 T에 대해 Rvalue reference를 취하는 것을 universal_reference라고 함, 이놈은 rvalue reference만을 받지 않습니다.
// universal_reference는 우측값과 좌측값을 모두 받을 수 있습니다.
// 좌측값이 오는 경우 --> reference collapsing rule에 따라 T의 타입을 추론
// reference collapsing rule: T& & --> T&, T& && --> T&, T&& & --> T&, T&& && --> T&&
  // g(u); // 이렇게 처리하면, 우측값도 다시 전달이 될 때, u라는 lvalue에 담겨서 전달이 되므로, lvalue reference로 전달이 됩니다.
  // g(std::move(u)); // 이렇게 해버리면, 좌측값 참조도 우측값 참조로 전달이 되어버리는 이슈가 발생
  // 우리가 필요한 것은 진짜 우측값일 경우에만 우측값 참조로 전달하는 것이 목표!
  g(std::forward<T>(u)); // std::forward는 입력 u가 우측값 reference인 경우에만, move를 적용한 것 처럼 동작합니다! 우리가 정확히 원하던 내용

}

class A {};

void g(A& a) { std::cout << "lvalue reference called" << std::endl; }
void g(const A& a) { std::cout << "const lvalue reference called" << std::endl; }
void g(A&& a) { std::cout << "rvalue reference called" << std::endl; }

int main() {
  A a;
  const A ca;
  std::cout << "original______" << std::endl;
  g(a);
  g(ca);
  g(A());

  std::cout << "wrapper______" << std::endl;
  wrapper(a); // T&로 기본적으로 입력되며, T&& & --> T&로 변환
  wrapper(ca); // const T&로 기본적으로 입력되며, const T&& & --> const T&로 변환
  wrapper(A()); // T로 입력되며, T&&  --> T&&로 변환

}