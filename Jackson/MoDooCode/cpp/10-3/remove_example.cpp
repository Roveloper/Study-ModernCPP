#include <vector>
#include <iostream>

int main() {
  std::vector<int> v = {1, 3, 5, 7, 10, 3, 3, 9, 3, 15, 3};
  v.erase(v.begin() + 3); // 7이 지워진다 (v[3]에 해당하는 값이 삭제)

  for (const auto& val : v) {
    std::cout << val << " ";
  }
  std::cout << std::endl;

  auto iter = v.begin();
  while (iter != v.end()) {
    if (*iter == 3) {
      v.erase(iter);
      iter = v.begin();
    }
    ++iter;
  }

  for (const auto& val : v) {
    std::cout << val << " ";
  }
  std::cout << std::endl;

  return 0;
}