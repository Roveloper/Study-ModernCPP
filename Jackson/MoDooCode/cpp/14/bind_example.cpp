#include <functional>
#include <iostream>

void add(int x, int y) {
  std::cout << x << " + " << y << " = " << x + y << std::endl;
}

void subtract(int x, int y) {
  std::cout << x << " - " << y << " = " << x - y << std::endl;
}

int main() {
  auto add_with_2 = std::bind(add, 2, std::placeholders::_1); // 순서대로 대체됨 첫번째 인자에 2가 들어감 (x = 2)
  add_with_2(3);

  add_with_2(3, 4); // 2번째 인자는 무시됨)

  auto subtract_from_2 = std::bind(subtract, std::placeholders::_1, 2);
  auto negate = std::bind(subtract, std::placeholders::_2, std::placeholders::_1);

  subtract_from_2(3);
  negate(4, 2);

}