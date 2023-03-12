#include <iostream>

template <int X, int Y>
struct GCD {
  static const int value = GCD<Y, X % Y>::value;
};

template <int X>
struct GCD<X, 0> {
  static const int value = X;
};

int main() {
  std::cout << "gcd (24, 36) :: " << GCD<24, 36>::value << std::endl;
}