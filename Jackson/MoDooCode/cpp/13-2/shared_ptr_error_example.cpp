#include <iostream>
#include <memory>

class A {
  int* data;

 public:
  A() {
    data = new int[100];
    std::cout << "자원을 획득함!" << std::endl;
  }

  ~A() {
    std::cout << "소멸자 호출!" << std::endl;
    delete[] data;
  }
};

int main() {
  A* a = new A();

  std::shared_ptr<A> pa1(a);
  std::shared_ptr<A> pa2(a);

  std::cout << pa1.use_count() << std::endl;
  std::cout << pa2.use_count() << std::endl;
}