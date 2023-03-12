#include <iostream>

template <typename T, int num = 5>
T add_num(T t) {
  return t + num;
}

template <typename T>
struct Compare {
  bool operator()(T& a, T& b) {
    return a < b;
  }
};

template <typename T, typename Comp = Compare<T>>
T min(T& a, T& b) {
  Comp comp;
  if (comp(a, b)) {
    return a;
  }
  return b;
}

int main() {
  int x = 3;
  std::cout <<  "x : " << add_num(x) << std::endl;

  int a = 3, b = 5;

  std::cout << "Min " << a << ", " << b << " :: " <<  min(a, b) << std::endl;

  std::string s1 = "abc", s2 = "def";
  std::cout << "Min " << s1 << ", " << s2 << " :: " << min(s1, s2) << std::endl;

  return 0;
}