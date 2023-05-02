#include <future>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using std::string;
using namespace std::chrono_literals;

void worker(std::promise<string>* p) {
  std::this_thread::sleep_for(1s);
  p->set_value("some_data"); // promise의 값인 string을 set_value를 통해서 설정
}

int main() {
  std::promise<string> p; // string type의 promise 생성 (최종 결과값에 대한 type지정)

  std::future<string> data = p.get_future(); // 약속된 값을 받을 data 생성 (get_future()를 통해 미래의 값을 받아온다.)
  // promise의 값을 받을 수 있는 타입은 std::future<T>

  std::thread t(worker, &p); // 실제 수행 부분

  // data.wait(); // 약속 이행이 완료될 때 까지 대기, 당연히 이행이 되지 않으면, 무한 대기에 빠질 수 있음

  std::cout << "received data : " << data.get() << std::endl; // wait을 하지 않아도, get을 호출하면 전달될 때까지 기다렸다가 가져오므로 사실 wait가 꼭 있어야할 필요는 없음
  // data.get()을 사용 시, 데이터가 이동되므로, 한번 더 호출하면 죽음, 아래와 같이 한번 더 호출하면 seg fault 발생
  // std::cout << "received data : " << data.get() << std::endl; // wait을 하지 않아도, get을 호출하면 전달될 때까지 기다렸다가 가져오므로 사실 wait가 꼭 있어야할 필요는 없음


  t.join();
}