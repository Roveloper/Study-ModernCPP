// 컨테이너 일부 또는 전체를 순회하며 특정 작업을 진행하는 것을 transform 함수가 도와줌

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

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

  print(v.begin(), v.end());

  std::vector<int> v2(10, 0);
  std::transform(v.begin(), v.end(), v.begin(), [](int i) { return ++i; }); // 첫번째 인자부터 두번째 인자까지 네번째 인자를 적용한 결과는 세번째 인자부터 적용
  std::transform(v.begin(), v.end(), v2.begin(), [](int i) { return ++i; }); // 첫번째 인자부터 두번째 인자까지 네번째 인자를 적용한 결과는 세번째 인자부터 적용 (v2.begin()에서부터 복사가 진행된다는 뜻)
  // 문제는 당연히 복사하려는 공간의 자리가 모자라면 seg fault 발생
  print(v.begin(), v.end());
  print(v2.begin(), v2.end());
}