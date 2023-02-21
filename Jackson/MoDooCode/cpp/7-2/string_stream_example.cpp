#include <iostream>
#include <sstream>

double to_number(std::string s) {
  std::istringstream ss(s);
  double x;
  
  ss >> x;
  return x;
}

int main() {
  std::istringstream ss("123"); // 문자열을 하나의 Stream으로 만들어주는 가상화 장치
  // 이걸 잘 활용하면 atoi 이런거 안쓰고도 간편하게 문자열에서 숫자로 변환할 수 있음!
  int x;
  ss >> x;

  std::cout << "입력 받은 데이터 :: " << x << std::endl;

  std::cout << "변환:: 1 + 2 = " << to_number("1")  + to_number("2") << std::endl;

  return 0;
}