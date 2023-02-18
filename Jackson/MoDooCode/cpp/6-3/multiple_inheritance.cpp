#include <iostream>

class A {
 public:
  int a;

  A() { std::cout << "A 생성자 호출" << std::endl; }
};

class B {
 public:
  int b;

  B() { std::cout << "B 생성자 호출" << std::endl; }
};

class C : public A, public B { // 적는 순서에 따라서, 호출되는 생성자의 순서가 달라진다. (B, A로 적으면 B, A 순으로 생성자가 호출됨)
 public:
  int c;

  C() : A(), B() { std::cout << "C 생성자 호출" << std::endl; }
};
int main() { C c; }

// 다중 상속 시 유의 사항
// 상속 받는 여러 개의 클래스가 같은 이름의 변수, 함수를 포함해서는 안된다.

// 다이아몬드 상속을 통해서, 변수 또는 함수의 이름이 겹치는 경우도 주의!

// 그치만 해결 방법이 있다!
// public으로 상속을 받는 것이 아니라, virtual public으로 상속을 받으면 된다!

// 다중 상속을 사용해야하는 경우?
// 상황에 따라서, Bridge Pattern, Nested Generalization, Multiple Inheritance를 적절히 활용하면 좋다.
