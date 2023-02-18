#include <iostream>
#include <string>

class Base {
  std::string s;

public:
  Base() : s("기반") { std::cout << "기반 클래스" << std::endl; }

  void what() { std::cout << s << std::endl; }
};

class Derived : public Base { // Derived Class가 Base Class를 public 형식으로
                              // 상속을 받겠다는 뜻 (public형식???은 무엇?)
  std::string s;

public:
  Derived()
      : Base(),
        s("파생") { // 초기화 list를 통해서, Base Class의 생성자인 Base()를 먼저
                    // 호출한 후, Derived Class에 대한 내용을 진행한다,
                    // 명시적으로 호출하지 않을 경우, Default 생성자를 호출한
                    // 후, Derived Class에 대한 내용이 실행된다.
    std::cout << "파생 클래스" << std::endl;
    what(); // what은 Base가 가지고 있는 s를 사용한다 (즉 Base Class의 std::string s와 Derived Class의 std::string s는 다른 주소이며, 서로 다른 값을 가진다.)
  }
};

int main() {
  std::cout << " === 기반 클래스 생성 === " << std::endl;
  Base p;

  std::cout << " === 파생 클래스 생성 === " << std::endl;
  Derived c;
  
  return 0;
}