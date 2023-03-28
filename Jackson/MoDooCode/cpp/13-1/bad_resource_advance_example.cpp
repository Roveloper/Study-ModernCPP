#include <iostream>

class A{
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

void thrower() {
  throw 1;
}

void do_something() {
  A* pa = new A();
  thrower();

  delete pa;
}

int main() {
  try {
    do_something();
  } catch (int i) {
    std::cout << "Exception caught: " << i << std::endl;  
  }
}
