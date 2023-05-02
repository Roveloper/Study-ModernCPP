#include <future>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <exception>

void worker(std::promise<void> *p) {
  std::this_thread::sleep_for(std::chrono::seconds(10));
  p->set_value();
}

int main() {
  std::promise<void> p;

  std::future<void> data = p.get_future();

  std::thread t(worker, &p);

  while(true) {
    std::future_status status = data.wait_for(std::chrono::seconds(1)); // status는 timeoue, ready, deferred 세가지가 존재, timeout은 시간 초과, ready는 값 전달할 준비 됨, deferred는 결과값을 계산하는 함수가 실행되지 않았음을 의미 (아직 모름)

    if (status == std::future_status::timeout) {
      std::cerr << ">";
    }
    else if (status == std::future_status::ready) {
      break;
    }
  }
  t.join();
}