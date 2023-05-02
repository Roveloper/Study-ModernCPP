#include <exception>
#include <future>
#include <iostream>
#include <string>
#include <thread>

using std::string;

void worker(std::promise<string>* p) {
  try {
    throw std::runtime_error("Some Error!");
  } catch (...) {
    p->set_exception(std::current_exception()); // Set_exception에는 exception_ptr을 전달해야함
  }
}

int main() {
  std::promise<string> p;

  std::future<string> data = p.get_future();

  std::thread t(worker, &p);

  data.wait();

  try {
    data.get(); // get을 통해 받아왔을 때, exception이 존재하면 exception이 발생한 것처럼 처리되며, catch 구문으로 넘어감
  } catch (const std::exception& e) {
    std::cout << "Exception : " << e.what() << std::endl;
  }
  t.join();
}