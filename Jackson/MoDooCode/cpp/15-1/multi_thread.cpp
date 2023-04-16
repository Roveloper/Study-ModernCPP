#include <iostream>
#include <thread>

void func1() {
  for (int i = 0; i < 10; ++i) {
    std::cout << "thread 1 activate! \n";
  }
}

void func2() {
  for (int i = 0; i < 10; ++i) {
    std::cout << "thread 2 activate! \n";
  }
}

void func3() {
  for (int i = 0; i < 10; ++i) {
    std::cout << "thread 3 activate! \n";
  }
}

int main() {
  std::thread t1(func1);
  std::thread t2(func2);
  std::thread t3(func3);

  t1.join();
  t2.join();
  t3.join(); // 실행 순서는 전적으로 운영체제가 스케줄링을 어떻게하냐에 따라 달려있음
  // 해당 부분을 제거하면, 각 thread가 일을 마치기 전에, thread의 소멸자가 먼저 호출되면서 오류가 발생함
}