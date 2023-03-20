#include <exception>
#include <iostream>

class Parent : public std::exception {
 public:
  virtual const char* what() const noexcept override { return "Parent!\n"; }
};

class Child : public Parent {
 public:
  const char* what() const noexcept override { return "Child!\n"; }
};

int func(int c) {
  if (c == 1) {
    throw Parent();
  } else if (c == 2) {
    throw Child();
  }
  return 0;
}

int main() {
  int c;
  std::cin >> c;

  // try {
  //   func(c);
  // } catch (Parent& p) { // Child Class가 날아와도, 해당 Class가 Parent에 상속되어 있으므로, 우선적으로 Parent가 동작해버림
  // // warning도 발생하며, 이에 따라 순서를 수정해주면 됨
  //   std::cout << "Parent Catch!" << std::endl;
  //   std::cout << p.what();
  // } catch (Child& c) {
  //   std::cout << "Child Catch!" << std::endl;
  //   std::cout << c.what();
  // }

    try {
    func(c);
  } catch (Child& c) { // Child는 해당 위치에 들어갈 수 있지만, Child는 Parent를 받을 수 없으므로 넘어감
    std::cout << "Child Catch!" << std::endl;
    std::cout << c.what();
  } catch (Parent& p) {
  // warning도 발생하며, 이에 따라 순서를 수정해주면 됨
    std::cout << "Parent Catch!" << std::endl;
    std::cout << p.what();
  } 
}