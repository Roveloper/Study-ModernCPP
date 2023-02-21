#include <iostream>
#include <string>

int main() {
  using namespace std::string_literals;
  std::string a = "hello"s;
  auto b = "world"s;
  std::cout << a << std::endl;
  std::cout << b << std::endl;
  std::cout << typeid(b).name() << std::endl;

  return 0;
}
