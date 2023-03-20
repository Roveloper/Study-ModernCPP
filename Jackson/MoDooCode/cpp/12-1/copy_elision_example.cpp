#include <iostream>

class A {
  int data_;

  public:
    A(int data) : data_(data) { std::cout << "일반 생성자" << std::endl; }
    A(const A& a) : data_(a.data_) { std::cout << "복사 생성자" << std::endl; }
};

int main() {
  A a(1); // 일반 생성자 호출
  A b(a); // 복사 생성자 호출

  A c(A(2)); // A(2)에서 일반 생성자가 호출, c(A(2))에서 복사 생성자가 호출되어야 맞음, -fno-elide-constructors 옵션을 줘서 컴파일하면 이러한 결과가 나옴
  // 컴파일러가 알아서 최적화를 시켜버려서 A c(2)로 만들어버림, 이를 copy-elision (복사 생략) 이라고 함
}
