#include <iostream>
#include <vector>

int main() {
  std::vector<int> v(3);
  std::cout << "capacity of v: " << v.capacity() << std::endl;
  std::cout << v[4] << std::endl; // size, capacity와 상관없이 접근 가능하며, 오류 발생 가능성이 늘 있음
  std::cout << v.at(4) << std::endl; // size보다 크면 std::out_of_range 예외 발생

  std::vector<int> v2(10000000000000000); // 메모리가 부족하면 std::bad_alloc 예외 발생
}