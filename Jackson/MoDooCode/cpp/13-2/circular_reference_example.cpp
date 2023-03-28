#include <iostream>
#include <memory>

class A {
  int *data;
  std::shared_ptr<A> other;

 public:
  A() {
    data = new int[100];
    std::cout << "자원을 획득함!" << std::endl;
  }

  ~A() {
    std::cout << "소멸자 호출!" << std::endl;
    delete[] data;
  }

  void set_other(std::shared_ptr<A> other) { this->other = other; }
};

int main() {
  std::shared_ptr<A> pa1 = std::make_shared<A>();
  std::shared_ptr<A> pa2 = std::make_shared<A>();

  pa1->set_other(pa2);
  pa2->set_other(pa1);

  std::cout << pa1.use_count() << std::endl;
  std::cout << pa2.use_count() << std::endl;
}
