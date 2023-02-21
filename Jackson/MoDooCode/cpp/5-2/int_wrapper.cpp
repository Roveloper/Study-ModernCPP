#include <iostream>

// Wrapper --> 포장한다는 의미
// 기본 자료형을 객체로서 다루어야 할 때 사용 (기본 자료형을 다른 클래스로 포장해서 사용하는 것을 Wrapper 클래스라고 한다.)

class Int
{
  int data;

  public:
    Int(int data) : data(data) {}
    Int(const Int& i) : data(i.data) {}
    operator int() { return data; } // Int형 Wrapper 클래스를 int형으로 변환하는 연산자. a+b --> a.operator+(b), int(a) --> operator int(a) (a는 생략되고 자연스럽게 operator int()를 호출한다.)
    Int& operator++() { // ++i
      ++data;
      std::cout << "전위 증감 연산자!" << std::endl;
      return *this; } // 전위 증감 연산자
    Int operator++(int) {  // i++
      Int temp(*this); 
      ++data; 
      std::cout << "후위 증감 연산자!" << std::endl;
      return temp; } // 후위 증감 연산자
}; // Int형 Wrapper 클래스

// 실컷 만들어놨더니, int형 변수를 Int로 바꿔서 사용하는 것은 좋은데, 기존과 동일하게 동작하고 싶은데 그럴 수가 없다.
// Compiler에게 Int 타입을 처리할 때, 자동으로 int로 변환해서 사용하도록 명령을 내려야 한다.
// 그럴 때 사용하는 것이 타입 변환 연산자이다. operator (변환 타입) () { ... }

// 다음은 전위, 후위 증감 연산자 입니다. a++, ++a이냐....
// 근데 따지고보면, a++ --> a.operator++(), ++a --> operator++(a) 이므로 둘다 operator++입니다? 흠... 그러면 이걸 어케 구분할까요?
// operator++(), operator--() --> 전위 증감 연산자를 overloading
// operator++(int a), operator--(int a) --> 후위 증감 연산자를 overloading
// ?????? 뭐지? ++a --> operator++(a)니까, operator++(int a)이고, 이게 후위 증감 연산자 아님?
// 반대로 적용되는 것 같네 흠... 헷갈리네



int main() {
  Int x = 3;
  int a = x + 4;

  x = a * 2 + x + 4;
  std::cout << x << std::endl;

  std::cout << ++x << std::endl;
  std::cout << x++ << std::endl;

  return 0;
}