#include "myvector.hpp"
#include "test_function.hpp"

int main() {
  Vector<int> vec_int;
  vec_int.push_back(1);
  vec_int.push_back(2);

  std::cout << vec_int[0] << ", " << vec_int[1] << std::endl;

  Vector<std::string> vec_str;
  vec_str.push_back("Hello");
  vec_str.push_back("World");
  std::cout << vec_str[0] << ", " << vec_str[1] << std::endl;

  my_test::print_hello();

  Vector<bool> bool_vec;
  bool_vec.push_back(true);
  bool_vec.push_back(true);
  bool_vec.push_back(false);
  bool_vec.push_back(false);
  bool_vec.push_back(false);
  bool_vec.push_back(true);
  bool_vec.push_back(true);
  bool_vec.push_back(true);
  bool_vec.push_back(true);
  bool_vec.push_back(true);
  bool_vec.push_back(true);
  bool_vec.push_back(true);
  bool_vec.push_back(true);
  bool_vec.push_back(true);
  bool_vec.push_back(true);

  std::cout << "--------- bool vector --------" << std::endl;
  for (int i = 0; i < bool_vec.size(); ++i) {
    std::cout << bool_vec[i];
  }
  std::cout << std::endl;

  return 0;
  
}
