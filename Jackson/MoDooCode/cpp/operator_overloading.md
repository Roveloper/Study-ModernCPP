# [basic rules and idioms for operator overloading](https://stackoverflow.com/questions/4421706/what-are-the-basic-rules-and-idioms-for-operator-overloading)
# operator overloading
- C++에서 overloading할 수 없는 연산자는 `.`, `::`, `sizeof`, `?:`, `typeid`, `.*` 이다.
- 일반적으로 overloading할 수 있는 연산자는 다음과 같다.
  - 수학 연산자 (`+`, `-`, `*`, `/`, `%`, `+=`, `-=`, `*=`, `/=`, `%=`, `+`, `-`, `++`, `--`)
  - 비트 연산자 (`&`, `|`, `^`, `~`, `<<`, `>>`, `&=`, `|=`, `^=`, `<<=`, `>>=`)
  - 비교 연산자 (`==`, `!=`, `<`, `>`, `<=`, `>=`, `||`, `&&`, `!`)
  - 메모리 연산자 (`new`, `delete`, `new[]`, `delete[]`)
  - 암묵적 변환 연산자 (`operator T()`)
  - 기타 연산자 (`=`, `[]`, `->`, `->*`, `,`, `*`, `&`, `()`)
- 일반적으로 연산자 오버로딩의 경우는 왼쪽 타입의 멤버함수로 정의하거나, 외부 함수로 정의한다.
- 단항 연산자 @의 경우는 operator@(a) 또는 a.operator@()로 해석이 가능하며
- 이항 연산자 a@b는 두 가지로 해석이 가능한데, a.operator@(b) 또는 operator@(a, b)로 해석이 가능하다.
- 전자로 해석이 되었을 경우에는 멤버함수로 정의가 되었을 경우이며, 후자로 해석이 되었을 경우에는 외부 함수로 정의가 되었을 경우이다.
- 멤버함수가 아닌 외부 함수로 정의되었을 경우에는 `friend` 함수로 정의가 되었을 수도 있다.

# Three Basic Rules of Operator Overloading in C++
1. 연산자 오버로딩의 의미가 명확하지 않은 경우에는 오버로딩을 하지 않아야 한다.
  - 이와 같은 애매한 경우는 잘 정해진 이름의 함수를 사용하는 것이 좋다.
  - 수 많은 자료들이 있지만, 실제로 연산자 오버로딩이 필요한 경우는 얼마 없기 때문입니다.
  - 실제 도메인에 따라서, 정확한 내용을 파악하기 힘든 경우들도 존재하기 때문입니다.
2. 항상 연산자의 잘 알려진 문맥을 따르라 (의미를 따르라)
  - C++은 연산자 오버로딩에 대해 제한을 두지 않습니다.
  - 그러나, 연산자 오버로딩을 사용할 때에는 항상 연산자의 의미를 따라야 합니다.
3. 항상 관련된 연산자들을 함께 오버로딩하라
  - 사람들은 특정한 값만 사용하는 것이 아니라, +가 있다면, +=도 당연히 있을 것이라고 생각하므로, 모든 연산자를 모두 정의하길 바랍니다.
  - `>`가 있다면, 당연히 <=도 있을거라고 생각하는 것 처럼

# The Decision between Member and Non-Member Operator Overloading
- `=`, `[]`, `->`, `()`는 멤버함수로 정의해야합니다, 왜냐하면 언어의 문법이 그렇게 필요로 하기 때문입니다.
- 이 외의 연산자들은 멤버함수로 정의할 수도 있고, 외부 함수로 정의할 수도 있습니다.
- 하지만 일반적으로 외부 함수로 정의하는 경우도 있는데, 이는 왼쪽 피연산자가 변환이 불가능한 경우가 있기 때문입니다.
- 예를 들면, `<<`, `>>`의 경우, 왼쪽 피연산자가 stream class 이기 때문에 변환할 수 없습니다.
- 모든 연산자에 대해 멤버함수 또는 외부 함수로 정의해야 되는 경우가 있다면, rules of thumb를 따르는 것이 좋습니다.
  - 단항 연산자라면, 멤버함수로 정의하라.
  - 이항 연산자가 두 개의 피연산자를 같게 취급한다면(두 값의 변화도 없으며), 외부 함수로 정의하라
  - 이항 연산자가 두 개의 피연산자를 다르게 취급한다면(일반적으로 왼쪽 피연산자를 변화시키는 경우), 왼쪽 피연산자의 멤버함수로 정의하는 것이 유용합니다. (만약 피연산자의 private 멤버에 접근해야 한다면)
- 예외가 있다면 다음과 같습니다.
  ```c++
  enum Month {Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec};
  ```
  - 위와 같은 상황에서 증가, 감소 연산자를 정의하고 싶다면, 멤버함수로 정의할 수 없습니다. (`enum` 타입은 멤버함수를 가질 수 없기 때문입니다.)
  - 이와 달리 클래스 템플릿 내에 중첩된 클래스 템플릿에 대한 `operator<()`는 훨씬 더 읽고 쓰기 쉽습니다. (하지만 드문 예외 케이스입니다. ?? 뭔소린지 모르겠슴다)

# Common operators to overload
- Assignment Operator (대입 연산자)
  ```c++
  X& X::operator=(X rhs)
  {
    swap(rhs);
    return *this;
  }
  ```
- Bitshift Operators (비트 이동 연산자)
  ```c++
  std::ostream& operator<<(std::ostream& os, const T& obj)
  {
    // write obj to stream

    return os;
  }

  std::istream& operator>>(std::istream& is, T& obj)
  {
    // read obj from stream

    if( /* no valid object of T found in stream */ )
      is.setstate(std::ios::failbit);

    return is;
  }
  ```
  - 비트 이동 연산자는 꼭 외부 함수로 정의할 것
- 함수 호출 연산자
  - 함수 객체 생성시 사용 (functors)
  - 멤버 함수로 정의해야만 함
  - 또한 몇 개든 추가적인 입력 인자를 받을 수 있음 (0개도 가능)
  ```c++
  class foo {
    public:
      int operator()(const std::string& y) {

      }
  };

  foo f;
  int a = f("hello");
  ```
  - C++ STL에서, 함수 객체는 항상 복사됩니다.
  - 그러므로, 당신이 만든 함수 객체도 쉽게 복사가 가능해야합니다.
  - 만약 함수 객체가 복사하기 힘든 데이터를 사용해야 한다면, 데이터를 다른 곳에 저장하고, 함수 객체가 그 데이터를 참조하도록 만들어야 합니다.
- Comparison operators (비교 연산자)
  - std::sort() 또는 std::map 등을 위해서 비교연산자 operator<가 존재해야합니다.
  ```c++
  inline bool operator==(const X& lhs, const X& rhs){ /* do actual comparison */ }
  inline bool operator!=(const X& lhs, const X& rhs){return !operator==(lhs,rhs);}
  inline bool operator< (const X& lhs, const X& rhs){ /* do actual comparison */ }
  inline bool operator> (const X& lhs, const X& rhs){return  operator< (rhs,lhs);}
  inline bool operator<=(const X& lhs, const X& rhs){return !operator> (lhs,rhs);}
  inline bool operator>=(const X& lhs, const X& rhs){return !operator< (lhs,rhs);}
  ```
  - 여기서 확인할 것은 실제 동작하는 함수는 단 두개 뿐이라는 것입니다.
  - 나머지는 단순히 두 함수를 이용하여 전달해주는 역할을 할 뿐입니다.
- Arithmetic Operators (산술 연산자)
  - 단항 연산자
    - 단항 증감 연산자는 전위 및 후위에 올 수 있습니다.
    - 후위 연산자는 추가적인 더미 인자가 필요합니다.
    - 증감 연산자를 정의한다면, 꼭 전위 및 후위를 둘다 정의하길 바랍니다.
    ```c++
    class X {
      X& operator++()
      {
        // do actual increment
        return *this;
      }
      X operator++(int)
      {
        X tmp(*this);
        operator++();
        return tmp;
      }
    };
    ```
    - 후위 연산자는 전위 연산자를 이용하여 정의가 가능합니다.
    - 또한 후위 연산자는 추가적인 복사가 필요합니다. (느립니다.)
    - 단항 + 또는 단항 - 연산자는 일반적으로 구현하지 않습니다.
    - 필요하다면, 꼭 멤버 함수로 구현하기를 바랍니다.
- Binary arithmetic operators (이항 산술 연산자)
  - +가 있다면 +=을, -가 있다면 -=을 꼭 구현하길 바랍니다.
  - 복합 대입 연산자는 대응하는 연산자의 구현에 사용할 수 있습니다.
  ```c++
  class X {
    X& operator+=(const X& rhs)
    {
      // actual addition of rhs to *this
      return *this;
    }
  };
  inline X operator+(X lhs, const X& rhs)
  {
    lhs += rhs;
    return lhs;
  }
  ```
  - 참조자를 반환하는 것이 일반 복사를 통해 반환하는 것보다 효율적이지만, operator+는 그럴 수 없습니다.
  - 왜냐면 일반적으로 a + b를 게산할 때, 새로운 값이 나오길 바라기 때문입니다.
  - 또한 operator+가 왼쪽 값을 복사로 받아오는 것을 추천합니다. 이는 operator=가 복사로 인자를 받는 이유와 동일합니다. (그 이유가 뭔디요?)
  - a += b가 실제로 a + b를 계산하는 것보다 효율적입니다. (reference를 활용하기 때문)
- Array Subscripting (첨자 연산자)
  - 첨자 연산자는 클래스 멤버로 구현되어야하는 필수적인 이항연산자입니다.
  - container-like 타입에서 각 데이터에 접근할 수 있는 키가 됩니다.
  ```c++
  class X {
          value_type& operator[](index_type idx);
    const value_type& operator[](index_type idx) const;
    // ...
  };
  ```
  - 만약 당신이 유저가 operator[]를 통해 받은 데이터를 변경하지 않으려면, 위 두 가지를 꼭 모두 제공해야합니다. (변경하려면 const를 생략할 수 있음)
  - `value_type`이 기본 제공 타입을 참조한다면, const 버전의 operator는 const reference 대신 복사값을 반환해야합니다.
  ```c++
  class X {
    value_type& operator[](index_type idx);
    value_type  operator[](index_type idx) const;
    // ...
  };
  ```
- Operators for Pointer-like Types (포인터 연산자)
  - 자신의 iterator 타입 또는 smart pointer를 정의하기 위해서는 단항 전위 역참조 연산자인 (*)와 이항 고정 포인터 멤버 접근 연산자인 (->)를 구현해야합니다.
  ```c++
  class my_ptr {
          value_type& operator*();
    const value_type& operator*() const;
          value_type* operator->();
    const value_type* operator->() const;
  };
  ```
  - 일반적으로 const와 non-const 버전 두 가지 모두가 필요합니다.
  - `->` 연산자에 대해, `value_type`이 class, struct, union 타입이라면, 다른 operator->()를 재귀적으로 호출할 수 있습니다. (다른 operator->()이 클래스 타입이 아닌 값을 반환할 때 까지)
  - 단항 주소 연산자인 (&)는 오버로딩 되어서는 안됩니다.
  - `operator->*()`는 아주 드물게 사용되며, 아주 드물게 오버로딩 됩니다. 실제로 iterator 조차도 이를 오버로딩하지 않습니다. [참고](https://stackoverflow.com/questions/8777845/overloading-member-access-operators)
# Conversion Operators
- implicit and explicit conversion operator가 존재
- Implicit Conversion Operators (C++98, C++03, C++11)
  - 컴파일러가 암시적으로 변환할 수 있게 함 (사용자 정의 타입을 다른 타입으로)
  ```c++
  class my_string {
    public:
      operator const char*() const {return data_;} // This is the conversion operator
    private:
      const char* data_;
    };
  ```
  - 하나의 입력을 받는 생성자와 같이 암시적 변환 연산자는 사용자 정의 변환 연산자를 정의하는 데 사용할 수 있습니다.
  - 컴파일러는 오버로딩된 함수에 매칭 시키기 위해 암시적 변환을 사용할 수 있습니다.
  ```c++
  void f(const char*);

  my_string str;
  f(str); // same as f( str.operator const char*() )
  ```
  - 이는 매우 편해보이나, 암시적 변환은 가끔 예상치 못한 결과를 초래할 수 있습니다.
  - 아래와 같은 상황에서 my_string()이 l-value가 아니므로 (&는 l-value에 대한 reference이므로), `void f(const char*)`가 호출됩니다.
  ```c++
  void f(my_string&);
  void f(const char*);

  f(my_string());
  ```
  - 이를 방지하기 위해, `explicit conversion operators`를 사용할 수 있습니다.
- Explicit Conversion Operators (C++11)
  - 이는 명시적으로 지정했을 때만 사용이 가능합니다.
  ```c++
  class my_string {
    public:
      explicit operator const char*() const {return data_;}
    private:
      const char* data_;
    };
  ```
  - `explicit` 키워드를 통해서, 암시적 변환을 하려고 하면, 컴파일러 에러를 발생시킵니다.
  - 명시적 변환 연산자를 사용하려면, `static_cast`를 사용하거나, `C-style cast`(`(T)(value)`) 또는 생성자 스타일의 변환(`T(value)`)을 사용합니다.
  - 하지만 예외는 있습니다. 컴파일러는 `bool` 타입으로의 암시적 변환은 허용합니다.
  - 추가로, 컴파일러는 `bool`로 변환된 후의 다른 암시적 변환을 허용하지 않습니다. (컴파일러는 2개의 암시적 변환을 동시에 수행하는 것을 허용하지만, 사용자 정의 형태의 경우는 1개만 허용합니다.)

# Overloading `new` and `delete` operators
- `new T(arg)`를 수행하면, `operator new`가 호출되어 새로운 raw 메모리를 할당합니다. 그리고 적절한 생성자 `T`를 호출하여 이 raw 메모리를 적절한 객체로 변환합니다.
- 이와 유사하게 `delete T`를 수행하면, 소멸자가 호ㅅ브니다.
출되어 객체를 파괴하고, `operator delete`가 호출되어 raw 메모리를 해제합니다.
- C++에서는 이 `new`와 `delete`를 오버로딩할 수 있습니다.
- 첫 번째 연산자 오버로딩의 기본 룰은 `new`와 `delete`에는 특별하게 적용됩니다.
  - 거의 이 연산자들에 대한 오버로딩의 이유는 성능 문제 또는 메모리 제약 때문입니다.
  - 그리고 많은 경우에, 사용되는 알고리즘을 변경하는 방법 등의 액션이 이와 같은 메모리를 비틀어서 사용하는 방법보다 더 많은 효율을 제공할 것입니다. (그러니까 애매하게 하지말라는 뜻ㅋㅋㅋㅋ)
- STL의 기본 제공 `new`와 `delete`는 다음과 같습니다.
```c++
void* operator new(std::size_t) throw(std::bad_alloc); 
void  operator delete(void*) throw(); 
void* operator new[](std::size_t) throw(std::bad_alloc); 
void  operator delete[](void*) throw(); 
```
- 위 2개는 객체에 대한 할당 및 소멸에 대한 것이고, 아래 2개는 배열에 대한 할당 및 소멸에 대한 것입니다.
- 만약 당신이 이를 정의한다면, 이들은 오버로딩이 되는 것이 아니라, STL의 것들을 대체합니다.
- 만약 `new`를 오버로딩한다면, `delete`도 오버로딩해야 합니다. 당신이 호출하지 않는다고 하더라도, 컴파일러는 `delete`를 호출하기 때문에, `new`에 대응되는 `delete`가 없다면 이상하게 동작할 수 있습니다.
- 또한, `new`와 `delete`를 오버로딩한다면, 배열도 오버로딩하는 것을 고려해야합니다.
- `new` 대체하기
  - c++은 `new와 `delete`가 추가적인 인자를 받는 것을 허용합니다.
  - `new`는 전달된 주소에 특정한 객체를 생성할 수 있습니다.
  ``` c++
  class X { /* ... */ };
  char buffer[ sizeof(X) ];
  void f()
  { 
    X* p = new(buffer) X(/*...*/);
    // ... 
    p->~X(); // call destructor 
  } 
  ```
  - C++ STL은 다음과 같은 적절한 오버로딩을 제공하고 있습니다.
  ``` c++
  void* operator new(std::size_t,void* p) throw(std::bad_alloc); 
  void  operator delete(void* p,void*) throw(); 
  void* operator new[](std::size_t,void* p) throw(std::bad_alloc); 
  void  operator delete[](void* p,void*) throw(); 
  ```
  - 예제 코드에서, new의 위치에서 X의 생성자가 예외를 던지지 않는 한, `delete`는 호출되지 않습니다
  - 특정 class에 대한 `new`와 `delete`
    ```c++
    class my_class { 
      public: 
        // ... 
        void* operator new(std::size_t);
        void  operator delete(void*);
        void* operator new[](std::size_t);
        void  operator delete[](void*);
        // ...  
    }; 
    ```
    - `new`와 `delete`는 static 멤버함수처럼 동작합니다.
    - `myclass`에 대해 `std::size_t`는 `sizeof(myclass)`와 같습니다.
    - 하지만, 이 연산자들은 파생된 클래스에 대해 동적으로 할당할 수도 있습니다. (기본 값보다 더 크게)
    - `new`와 `delete`를 오버로딩하려면 STL보다 먼저 정의하면 되지만, 이런 경우는 드뭅니다.
    