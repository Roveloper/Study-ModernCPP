// RAII --> Resource Acquisition Is Initialization
// 자원 획득은 곧 초기화다.
// 예외가 발생해서 함수를 탈출하더라도, 함수 스택 (힙 아님)에 정의된 객체들은 모두 소멸자가 호출됩니다. (stack unwinding)
// 또한, 예외가 발생하지 않으면, 당연히 해당 함수를 탈출할 때, 스택에 정의된 객체들이 소멸됩니다.
// 따라서, 소멸자에 자원을 해제하는 코드를 넣으면? 자원 해제가 보장됩니다.
// 따라서, 포인터를 객체화 시켜서, 소멸자에서 소멸하도록 만들어놓은 것이 바로 스마트 포인터입니다.

// 1. unique_ptr
// C++의 메모리 문제는 크게 두가지.
// 첫번째는 메모리를 사용한 후 해제하지 않은 경우 (memory leak) --> 장시간 사용할 경우 문제가 될 수 있음. (out of memory 발생)
// 위 문제는 RAII 패턴을 이용하면 해결 가능.
// 두번째는 해제한 메모리를 참조하는 경우 (double free, null pointer dereference) --> 프로그램 죽음 (seg fault 발생)

// Data* data = new Data();
// Data* data2 = data;

// delete data;
// delete data2; // double free 발생

// 이러한 문제가 발생하는 원인은 객체의 소유권이 명확하지 않아서 입니다. (그러니까 소유한 자가 해제까지 책임져야하는데, 누구 것인지 모름)
// 따라서, 포인터에 객체의 유일한 소유권을 부여해서, 해당 객체를 끝까지 책임진다고 한다면, 이와 같은 문제를 해결 가능

// 위의 상황에서 data에 new Data()의 소유권을 가지게 한다면, 객체의 소유권이 없는 data2는 delete를 할 수 없습니다. (compile error가 발생할 것)
// 이렇게, 특정 객체에 대한 유일한 소유권을 부여하는 포인터 객체를 unique_ptr이라고 합니다.

#include <iostream>
#include <memory>

class A {
  int *data;

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
  std::unique_ptr<A> pa(new A()); // 이렇게 쓸 수 있다고 해도, 이렇게 쓰면 혼남
  // std::unique_ptr<A> pa = std::make_unique<A>(); // 이렇게 써야 unique함을 보장할 수 있음
  pa->some();
}

int main() {
  do_something();
}