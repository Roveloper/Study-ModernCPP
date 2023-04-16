#include <iostream>
#include <thread>
using std::thread;

void func1() {
  for (int i = 0; i < 10; i++) {
    std::cout << "쓰레드 1 작동중! \n";
  }
}

void func2() {
  for (int i = 0; i < 10; i++) {
    std::cout << "쓰레드 2 작동중! \n";
  }
}

void func3() {
  for (int i = 0; i < 10; i++) {
    std::cout << "쓰레드 3 작동중! \n";
  }
}
int main() {
  thread t1(func1);
  thread t2(func2);
  thread t3(func3);

  t1.detach();
  t2.detach();
  t3.detach(); // 소멸이 안되게 하는 게 아니라, 소멸자가 호출되더라도 예외가 발생하지 않도록 하는 것
  // 백그라운드에서 돌아가며, 만약 소멸자가 호출되면 소멸됨

  std::cout << "메인 함수 종료 \n";
}