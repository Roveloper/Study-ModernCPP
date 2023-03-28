#include <iostream>

class A {
  public:
    A(int a) {};
    A(const A& a) = delete; // 명시적으로 복사 생성자를 삭제 (기본 존재하는 값도 사용하지 못하도록 만듦)
    // 특정한 함수를 사용하지 못하도록 만들고 싶을 때 사용, 사용하더라도 컴파일 에러 발생
    // 그러니까, unique_ptr은 복사 생성자를 delete 시켜서 복사 생성을 하지 못하도록 만든 것
};

int main() {
  A a(3);
  A b(a); // 삭제된 함수 호출
}