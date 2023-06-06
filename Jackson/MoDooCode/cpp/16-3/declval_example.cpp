#include <iostream>
#include <utility>

template <typename T>
decltype(T().f()) call_f_and_return(T& t) {
  return t.f();
}

template <typename T>
decltype(std::declval<T>().f()) call_f_and_return_declval(T& t) {
  return t.f();
}

template <typename T>
auto call_f_and_return_auto(T& t) {
  return t.f();
}

struct A {
  int f() { return 0; }
};

struct B {
  B(int x) {}
  int f() { return 0; }
};

int main() {
  A a;
  B b(1);

  call_f_and_return(a);
  // call_f_and_return(b); // b는 default 생성자가 없어서, 오류가 발생!


  call_f_and_return_declval(a);
  call_f_and_return_declval(b); // b는 default 생성자가 없어서, 오류가 발생!

  call_f_and_return_auto(a);
  call_f_and_return_auto(b); // b는 default 생성자가 없어서, 오류가 발생!
}