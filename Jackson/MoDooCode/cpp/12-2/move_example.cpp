#include <iostream>
#include <utility>

class A {
 public:
  A() { std::cout << "일반 생성자 호출!" << std::endl; }
  A(const A& a) { std::cout << "복사 생성자 호출!" << std::endl; }
  A(A&& a) { std::cout << "이동 생성자 호출!" << std::endl; }
};

int main() {
  A a;

  std::cout << "---------" << std::endl;
  A b(a);

  std::cout << "---------" << std::endl;
  A c(std::move(a)); // std::move는 입력으로 받은 객체를 rvalue로 변환하는 역할을 수행 (사실 move를 하기 위함인 것이지, move를 수행하는 것이 아니므로, 이름이 사실 별로 좋지 않았다고 함)
}