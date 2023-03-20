#include <iostream>
#include <string>

int foo() noexcept {}; // noexcept는 해당 함수가 예외를 발생시키지 않는다는 것을 명시하는 것

int bar(int x) noexcept { throw 1; } // noexcept가 붙어있는 함수 내부에서 예외를 발생시키면, 프로그램이 종료됨
// 안던진다고 하고 던지면 안됨ㅋ
// 그러면 그냥 안적으면 안되나요?? 안적어도 되지만 그러면 컴파일러가 수행하는 최적화의 일부를 사용할 수 없다고 생각하면 됨
// But, google guide 부분을 보면 google에서는 예외처리 같은걸 사용하지 않음ㅋ
// https://google.github.io/styleguide/cppguide.html#Exceptions
// http://jongwook.kim/google-styleguide/trunk/cppguide.xml#%EC%98%88%EC%99%B8

int main() {
  foo();
  try {
    bar(1);
  } catch (int e) {
    std::cout << "Catch int : " << e << std::endl;
  }
}