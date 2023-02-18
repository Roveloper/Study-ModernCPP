#include <iostream>

class Animal {
 public:
  Animal() {}
  virtual ~Animal() {}
  virtual void speak() = 0; // = 0이 붙은 virtual 함수는 정의가 되어있지 않고, 무조건 이를 상속한 Class에서 overriding해야만 합니다. 이를 순수 가상 함수라고 부릅니다.
  // 이런 순수 가상함수를 포함하고 있는 객체의 경우 생성이 불가능하고, 당연히 함수 호출도 불가능합니다.
  // 이와 같이 순수 가상 함수를 하나라도 포함하고 있는 클래스를 Abstract Class라고 부릅니다. --> 설계도와 같은 역할
};

class Dog : public Animal {
 public:
  Dog() : Animal() {}
  void speak() override { std::cout << "왈왈" << std::endl; }
};

class Cat : public Animal {
 public:
  Cat() : Animal() {}
  void speak() override { std::cout << "야옹야옹" << std::endl; }
};

int main() {
  Animal* dog = new Dog();
  Animal* cat = new Cat();
  Animal& dog_ref = *dog;
  Animal& cat_ref = *cat;

  dog->speak();
  cat->speak();
  dog_ref.speak();
  cat_ref.speak();
}
