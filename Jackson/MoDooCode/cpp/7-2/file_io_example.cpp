#include <iostream>
#include <fstream>
#include <string>

int main() {
  std::ifstream in("test.txt"); // 생성자에서 자동으로 파일 열어줌, 소멸자에서 파일 알아서 닫아줌, but ifstream 객체를 그대로 쓰면서 새로운 파일을 열고 싶을 때는, close로 직접 닫아줘야함
  std::string s;

  if (in.is_open()) {
    in >> s;
    std::cout << "입력 받은 문자열 :: " << s << std::endl;
  } else {
    std::cout << "파일을 찾을 수 없습니다" << std::endl;
  }

  in.close();
  in.open("other.txt");

  if (in.is_open()) {
    in >> s;
    std::cout << "입력 받은 문자열 :: " << s << std::endl;
  } else {
    std::cout << "파일을 찾을 수 없습니다" << std::endl;
  }

  return 0;
}