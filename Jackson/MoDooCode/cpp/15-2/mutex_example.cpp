#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
using std::vector;
using std::thread;

void worker(int& counter, std::mutex& m) {
  for (int i = 0; i < 10000; ++i) {
    // printf("worker is working %d\n", counter);
    // m.lock();
    // counter += 1;
    // m.unlock(); // unlock 하지않으면, 계속 가지고 있으며, Deadlock이 발생할 수 있음
    // 대신 RAII 패턴을 적용해서 사용할 수 있는 std::lock_guard<std::mutex> lock(m) 을 사용할 수 있음
    
    std::lock_guard<std::mutex> lock(m);
    counter += 1;
    // 해당 함수가 종료되면서 생성되었던 lock_guard가 소멸되며, unlock됨
  }
}

int main() {
  int counter = 0;
  std::mutex m;

  vector<thread> workers;
  int worker_count = 10;
  for (int i = 0; i < worker_count; ++i) {
    workers.push_back(thread(worker, std::ref(counter), std::ref(m)));
  }

  for (int i = 0; i < worker_count; ++i) {
      workers[i].join();
  }
    std::cout << "Counter last value = " << counter << std::endl;
}