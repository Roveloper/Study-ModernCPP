#include <iostream>
#include <string>
using namespace std::literals;

int main() {
  auto s1 = "hello"s;
  std::cout << "s1 length = " << s1.size() << std::endl;

  std::string str = "hello";
  std::wstring wstr = L"hello";

  std::string raw_str = R"(asdfasdf
  안녕하세요, 여기 안에는 아무거나 와도 됩니다.
  // 이런 주석도 가능하구요?
  #define hasajskldfjaklse
  \n\n hello \t 등도 가능합니다.)"; // R"()" 이 안에다가 입력하면 문자 그대로 char배열로 들어감 (but, ()는 넣을 수 없음)

  std::string raw_str2 = R"foo()"; <-- 무시됨)foo"; // R"foo()foo" 사이에 입력하면 ()도 넣을 수 있음 (foo 대신 다른 구분자 이름 사용 가능)

  std::cout << raw_str << std::endl; 
  std::cout << raw_str2 << std::endl;
}