#include <chrono>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

void producer(std::queue<std::string>& downloaded_pages, std::mutex& m, int index) {
  for (int i = 0; i < 5; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100 * index));
    std::string content = "website : " + std::to_string(i) + " from thread(" + std::to_string(index) + ")\n";

    std::lock_guard<std::mutex> lock(m);
    downloaded_pages.push(content);
  }
}

void consumer(std::queue<std::string>& downloaded_pages, std::mutex& m, int& num_processed) {
  while(num_processed < 25) {
    m.lock();

    if (downloaded_pages.empty()) { // consumer 입장에서는 일이 있는지 없는지 계속 체크해야하므로, 별로 효율적이지 못할 수 있음
      m.unlock(); 
      // 당연히 여기서 unlock을 하지 않는다면, 계속 lock이 걸려있는 상태이므로, downloaded_pages에 값이 추가되는 일도, consumer의 다음 while loop도 도는 일이 없을 것

      std::this_thread::sleep_for(std::chrono::milliseconds(10));
      continue;
    }

    std::string content = downloaded_pages.front();
    downloaded_pages.pop();

    ++num_processed;
    m.unlock();

    std::cout << content;
    std::this_thread::sleep_for(std::chrono::milliseconds(80));

  }
}

int main() {
  std::queue<std::string> downloaded_pages;
  std::mutex m;

  std::vector<std::thread> producers;
  int producer_num = 5;
  for (int i = 0; i < producer_num; ++i) {
    producers.push_back(std::thread(producer, std::ref(downloaded_pages), std::ref(m), i + 1));
  }

  int num_processed = 0;
  std::vector<std::thread> consumers;
  int consumer_num = 3;
  for (int i = 0; i < consumer_num; ++i) {
    consumers.push_back(std::thread(consumer, std::ref(downloaded_pages), std::ref(m), std::ref(num_processed)));
  }

  for (int i = 0; i < producer_num; ++i) {
    producers[i].join();
  }
  for (int i = 0; i < consumer_num; ++i) {
    consumers[i].join();
  }
}