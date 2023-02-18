#include <iostream>

class Base {
  public:
    Base() { std::cout << "기반 클래스" << std::endl; }
    virtual void what() {
        std::cout << "기반 클래스의 what?" << std::endl;
    } // virtual 키워드가 추가됨! 가상함수
};

class Derived : public Base {
  public:
    Derived() { std::cout << "파생 클래스" << std::endl; }
    void what() override { std::cout << "파생 클래스의 what" << std::endl; }
    // 가상함수 overriding 두 함수의 형태가 완벽하게 동일해야만 가능
    // override 키워드는 생략 가능하지만 안전을 위해 가상함수 override 시에는 적어주는 것이 좋음
};

int main() {
    Base p;
    Derived c;

    Base *p_c = &c;
    Base *p_p = &p;

    std::cout << "실제 객체는 Base" << std::endl;
    p_p->what();

    std::cout << "실제 객체는 Derived" << std::endl;
    p_c->what();

    return 0;
}
