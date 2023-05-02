#include <chrono>
#include <future>
#include <iostream>
#include <thread>
using std::thread;

void runner(std::shared_future<std::string> start) {
  auto result = start.get(); // shared_future는 여러명이 get을 해도 문제가 되지 않습니다.
  std::cout << result << "Start!" << std::endl;
}

int main() {
  std::promise<std::string> p;
  std::shared_future<std::string> start = p.get_future(); // promise는 따로 바꿀 필요 없이, shared_future로 값을 받게되면, get으로 받을 시, 복사로 전달되게 된다.
  // 여러 개의 thread에서 접근 시, 복사본으로 전달해줘야만 안전하게 접근해서 사용할 수 있음 (reference나 pointer 전달은 안전하지 않음)

  thread t1(runner, start);
  thread t2(runner, start);
  thread t3(runner, start);
  thread t4(runner, start);

  std::cerr << "Ready?.....";
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cerr << "Go!" << std::endl;

  p.set_value("Hello");

  t1.join();
  t2.join();
  t3.join();
  t4.join();
}