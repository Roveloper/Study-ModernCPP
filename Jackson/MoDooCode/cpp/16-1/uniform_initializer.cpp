#include <iostream>

class A {
  public:
    A(int x) { std::cout << "A Constructor Called" << std::endl; }
};

int main() {
  A a(3.5); // narrow-conversion possible
  A b{3.5}; // narrow-conversion impossible (double --> int)
}