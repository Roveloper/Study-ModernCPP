#include <iostream>
#include <string>

// 클래스 상속 시 작성하는 접근 지시자는 
// Public으로 상속 시에는 기반 클래스의 접근 지시자 (public, protected, private)가 그대로 동작
// Protected로 상속 시에는 기반 클래스의 public이 protected로, 나머지는 그대로 동작
// Private로 상속 시에는 기반 클래스의 public, protected가 모두 private로 동작합니다.

class Base {
  public:
  std::string parent_string;

  Base() : parent_string("기반") { std::cout << "기반 클래스" <<std::endl;}

  void what() { std::cout << parent_string << std::endl;}

};

class Derived : private Base {
  std::string child_string;

  public:
  Derived() : Base(), child_string("파생") {
    std::cout << "파생 클래스" << std::endl;
  }

  void what() { std::cout << child_string << std::endl;}

};

int main() {
  Base p; // Base에서는 현재 parent_string이 public이므로 접근 가능
  std::cout << p.parent_string << std::endl;

  Derived c; // Derived에서는 Base를 Private으로 상속했으므로, parent_string에 접근할 수 없다.
  std::cout << c.parent_string << std::endl; // 컴파일 오류 발생! 위의 내용을 Public으로 변환하면 사용 가능!
  
  return 0;
}