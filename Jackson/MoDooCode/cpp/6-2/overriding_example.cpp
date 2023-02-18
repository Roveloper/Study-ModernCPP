#include <iostream>
#include <string>

class Base {
    std::string s;

  public:
    Base() : s("기반") { std::cout << "기반 생성자" << std::endl; }
    void what() { std::cout << s << std::endl; }
};

class Derived : public Base {
    std::string s;

  public:
    Derived() : Base(), s("파생") { std::cout << "파생 생성자" << std::endl; }

    void what() { std::cout << s << std::endl; }
};

int main() {
    Base p;
    Derived c;

    std::cout << "포인터 버전" << std::endl;
    Base *p_c = &c; // 파생 클래스의 객체를 기반 클래스로 캐스팅하는 것을 업캐스팅이라고 합니다,
                    // 당연히 Derived Is-A Base 관계는 성립하지만, Base Is-A Derived의 관계는
                    // 성립하지 않기 때문에, 역은 불가능합니다.
                    // Derived *p_p = &p; // 컴파일 에러가 발생합니다.

    Derived *p_p = static_cast<Derived *>(
        p_c); // 암시적 변환은 불가능하지만, 명시적 변환은 가능합니다. 따라서 Derived *p_p = p_c; 는
              // 컴파일 오류가 발생하지만 static_cast를 통한 명시적 변환은 가능합니다. (이와 같은
              // 다운 캐스팅은 가능합니다.)
    p_c->what();
    p_p->what();

    Base *p_new = &p;
    Derived *p_d_new = static_cast<Derived *>(p_new);
    // Base Class의 포인터를 강제로 Derived Class의 포인터로 형변혼 시켰기 때문에, 이런 저런 오류가
    // 발생할 수 있지만, static_cast는 강제 형변환이므로, 컴파일 오류는 발생하지 않는다. (주의가
    // 필요합니다.) 이를 위해서 있는 것이 바로 dynamic_cast입니다
    // dynamic_cast는 상속 관계에 있는 두 포인터 간의 변환을 지원합니다.

    // Derived *p_dynamic_new = dynamic_cast<Derived *>(p_new); // 컴파일 오류가 발생합니다.

    p_d_new->what();

    return 0;
}