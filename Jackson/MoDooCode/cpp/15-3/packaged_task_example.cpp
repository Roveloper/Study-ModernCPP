#include <future>
#include <iostream>
#include <thread>

int some_task(int x) {
  return 10 * x;
}
int main() {
  std::packaged_task<int(int)> task(some_task); // 수행할 함수를 인자로 받고, 그 입력과 출력을 템플릿 인자로 받음
  // packaged_task가 수행되면 해당 결과값이 promise에 설정됨 (get()으로 받아올 수 있음)

  std::future<int> start = task.get_future();

  std::thread t(std::move(task), 5); // packaged_task는 복사생성이 불가능하므로, std::move로 넘겨줘야함, promise도 마찬가지로 복사 불가능

  std::cout << "result = " << start.get() << std::endl;

  t.join();
}