#include <iostream>
#include <string>

class Base {
protected:
  std::string parent_string;

public:
  Base() : parent_string("기반") { std::cout << "기반 클래스" << std::endl; }

  void what() { std::cout << parent_string << std::endl; }
};
class Derived : public Base { // 여기에 있는 public의 의미는 
                              // Public으로 상속 시에는 기반 클래스의 접근 지시자 (public, protected, private)가 그대로 동작
                              // Protected로 상속 시에는 기반 클래스의 public이 protected로, 나머지는 그대로 동작
                              // Private로 상속 시에는 기반 클래스의 public, protected가 모두 private로 동작합니다.
  std::string child_string;

public:
  Derived() : child_string("파생"), Base() {
    std::cout << "파생 클래스" << std::endl;

    // 그렇다면 현재 private 인 Base 의
    // parent_string 에 접근할 수 있을까?
    parent_string =
        "바꾸기"; // private로 선언된 부분은 상속을 받더라도 직접적으로 수정할
                  // 수 없다. 이를 위해 등장한 것이 Protected! (protected는
                  // public과 private의 중간으로, 상속 받은 클래스에서도 접근이
                  // 가능하다!)
  }

  void what() { std::cout << child_string << std::endl; }
};

int main() {
  std::cout << " === 기반 클래스 생성 === " << std::endl;
  Base p;

  std::cout << " === 파생 클래스 생성 === " << std::endl;
  Derived c;

  return 0;
}