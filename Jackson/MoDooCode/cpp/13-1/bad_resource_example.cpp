#include <iostream>

class A {
  int* data;

  public:
  A() {
    data = new int[100];
    std::cout << "get resource" << std::endl;
  }

  ~A() {
    std::cout << "call destructor" << std::endl;
    delete[] data;
  }
};

void do_something() {
  A* pa = new A(); // 동적할당으로 생성한 객체는 해당 함수를 탈출해도 사라지지 않음
}

int main() {
  do_something();
  return 0;
}