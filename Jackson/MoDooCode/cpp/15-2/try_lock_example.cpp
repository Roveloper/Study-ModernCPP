#include <iostream>
#include <mutex>
#include <thread>

void worker1(std::mutex& m1, std::mutex& m2) { // 우선권이 높은 worker는 신경쓸 게 없음
  for (int i = 0; i < 10000; ++i) {
    std::lock_guard<std::mutex> lock1(m1);
    std::lock_guard<std::mutex> lock2(m2);
    printf("worker1 is working\n");
  }
}
void worker2(std::mutex& m1, std::mutex& m2) {
  for (int i = 0; i < 10000; ++i) {
    while (true) {
      m2.lock();

      if (not m1.try_lock()) { // try_lock() 시도 시, lock을 성공하면 true, 실패하면 false가 return
        m2.unlock(); // m1을 취득하는데 실패했으므로, m2도 포기
        continue; // 다시 시도
      }

      printf("worker2 is working\n");
      m1.unlock();
      m2.unlock();
      break;
    }

  }
}

int main() {
  int counter = 0;
  std::mutex m1, m2;

  std::thread t1(worker1, std::ref(m1), std::ref(m2));
  std::thread t2(worker2, std::ref(m1), std::ref(m2));

  t1.join();
  t2.join();

  std::cout << "END" << std::endl;
}