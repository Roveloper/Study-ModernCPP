#include <iostream>
#include <memory>

class A {
  int *data;

  public:
  A() {
    std::cout << "get resource" << std::endl;
    data = new int[100];
  }

  void some() {std::cout << "일반 포인터와 동일하게 사용 가능" << std::endl;}

  void do_sth(int a) {
    std::cout << "do sth" << std::endl;
    data[0] = a;
  }

  ~A() {
    std::cout << "call destructor" << std::endl;
    delete[] data;
  }
};

void do_something(std::unique_ptr<A>& ptr) { // 이런 식의 동작이 안되는 것은 아니지만, unique_ptr을 다른 곳에서 소유할 수 있게 되므로, 이러한 방식을 사용해서는 안됨
  ptr->do_sth(3);
}

void do_something_correctly(A* ptr) {
  ptr->do_sth(3);
}

int main() {
  std::unique_ptr<A> pa(new A());
  do_something(pa);
  do_something_correctly(pa.get());
}