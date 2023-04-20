#include <chrono>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>
#include <thread>
#include <vector>
#include <functional>

void producer(std::queue<std::string>& downloaded_pages, std::mutex& m, int index, std::condition_variable_any& cv) {
  for (int i = 0; i < 5; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100 * index));
    std::string content = "website : " + std::to_string(i) + " from thread(" + std::to_string(index) + ")\n";

    std::lock_guard<std::mutex> lock(m);
    downloaded_pages.push(content);
    cv.notify_one();
  }
}

void consumer(std::queue<std::string>& downloaded_pages, std::mutex& m, int& num_processed, std::condition_variable_any& cv) {
  while(num_processed < 25) {
    m.lock();

    cv.wait(m, [&downloaded_pages, &num_processed]{ return !downloaded_pages.empty() || num_processed == 25; });
    // wait는 condition이 false이면 unlock하고 notify올 때까지 대기
    // condition이 true면 그대로 통과함

    if (num_processed == 25) {
      m.unlock();
      return;
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
  std::condition_variable_any cv;

  std::vector<std::thread> producers;
  int producer_num = 5;
  for (int i = 0; i < producer_num; ++i) {
    producers.push_back(std::thread(producer, std::ref(downloaded_pages), std::ref(m), i + 1, std::ref(cv)));
  }

  int num_processed = 0;
  std::vector<std::thread> consumers;
  int consumer_num = 3;
  for (int i = 0; i < consumer_num; ++i) {
    consumers.push_back(std::thread(consumer, std::ref(downloaded_pages), std::ref(m), std::ref(num_processed), std::ref(cv)));
  }

  for (int i = 0; i < producer_num; ++i) {
    producers[i].join();
  }

  cv.notify_all();

  for (int i = 0; i < consumer_num; ++i) {
    consumers[i].join();
  }
}