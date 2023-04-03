#include <functional>
#include <iostream>
#include <string>

int some_func1(const std::string& a) {
  std::cout << "Func1 호출 " << a << std::endl;
  return 0; 
}

struct S {
  void operator()(char c) {
    std::cout << "Func2 호출 " << c << std::endl;
  }
};

int main() {
  std::function<int(const std::string&)> f1 = some_func1; // 출력타입(입력 타입) 형태의 Template으로 사용할 수 있습니다.
  std::function<void(char)> f2 = S();
  std::function<void()> f3 = [](){ std::cout << "Func3 호출" << std::endl; };

  f1("hello");
  f2('c');
  f3();
}