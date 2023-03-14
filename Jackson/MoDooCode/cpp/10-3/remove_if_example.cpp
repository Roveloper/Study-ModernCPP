#include <algorithm>
#include <functional>
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
struct is_odd {
  bool operator()(const int& i) {return i % 2 == 1;}
};

int main() {
  std::vector<int> v = {5, 3, 1, 2, 3, 4};

  print(v.begin(), v.end());

  std::cout << "after remove if" << std::endl;
  auto result = std::remove_if(v.begin(), v.end(), is_odd()); // is_odd가 true가 아닌 애들을 앞으로 당겨옴, 마찬가지로 당겨오기만 할 뿐 지워주진 않음
  print(v.begin(), v.end());
  std::cout << "after erase" << std::endl;
  v.erase(result, v.end());
  // v.erase(std::remove_if(v.begin(), v.end(), is_odd()), v.end()); // 이와 같이 한줄 처리 가능
  print(v.begin(), v.end());
}