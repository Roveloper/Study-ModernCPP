#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using std::vector;

int main() {
  vector<int> a(1);
  vector<int> b(2);
  vector<int> c(3);
  vector<int> d(4);

  vector<vector<int>> container;
  container.push_back(b);
  container.push_back(d);
  container.push_back(a);
  container.push_back(c);

  vector<int> size_vec(4);
  std::function<size_t(const vector<int>&)> sz_func = &vector<int>::size;
  // std::transform(container.begin(), container.end(), size_vec.begin(), &vector<int>::size); // 이렇게는 사용할 수 없음
  // std::transform(container.begin(), container.end(), size_vec.begin(), sz_func); // 요렇게 멤버함수를 std::function으로 만들어서 전달하거나
  // std::transform(container.begin(), container.end(), size_vec.begin(), std::mem_fn(&vector<int>::size)); // 이렇게 그냥 멤버 함수를 불러다가 사용할 수 있음!
  std::transform(container.begin(), container.end(), size_vec.begin(), [](const auto& v) {return v.size();}); // 이렇게 그냥 받아서 사용하는 형태도 가능
  for (auto itr = size_vec.begin(); itr != size_vec.end(); ++itr) {
    std::cout << "vector size = " << *itr << std::endl;
  }
}