#include <algorithm>
#include <iostream>
#include <vector>

template <typename Iter>
void print(Iter begin, Iter end) {
  while (begin != end) {
    std::cout << *begin << " ";
    begin++;
  }
  std::cout << std::endl;
}
int main() {
  std::vector<int> vec;
  vec.push_back(5);
  vec.push_back(3);
  vec.push_back(1);
  vec.push_back(6);
  vec.push_back(4);
  vec.push_back(7);
  vec.push_back(2);

  std::cout << "정렬 전 ----" << std::endl;
  print(vec.begin(), vec.end());
  std::partial_sort(vec.begin(), vec.begin() + 3, vec.end()); // 시작부터 끝까지 중에 몇개만 정렬할 지 지정할 수 있음, 첫번째 인자와 마지막 인자는 시작과 끝 범위 지정, 가운데는 몇번까지 정렬할지 전달 (그 외는 랜덤하게 존재)
  // partial_sort는 O(NlogM) (N은 전체 원소 개수, 정렬하려는 부분의 크기는 M), 전체가 다 필요한 경우가 아닌 경우, 일반 std::sort 보다 빠름
  std::cout << "정렬 후 ----" << std::endl;
  print(vec.begin(), vec.end());
}