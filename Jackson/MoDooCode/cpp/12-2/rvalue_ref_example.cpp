#include <iostream>

void show_value(int&& t) { std::cout << "rvalue : " << t << std::endl; }

int main() {
  show_value(5);

  int x = 3;
  // show_value(x);
  show_value(std::move(x));
}