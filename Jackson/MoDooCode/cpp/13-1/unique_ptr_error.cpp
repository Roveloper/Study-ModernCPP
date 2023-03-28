#include <iostream>
#include <memory>

class A {
  int * data;

  public:
  A() {
    std::cout << "get resource" << std::endl;
    data = new int[100];
  }

  void some() {
    std::cout << "일반 포인터와 동일하게 사용 가능" << std::endl;
  }

  ~A() {
    std::cout << "call destructor" << std::endl;
    delete[] data;
  }
};

void do_something() {
  std::unique_ptr<A> pa(new A());
  std::unique_ptr<A> pb = pa; // deleted function error가 발생
  // deleted function error가 뭐임???
}

int main() {
  do_something();
}