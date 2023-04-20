#include <iostream>
#include <mutex>
#include <thread>

void worker1(std::mutex& m1, std::mutex& m2) {
  for (int i = 0; i < 10000; ++i) {
    std::lock_guard<std::mutex> lock1(m1);
    std::lock_guard<std::mutex> lock2(m2);
    printf("worker1 is working\n");
  }
}
void worker2(std::mutex& m1, std::mutex& m2) {
  for (int i = 0; i < 10000; ++i) {
    std::lock_guard<std::mutex> lock2(m2);
    std::lock_guard<std::mutex> lock1(m1);
    printf("worker2 is working\n");
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