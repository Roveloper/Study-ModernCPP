#include <iostream>
#include <vector>

template <typename T>
void wrapper(T& u) {
  std::cout << "wrapper called" << std::endl;
  g(u);
}

template <typename T>
void wrapper(const T& u) {
  std::cout << "const wrapper called" << std::endl;
  g(u);
}

class A {};

void g(A& a) { std::cout << "lvalue reference called" << std::endl; }
void g(const A& a) { std::cout << "const lvalue reference called" << std::endl; }
void g(A&& a) { std::cout << "rvalue reference called" << std::endl; }

int main() {
  A a;
  const A ca;

  std::cout << "original ----------" << std::endl;
  g(a);
  g(ca);
  g(A());

  std::cout << "Wrapper---------------" << std::endl;
  wrapper(a);
  wrapper(ca); // Template이 type deduction을 수행할 때, reference가 아닌 경우는 const를 무시합니다.
  wrapper(A()); // 무슨 난리를 쳐도, wrapper 안으로 들어간 A()는 rvalue가 아닌, lvalue가 되어서, rvalue reference 버전의 함수를 호출할 수 없다.
}

// 게다가 2개를 인자로 받는 Template을 정의한다면...?
// 아래와 같이, 일반 reference와 const reference를 구분하기 위해서 총 2^2 = 4개의 wrapper를 정의해야 한다.
// 3... 4... 5개로 늘어난다면? 이게 무슨...
// 귀찮다고 const T&만 있는 걸 정의한다면...? T&가 그냥 const T&로 동작해버립니다. (수정이 불가능)

template <typename T>
void wrapper(T& u, T& v) {
  g(u, v);
}
template <typename T>
void wrapper(const T& u, T& v) {
  g(u, v);
}

template <typename T>
void wrapper(T& u, const T& v) {
  g(u, v);
}
template <typename T>
void wrapper(const T& u, const T& v) {
  g(u, v);
}