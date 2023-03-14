#include <algorithm>
// #include <functional>
#include <iostream>
#include <string>
#include <vector>

template <typename Iter>
void print(Iter begin, Iter end) {
  while (begin != end) {
    std::cout << "[" << *begin << "] ";
    ++begin;
  }
  std::cout << std::endl;
}

int main() {
  std::vector<int> v = {5, 3, 1, 2, 3, 4, 3};

  print(v.begin(), v.end());

  std::cout << "remove 3" << std::endl;
  auto result = std::remove(v.begin(), v.end(), 3); // remove는 단순히 3 이외의 값들을 앞으로 당겨서 정렬하고, 쓸모없어진 부분의 Iterator를 넘겨줄 뿐이다. (그래서 erase를 안쓰면 이상한 값이 남을 수 있음)
  print(v.begin(), v.end());
  
  std::cout << std::distance(v.begin(), result) << std::endl;
  std::cout << "after remove" << std::endl;
  v.erase(result, v.end());
  print(v.begin(), v.end());

  v.erase(std::remove(v.begin(), v.end(), 5), v.end()); // 시작부터 끝 사이에서 5를 찾아서 맨 뒤로 옮긴 다음, 쓸모없어진 부분을 삭제한다 (그래서 시작부터 끝까지 중에 5를 모두 지울 수 있음)
  // remove에서 사용하는 Iterator는 ForwardIterator이므로 list, set, map 등에서도 모두 사용할 수 있음!
  print(v.begin(), v.end());

  return 0;
}