# [rule of three / five / zero](https://en.cppreference.com/w/cpp/language/rule_of_three)
## Rule of three
- Class에 사용자 정의된 `Destructor`, `Copy Constructor`, `Copy Assignment Operator` 중 하나라도 필요하다면, 거의 확실히 3개 모두가 필요합니다.
- C++에서 `복사`와 `복사 대입`은 다양한 상황에서 활용됩니다. (값 전달, 값 반환, 컨테이너 조작 등)
- 위와 같은 상황에서, 이 특별한 멤버 함수들이 호출됩니다.
- 이 때, 사용자 정의된 내용이 없다면, 이 함수들은 컴파일러가 암시적으로 생성합니다.
- 이 암시적으로 생성된 특별한 멤버 함수들은 아래와 같은 경우에서는 일반적으로 정확하지 않습니다.
  - Class가 핸들이 클래스가 아닌 유형의 객체의 리소스를 관리할 때(raw pointer, POSIX file descriptor, etc)
  - `Destructor`가 아무것도 하지 않으며, `Constructor` 또는 `Copy Assignment Operator`가 얕은 복사를 수행할 때
```C++
#include <iostream>
#include <cstddef>
#include <cstring>
 
class rule_of_three
{
    char* cstring; // raw pointer used as a handle to a dynamically-allocated memory block
 
    rule_of_three(const char* s, std::size_t n) // to avoid counting twice
    : cstring(new char[n]) // allocate
    {
        std::memcpy(cstring, s, n); // populate
    }
public:
    rule_of_three(const char* s = "")
    : rule_of_three(s, std::strlen(s) + 1) {}
 
    ~rule_of_three() // I. destructor
    {
        delete[] cstring; // deallocate
    }
 
    rule_of_three(const rule_of_three& other) // II. copy constructor
    : rule_of_three(other.cstring) {}
 
    rule_of_three& operator=(const rule_of_three& other) // III. copy assignment
    {
        if (this == &other)
            return *this;
 
        std::size_t n{std::strlen(other.cstring) + 1};
        char* new_cstring = new char[n];            // allocate
        std::memcpy(new_cstring, other.cstring, n); // populate
        delete[] cstring;                           // deallocate
 
        cstring = new_cstring;
        return *this;
    }
 
    operator const char *() const // accessor
    {
        return cstring;
    }
};
 
int main()
{
    rule_of_three o1{"abc"};
    std::cout << o1 << ' ';
    auto o2{ o1 }; // I. uses copy constructor
    std::cout << o2 << ' ';
    rule_of_three o3("def");
    std::cout << o3 << ' ';
    o3 = o2; // III. uses copy assignment
    std::cout << o3 << ' ';
}   // <- II. all destructors are called 'here'
```
- 복사가 불가능한 자원을 복사가 가능한 핸들을 통해 관리하는 클래스는 복사 대입 연산자와 복사 생성자를 private으로 선언해야합니다. 그리고 그들의 정의를 제공하지 않거나, 삭제된 것으로 정의해야할 수도 있습니다. (왜냐면, Compiler가 알아서 처리를 해버리면 오류가 날 것이기 때문)
- 이는 또 다른 `rule of three`입니다. 하나만 지우고 나머지를 user-defined로 만들면, 일반적으로 오류가 발생할 것입니다.

## Rule of five
- 사용자 정의된 또는 기본 또는 삭제 정의된 소멸자, 복사 생성자, 복사 대입 연산자가 `이동 생성자`와 `이동 대입 연산자`의 암시적 생성을 막기 때문에, `이동 문법`이 필요한 클래스의 경우는 위 5개의 특별한 멤버 함수를 모두 정의해야 합니다. (기존 `소멸자`, `복사 생성자`, `복사 대입 연산자`에 추가로 `이동 생성자`, `이동 대입 연산자` 까지)
```c++
class rule_of_five
{
    char* cstring; // raw pointer used as a handle to a dynamically-allocated memory block
public:
    rule_of_five(const char* s = "") : cstring(nullptr)
    { 
        if (s)
        {
            std::size_t n = std::strlen(s) + 1;
            cstring = new char[n];      // allocate
            std::memcpy(cstring, s, n); // populate 
        } 
    }
 
    ~rule_of_five()
    {
        delete[] cstring; // deallocate
    }
 
    rule_of_five(const rule_of_five& other) // copy constructor
    : rule_of_five(other.cstring) {}
 
    rule_of_five(rule_of_five&& other) noexcept // move constructor
    : cstring(std::exchange(other.cstring, nullptr)) {}
 
    rule_of_five& operator=(const rule_of_five& other) // copy assignment
    {
        return *this = rule_of_five(other);
    }
 
    rule_of_five& operator=(rule_of_five&& other) noexcept // move assignment
    {
        std::swap(cstring, other.cstring);
        return *this;
    }
 
// alternatively, replace both assignment operators with 
//  rule_of_five& operator=(rule_of_five other) noexcept
//  {
//      std::swap(cstring, other.cstring);
//      return *this;
//  }
};
```
- `Rule of three`와 다르게 `이동 생성자`와 `이동 대입 연산자`를 제공하지 않는 것이 오류로 이어지지는 않습니다, 하지만 최적화할 수 있는 기회를 놓치게 됩니다.

## Rule of zero
- 사용자 정의의 `소멸자`, `복사, 이동 생성자`, `복사, 이동 대입 연산자`를 가지는 클래스들은 예외적으로 소유권을 다뤄야합니다. (`Single Responsibility Principle`)
- 그렇지 않다면, `소멸자`, `복사, 이동 생성자`, `복사, 이동 대입 연산자`를 가져서는 안됩니다.
```c++
class rule_of_zero
{
    std::string cppstring;
public:
    rule_of_zero(const std::string& arg) : cppstring(arg) {}
};
```
- Base 클래스가 다형성을 위한 사용을 위해 의도되었을 때, 이의 소멸자는 `public` 또는 `virtual`로 선언되어야합니다.
- 암시적으로 이동하며(암시적인 복사를 제거합니다) 그리고 특별한 멤버 함수들은 `default`로 선언되어야합니다.
```c++
class base_of_five_defaults
{
public:
    base_of_five_defaults(const base_of_five_defaults&) = default;
    base_of_five_defaults(base_of_five_defaults&&) = default;
    base_of_five_defaults& operator=(const base_of_five_defaults&) = default;
    base_of_five_defaults& operator=(base_of_five_defaults&&) = default;
    virtual ~base_of_five_defaults() = default;
};
```
- 그러나 이는 클래스가 슬라이싱 되기 쉬워지므로, 다형성 클래스는 종종 복사를 `deleted`로 정의합니다. (이는 `Rule of five`로 이어집니다.)
- [C.67](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c67-a-polymorphic-class-should-suppress-public-copymove)
- [C.21](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c21-if-you-define-or-delete-any-copy-move-or-destructor-function-define-or-delete-them-all)

## Single Responsibility Principle [SRP](https://inpa.tistory.com/entry/OOP-%F0%9F%92%A0-%EC%95%84%EC%A3%BC-%EC%89%BD%EA%B2%8C-%EC%9D%B4%ED%95%B4%ED%95%98%EB%8A%94-SRP-%EB%8B%A8%EC%9D%BC-%EC%B1%85%EC%9E%84-%EC%9B%90%EC%B9%99)
- 모듈은 하나의 책임만 가져야한다는 것을 의미합니다.
- 하나의 클래스는 하나의 관심사에만 집중해야하며, 그렇지 않으면 클래스를 분리해야합니다.
- `책임`이라는 것은 변경하려는 이유를 뜻합니다. (로버트 마틴)