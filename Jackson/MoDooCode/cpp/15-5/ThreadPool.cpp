#include <chrono>
#include <condition_variable>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <functional>

class ThreadPool {
  size_t num_threads_;
  std::vector<std::thread> worker_threads_;
  std::queue<std::function<void()>> jobs_;
  std::condition_variable cv_job_q_;
  std::mutex m_job_q_;
  bool stop_all;

  public:
  ThreadPool(size_t num_threads) : num_threads_(num_threads), stop_all(false)
  {
    worker_threads_.reserve(num_threads_);
    for (size_t i = 0; i < num_threads_; ++i) {
      worker_threads_.emplace_back([this]() { this->WorkerThread(); });
    }
  }

  void WorkerThread() {
    while (true) {
      std::unique_lock<std::mutex> lk(m_job_q_);
      cv_job_q_.wait(lk, [this]() { return not jobs_.empty() || stop_all; });
      if (stop_all && this->jobs_.empty()) {
        return;
      }

      auto job = std::move(jobs_.front());
      jobs_.pop();
      lk.unlock();

      job();
    }
  }
  void EnqueueJob(std::function<void()> job) {
    if (stop_all) {
      throw std::runtime_error("ThreadPool Stop Using");
    }
    {
    std::lock_guard<std::mutex> lk(m_job_q_);
    jobs_.push(std::move(job));
    }
    cv_job_q_.notify_one();
  }
  ~ThreadPool() {
    stop_all = true;
    cv_job_q_.notify_all();

    for (auto& t : worker_threads_) {
      t.join();
    }
  }
};

void work(int t, int id) {
  printf("%d start \n", id);
  std::this_thread::sleep_for(std::chrono::seconds(t));
  printf("%d end after %ds\n", id, t);
}

int main() {
  ThreadPool pool(3);

  for (int i = 0; i < 10; ++i) {
    pool.EnqueueJob([i]() { work(i % 3 + 1, i);});
  }
}
