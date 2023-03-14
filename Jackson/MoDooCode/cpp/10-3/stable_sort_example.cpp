#include <iostream>
#include <algorithm>
// #include <functional>
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

struct User {
  std::string name;
  int age;

  User(std::string name, int age) : name(name), age(age) {}

  bool operator<(const User& u) const { return age < u.age; }
  
  friend std::ostream& operator<<(std::ostream& o, const User& u);
};

std::ostream& operator<<(std::ostream& o, const User& u) {
  o << u.name << ", " << u.age;
  return o;
}

int main() {
  std::vector<User> vec;
  for (int i = 0; i < 100; ++i) {
    std::string name = "";
    name.push_back('a' + i / 26);
    name.push_back('a' + i % 26);
    vec.push_back(User(name, static_cast<int>(rand() % 10)));
  }

  std::vector<User> vec2 = vec;

  std::cout << "before sort" << std::endl;
  print(vec.begin(), vec.end());

  std::sort(vec.begin(), vec.end()); // std::sort는 최악의 경우에도 O(NlogN)을 보장

  std::cout << "after sort" << std::endl;
  print(vec.begin(), vec.end());

  std::cout << "Stable Sort" << std::endl;
  std::stable_sort(vec2.begin(), vec2.end()); // 기존 순서를 유지하면서 비교해서 정렬, std::stable_sort는 O(n(logn)^2)입니다.
  print(vec2.begin(), vec2.end());

  return 0;
}