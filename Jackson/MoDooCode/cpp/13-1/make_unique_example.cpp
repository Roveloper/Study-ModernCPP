#include <iostream>
#include <memory>

class Foo {
  int a, b;

  public:
  Foo(int a, int b) : a(a), b(b) {
    std::cout << "Constructor" << std::endl;
  }
  void print() {
    std::cout << a << ", " << b << std::endl;
  }
  ~Foo() {
    std::cout << "Destructor" << std::endl;
  }
};

int main() {
  auto ptr = std::make_unique<Foo>(3, 5); // make_unique는 unique_ptr을 생성하는 함수이며, 가장 적절한 방법 C++14이상에서 사용 가능
  ptr->print();
}