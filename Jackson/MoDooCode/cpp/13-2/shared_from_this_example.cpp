#include <iostream>
#include <memory>

class A : public std::enable_shared_from_this<A> {
  int *data;

 public:
  A() {
    data = new int[100];
    std::cout << "자원을 획득함!" << std::endl;
  }

  ~A() {
    std::cout << "소멸자 호출!" << std::endl;
    delete[] data;
  }

  std::shared_ptr<A> get_shared_ptr() { return shared_from_this(); } // 객체 내부에서 이와 같이 shared_ptr을 반환하는 함수를 만들고 싶다면?
  // std::enable_shared_from_this<A>를 상속받아야 문제 없이 만들어낼 수 있음
};

int main() {
  std::shared_ptr<A> pa1 = std::make_shared<A>();
  std::shared_ptr<A> pa2 = pa1->get_shared_ptr(); // 이렇게 하면 문제 없이 작동함

  std::cout << pa1.use_count() << std::endl;
  std::cout << pa2.use_count() << std::endl;

  // 하지만 일반 객체를 통해서 생성하면?
  A* a = new A();
  std::shared_ptr<A> pa3 = a->get_shared_ptr(); // 이렇게 하면 문제가 발생함
}