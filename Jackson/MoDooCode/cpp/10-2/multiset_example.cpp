// multimap과 multiset은 중복을 허용한다는 차이가 있음

#include <iostream>
#include <set>
#include <string>

template <typename K>
void print_set(const std::multiset<K>& s) {
  for (const auto& val : s) {
    std::cout << val << std::endl;
  }
}

int main() {
  std::multiset<std::string> s;

  s.insert("a");
  s.insert("a");
  s.insert("b");
  s.insert("b");
  s.insert("a");
  s.insert("a");
  s.insert("c");
  s.insert("c");
  s.insert("a");
  s.insert("a");

  print_set(s); // 정렬은 됨, but 중복은 허용함
}