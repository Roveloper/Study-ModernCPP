#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

std::condition_variable cv;
std::mutex m;
bool done = false;
std::string info;

void worker() {
  {
  std::lock_guard<std::mutex> lk(m);
  info = "some_data";
  done = true;
  }
  cv.notify_all();
}

int main() {
  std::thread t(worker);

  std::unique_lock<std::mutex> lk(m);
  cv.wait(lk, [] { return done; }); // done이 true가 아니면, lock을 풀고 대기, notify가 날아오면 다시 lock을 획득하고 넘어가기
  lk.unlock();

  std::cout << "received data = " << info << std::endl;

  t.join();
}