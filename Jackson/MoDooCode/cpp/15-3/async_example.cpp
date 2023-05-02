#include <future>
#include <iostream>
#include <thread>
#include <vector>

int sum(const std::vector<int>& v, int start, int end) {
  int total = 0;
  for (int i = start; i < end; ++i) {
    total += v[i];
  }
  return total;
}

int parallel_sum(const std::vector<int>& v) {
  std::future<int> lower_half_future = std::async(std::launch::async, sum, cref(v), 0, v.size() / 2);
  // std::async([&v]() {return sum(v, 0, v.size() / 2); }); // 위는 launch policy를 지정하는 방식, 이거는 그냥 lambda 함수를 통해 실행하는 방식
  // launch policy는 async, deferred로 줄 수 있으며, 
  // async는 그 즉시 thread 생성 후, 함수를 실행하는 방식
  // deffered는 future의 get을 하였을 때, 실행되는 방식 (당장 실행이 필요없다면 deffered를 권장)
  
  int upper_half = sum(v, v.size() / 2, v.size());

  return lower_half_future.get() + upper_half;
}

int main() {
  std::vector<int> v;
  v.reserve(1000);

  for (int i = 0; i < 1000; ++i) {
    v.push_back(i + 1);
  }

  std::cout << "sum of 1 ~ 1000 = " << parallel_sum(v) << std::endl;
}