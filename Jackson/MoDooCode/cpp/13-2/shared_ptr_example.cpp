#include <iostream>
#include <memory>
#include <vector>

// unique_ptr과 다르게, 객체에 대한 소유권을 여러 명이 나눠서 가지고 싶은 경우?
// shared_ptr을 사용하면 됨 (unique_ptr과 다르게 복사 생성자가 존재함)
// shared_ptr의 경우 복사 생성자를 통해, 동일한 객체를 생성하는 방식이 아니라, 동일한 포인터를 가리키게 함과 동시에 내부 참조 counter를 증가 시키는 방식으로 동작
// 해당 reference count가 0이 되면, 해당 객체를 소멸시킴

class A {
  int * data;

  public:
  A() {
    std::cout << "get resource" << std::endl;
    data = new int[100];
  }

  void some() {
    std::cout << "일반 포인터와 동일하게 사용 가능" << std::endl;
  }

  ~A() {
    std::cout << "call destructor" << std::endl;
    delete[] data;
  }
};

int main() {
  std::vector<std::shared_ptr<A>> vec;

  vec.push_back(std::make_shared<A>());
  vec.push_back(vec[0]);
  vec.push_back(vec[1]); // unique_ptr은 이렇게 하면 바로 컴파일 오류 발생함 (복사 생성자가 없음)

  std::cout << "count = " << vec[0].use_count() << std::endl;

  std::cout << "remove first element" << std::endl;
  vec.erase(vec.begin());
  std::cout << "count = " << vec[0].use_count() << std::endl;

  std::cout << "remove next element" << std::endl;
  vec.erase(vec.begin());
  std::cout << "count = " << vec[0].use_count() << std::endl;

  std::cout << "remove last element" << std::endl;
  vec.erase(vec.begin());

  // 제어 블록을 하나 놓고, 그 제어 블록을 가리키는 포인터를 각 객체가 가지고 있는 방식을 이용하여, 객체의 소멸을 제어함 (reference count)

  std::cout << "program ends" << std::endl;
}
