#include <iostream>
#include <string>

// new를 이와 같은 방식으로 재정의하면, 모든 new 연산자를 오버로딩
// 특정 클래스의 멤버 함수로 정의하면, 해당 클래스의 new만 오버로딩 됨
void* operator new(std::size_t count) {
  std::cout << count << " bytes allocated" << std::endl;
  return malloc(count);
}
// basic_string의 내부를 변경하지 않고도, new 연산자를 오버로딩하여, 메모리 할당 여부를 확인할 수 있음

int main() {
  std::cout << "s1 create " << std::endl;
  std::string s1 = "this is a pretty long sentence!!!";
  std::cout << "s1 size = " << sizeof(s1) << std::endl;

  std::cout << "s2 create " << std::endl;
  std::string s2 = "short sentence";
  std::cout << "s2 size = " << sizeof(s2) << std::endl;
  // 짧은 문자열에서는 메모리 할당이 일어나지 않고, 객체 그 자체에 저장이 되어버림 (short string optimization)
  // 이를 통해서, 메모리 할당이라는 오래 걸리는 시간을 절약할 수 있음
}