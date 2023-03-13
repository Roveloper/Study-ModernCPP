// multimap과 multiset은 중복을 허용한다는 차이가 있음

#include <iostream>
#include <map>
#include <string>

template <typename K, typename S>
void print_map(const std::multimap<K, S>& s) {
  for (const auto& val : s) {
    std::cout << val.first << " -> " << val.second << std::endl;
  }
}

int main() {
  std::multimap<int, std::string> s;

  s.insert(std::make_pair(1, "hello"));
  s.insert(std::make_pair(1, "hi"));
  s.insert(std::make_pair(1, "hi"));
  s.insert(std::make_pair(1, "hi"));
  s.insert(std::make_pair(1, "hi"));
  s.insert(std::make_pair(1, "hi"));
  s.insert(std::make_pair(2, "ahihi"));
  s.insert(std::pair<int, std::string>(3, "byebye"));
  // s[2] = "bye"; // 이런건 허용하지 않음
  s.insert(std::make_pair(3, "bab"));
  print_map(s); // 정렬은 됨, but 중복은 허용함

  std::cout << s.find(1)->second << std::endl; // 뭐가 나올까...? 이건 사실 랜덤임...

  auto range = s.equal_range(1);
  for (auto it = range.first; it != range.second; ++it) {
    std::cout << it->first << " -> " << it->second << std::endl;
  }
}