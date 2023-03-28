#include <iostream>
#include <memory>
#include <vector>

class A {
  int *data;

  public:
  A() {
    std::cout << "get resource" << std::endl;
    data = new int[100];
  }

  void some() {std::cout << "일반 포인터와 동일하게 사용 가능" << std::endl;}

  ~A() {
    std::cout << "call destructor" << std::endl;
    delete[] data;
  }
};

int main() {
  std::vector<std::unique_ptr<A>> vec;
  std::unique_ptr<A> pa = std::make_unique<A>();

  // vec.push_back(pa); // push back은 기본적으로 복사를 수행하므로, error가 발생
  vec.push_back(std::move(pa)); // move를 통해 소유권을 이전하면, error가 발생하지 않음
  vec.emplace_back(std::make_unique<A>()); // emplace_back은 perfect forwarding을 수행하므로, error가 발생하지 않음
  
}