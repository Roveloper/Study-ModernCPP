#include <iostream>
#include <vector>
#include <algorithm>

template <typename Iter>
void print(Iter begin, Iter end) {
  while (begin != end) {
    std::cout << *begin << " ";
    ++begin;
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

  std::cout << "before sort" << std::endl;
  print(vec.begin(), vec.end());
  std::sort(vec.begin(), vec.end()); // sort 함수에 들어가는 Iterator는 RandomAccessIterator를 만족해야합니다. (BidirectionalIterator는 사용 불가능합니다.)
  // 따라서, vector, deque만 사용이 가능합니다.
  // std::sort는 기본적으로 오름차순으로 정렬을 해줍니다.
  std::cout << "after sort" << std::endl;
  print(vec.begin(),  vec.end());

  // std::sort(vec.begin(), vec.end(), comp_function); // 비교 함수 객체를 전달해서 순서를 반대로 할 수 있음, 근데 너무 불편함
  std::sort(vec.begin(), vec.end(), std::greater<int>()); // 기본적으로 less이며, greater을 줘야만 내림차순으로 가능
  print(vec.begin(),  vec.end());

  return 0;
}