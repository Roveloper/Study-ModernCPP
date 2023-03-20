int a = 3; 
// a는 메모리 상에 존재하며, &연산자를 통해 주소값을 확인할 수 있습니다. (이를 lvalue라고 합니다.)
// 어떠한 표현식의 왼쪽, 오른쪽에 모두 올 수 있습니다.

// 반대로 3은 메모리 상에 잠깐만 존재하고 사라지는 존재입니다. &연산자를 통해 주소를 확인할 수도 없습니다. (이를 rvalue라고 합니다.)
// lvalue와 다르게 rvalue는 왼쪽에는 올 수 없습니다, 오른쪽에만 올 수 있습니다.

int& l_a = a; // lvalue reference
// int& r_b = 3; // 3은 rvalue이므로 lvalue reference로 표현할 수 없으며, 오류가 발생합니다.

#include <iostream>

int& func1(int& a) { return a; }
int func2(int b) { return b; }
int func3(const int& c) { return c; }

int main() {
  int a = 3;
  func1(a) = 4; // 입력으로 들어간 a를 reference로 다시 return하므로, a의 값이 4로 바뀜
  std::cout << &func1(a) << std::endl; // func1(a)는 a의 reference를 return하고, 해당 값에 &연산자를 취했으므로, a의 주소값이 출력됨.

  int b = 2;
  a = func2(b); // b를 입력으로 넣고, b의 값을 return하므로, a = 2가 됨
  // func2(b) = 5; // func2는 reference를 return하는 것이 아닌, 임시 값을 return (rvalue)하므로, func2(b)의 값이 rvalue이므로, 왼쪽에 올 수 없음, 오류 발생
  // std::cout << &func2(b) << std::endl; // 마찬가지로 func2(b)는 임시 값인 rvalue를 return하므로, &연산자를 취할 수 없음, 오류 발생
  
  // 이와 같지만, 입력을 reference로 받는 func3에 대해서, rvalue를 입력으로 넣으면?
  // func1(10 + 5); // 10 + 5는 rvalue이므로 func1의 입력으로 들어갈 수는 없음, 오류 발생
  int c = func3(10 + 5); // 10 + 5는 분명 rvalue이므로 func3의 입력으로 들어갈 수 없을 것 같지만, const T& 타입에 대해서는 rvalue를 사용할 수 있음! (객체를 변경하지 않고, 참조만 하기 때문!)
  // std::cout << &func3(10 + 5) << std::endl; // 하지만, return 값은 int 타입이므로 당연히 이건 안됨
}