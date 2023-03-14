#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <functional>

template <typename Iter>
void print(Iter begin, Iter end) {
  while (begin != end) {
    std::cout << *begin << " ";
    ++begin;
  }
  std::cout << std::endl;
}

int main() {
  std::vector<int> v{5, 3, 1, 2, 3, 4};

  auto result = std::find(v.begin(), v.end(), 3); // 하나만 딱 찾아서 첫번째 값이 나옴
  auto result2 = std::find(result + 1, v.end(), 3); // 그 다음 원소를 찾고 싶으면? +1 부터 찾기 시작하면 됨
  std::cout << std::distance(v.begin(), result) << std::endl;
  std::cout << std::distance(v.begin(), result2) << std::endl;

  auto current = v.begin();
  while (true) {
    current = std::find(current, v.end(), 3);
    if (current == v.end()) break;
    std::cout << std::distance(v.begin(), current) << std::endl;
    ++current;
  }

  current = v.begin();
  while (true) {
    current = std::find_if(current, v.end(), [](int i) { return (i % 3 == 2); }); // 특정 조건을 만족하는 인자 찾기
    if (current == v.end()) break;
    std::cout << std::distance(v.begin(), current) << std::endl;
    ++current;
  }

  // set이나 map 등은 find를 지원하는데, 이를 이용하는 것이 더 빠르다. std::find의 경우 해당 입력 구조에 대한 정보가 없어서 순차 탐색하므로 느림
}