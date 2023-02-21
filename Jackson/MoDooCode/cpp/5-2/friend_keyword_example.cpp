class A {
 private:
  void private_func() {}
  int private_num;

  // B 는 A 의 친구!
  friend class B;  // B 클래스에서는 A 클래스의 내부 변수에 접근이 가능, 외부 클래스

  // func 은 A 의 친구!
  friend void func(); // func 함수에서는 A 클래스 내부 변수에 접근이 가능, 외부 함수
};

class B {
 public:
  void b() {
    A a;

    // 비록 private 함수의 필드들이지만 친구이기 때문에 접근 가능하다.
    a.private_func();
    a.private_num = 2;
  }
}; // B에서는 따로 friend를 선언하지 않아도, A클래스에 접근이 가능하지만, 그렇다고 A클래스가 B에게 접근이 가능한 것은 아님

void func() {
  A a;

  // 비록 private 함수의 필드들이지만 위와 마찬가지로 친구이기 때문에 접근
  // 가능하다.
  a.private_func();
  a.private_num = 2;
}

int main() {}