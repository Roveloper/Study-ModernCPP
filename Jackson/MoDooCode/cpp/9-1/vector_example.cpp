#include "myvector.hpp"

int main() {
  Vector<int> vec_int;
  vec_int.push_back(1);
  vec_int.push_back(2);

  std::cout << vec_int[0] << ", " << vec_int[1] << std::endl;

  Vector<std::string> vec_str;
  vec_str.push_back("Hello");
  vec_str.push_back("World");
  std::cout << vec_str[0] << ", " << vec_str[1] << std::endl;

  return 0;
}
