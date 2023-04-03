#include <functional>
#include <iostream>
#include <string>

class A {
  int c;

  public:
    A(int c) : c(c) {};
    int some_func() { 
      std::cout << "내부 데이터 : " << ++c << std::endl;
      return c; 
    }
    int some_const_function() const {
      std::cout << "const function : " << c << std::endl;
      return c;
    }

    static void set() {
      std::cout << "Set is called" << std::endl;
    }
};

int main() {
  A a(5);
  // std::function<int()> f1 = a.some_func; // 이런건 불가능합니다. 왜냐하면, class 내부의 멤버함수들은 암시적으로 this를 입력받고 있기 때문이죠
  std::function<int(A)> ff = &A::some_func; // 일반 함수와 다르게 직접적으로 주소를 전달해줘야합니다 (&연산자를 이용)
  std::function<int(A&)> f1 = &A::some_func; // 이와 같이 함수의 주소를 직접 전달해줘야합니다.
  std::function<int(const A&)> f2 = &A::some_const_function;
  std::function<void()> fn = &A::set;
  ff(a);
  ff(a);
  ff(a);
  ff(a);
  f1(a);
  f1(a);
  f1(a);
  f1(a);
  f2(a);
  fn();
}