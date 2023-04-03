#include <functional>
#include <iostream>

struct S {
  int data;
  S(int data) : data(data) { std::cout << "일반 생성자 호출" << std::endl;}
  S(const S& s) {
    std::cout << "복사 생성자 호출" << std::endl;
    data = s.data;
  }

  S(S&& s) {
    std::cout << "이동 생성자 호출" << std::endl;
    data = s.data;
  }
};

void do_something(S& s1, const S& s2) { s1.data = s2.data + 3; }

int main() {
  S s1(1), s2(2);
  std::cout << "Before : " << s1.data << std::endl;

  auto do_something_with_s1 = std::bind(do_something, s1, std::placeholders::_1); // s1이 아닌, s1의 복사본이 전달됨
  // 왜냐하면 bind함수 자체로 s1의 복사본이 전달이 되어버리기 때문!

  auto do_something_with_s1_ref = std::bind(do_something, std::ref(s1), std::placeholders::_1); 
  // std::ref는 입력받은 값을 복사 가능한 레퍼런스로 변환해줌! const는 cref를 사용
  // std::ref는 입력받은 값의 reference를 감싸는 reference_wrapper 타입을 return함!
  do_something_with_s1(s2);

  std::cout << "After : " << s1.data << std::endl;
}