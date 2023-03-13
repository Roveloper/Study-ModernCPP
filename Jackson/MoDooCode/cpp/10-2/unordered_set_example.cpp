#include <iostream>
#include <string>
#include <unordered_set>

template <typename K>
void print_unordered_set(std::unordered_set<K>& s) {
  for (const auto& val : s) {
    std::cout << val << " ";
  }
  std::cout << std::endl;
}

int main() {
  std::unordered_set<std::string> s; // 당연히 장점으로는 속도가 빠릅니다 (정렬할 필요가 없으므로, hash만을 이용하여 데이터를 저장하므로 O(1)로 수행 가능)
  // hash함수를 잘못 설계하면 같은 hash가 많이 튀어나와서 속도가 오히려 느려질 수 있으므로, 속도가 필요한 경우에 set이나 map 대신 사용해볼 수는 있음
  s.insert("hi");
  s.insert("my");
  s.insert("name");
  s.insert("is");
  s.insert("jackson");

  print_unordered_set(s);

  if (s.find("hi") != s.end()) {
    std::cout << "hi가 존재합니다. 삭제하겠습니다." << std::endl;
    s.erase(s.find("hi"));
  } else {
    std::cout << "hi가 존재하지 않습니다" << std::endl;
  }

  if (s.find("hi") != s.end()) {
    std::cout << "hi가 존재합니다. 삭제하겠습니다." << std::endl;
    s.erase(s.find("hi"));
  } else {
    std::cout << "hi가 존재하지 않습니다" << std::endl;
  }
}