#include <iostream>
#include <thread>
#include <vector>
using std::vector;
using std::thread;

void worker(int& counter) {
  for (int i = 0; i < 10000; ++i) {
    // printf("worker is working %d\n", counter);
    counter += 1;
  }
}

int main() {
  int counter = 0;

  vector<thread> workers;
  int worker_count = 10;
  for (int i = 0; i < worker_count; ++i) {
    workers.push_back(thread(worker, std::ref(counter)));
  }

  for (int i = 0; i < worker_count; ++i) {
      workers[i].join();
  }
    std::cout << "Counter last value = " << counter << std::endl;
}