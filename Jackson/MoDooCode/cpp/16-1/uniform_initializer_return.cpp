#include <iostream>

class A {
  public:
    A(int x, double y) { std::cout << "A constructor Called" << std::endl; }
};

A func() {
  return {1, 2.3}; // Same as A{1, 2.3} 
}

int main() {
  func();
}