#include <iostream>
#include <stdexcept>

int func(int c) {
  if (c == 1) {
    throw 1;
  } else if (c == 2) {
    throw "hi";
  } else if (c == 3) {
    throw std::runtime_error("error");
  }
  return 0;
}

int main() {
  int c;
  std::cin >> c;
  // func(c); // 당연히 try-catch가 없는 부분에서 발생 시 프로그램이 그냥 종료됨

  try {
    func(c);
  } catch (int e) {
    std::cout << "Catch int : " << e << std::endl;
  } catch (...) { // ... 으로 받으면 아무거나 다 받을 수 있음 else같은 존재
    std::cout << "Default Catch!" << std::endl;
  }
}