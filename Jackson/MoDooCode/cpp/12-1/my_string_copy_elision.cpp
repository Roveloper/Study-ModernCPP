#include <iostream>
#include <cstring>

class MyString {
  char *string_content;  // 문자열 데이터를 가리키는 포인터
  int string_length;     // 문자열 길이

  int memory_capacity;  // 현재 할당된 용량

 public:
  MyString();

  // 문자열로 부터 생성
  MyString(const char *str);

  // 복사 생성자
  MyString(const MyString &str);

  // 이동 생성자
  MyString(MyString &&str); // 수정해야하므로 const는 없습니다.

  void reserve(int size);
  MyString operator+(const MyString &s);
  ~MyString();

  int length() const;

  void print();
  void println();
};

MyString::MyString() {
  std::cout << "생성자 호출 ! " << std::endl;
  string_length = 0;
  memory_capacity = 0;
  string_content = nullptr;
}

MyString::MyString(const char *str) {
  std::cout << "생성자 호출 ! " << std::endl;
  string_length = strlen(str);
  memory_capacity = string_length;
  string_content = new char[string_length];

  for (int i = 0; i != string_length; i++) string_content[i] = str[i];
}
MyString::MyString(const MyString &str) {
  std::cout << "복사 생성자 호출 ! " << std::endl;
  string_length = str.string_length;
  memory_capacity = str.string_length;
  string_content = new char[string_length];

  for (int i = 0; i != string_length; i++)
    string_content[i] = str.string_content[i];
}
MyString::MyString(MyString &&str) {
  std::cout << "이동 생성자 호출 !" << std::endl;
  string_length = str.string_length;
  memory_capacity = str.memory_capacity;
  string_content = str.string_content; // 이러한 복사를 수행하면서, 포인터만 바꿔주므로 속도가 아주 빠릅니다.
  str.string_content = nullptr; // 임시 객체인 str의 포인터를 nullptr로 바꿔서, 객체 소멸 시 해당 포인터가 가리키는 값이 사라지지 않도록 한다!
}

MyString::~MyString() { 
  if (string_content != nullptr) delete[] string_content; 
}
void MyString::reserve(int size) {
  if (size > memory_capacity) {
    char *prev_string_content = string_content;

    string_content = new char[size];
    memory_capacity = size;

    for (int i = 0; i != string_length; i++)
      string_content[i] = prev_string_content[i];

    if (prev_string_content != nullptr) delete[] prev_string_content;
  }
}
MyString MyString::operator+(const MyString &s) {
  MyString str;
  str.reserve(string_length + s.string_length);
  for (int i = 0; i < string_length; i++)
    str.string_content[i] = string_content[i];
  for (int i = 0; i < s.string_length; i++)
    str.string_content[string_length + i] = s.string_content[i];
  str.string_length = string_length + s.string_length;
  return str;
}
int MyString::length() const { return string_length; }
void MyString::print() {
  for (int i = 0; i != string_length; i++) std::cout << string_content[i];
}
void MyString::println() {
  for (int i = 0; i != string_length; i++) std::cout << string_content[i];

  std::cout << std::endl;
}

int main() {
  MyString str1("abc");
  MyString str2("def");
  std::cout << "-------------" << std::endl;
  MyString str3 = str1 + str2; // 이렇게 복사를 수행할 때, const T&는 l, rvalue를 모두 받을 수 있으며, const이므로 수정이 불가능합니다.
  // 따라서 복사를 수행할 때, 해당 객체 내부 포인터가 가리키는 값이 소멸되지 않도록 만들 방법이 없음 (nullptr로 바꿔줘야하는데 const라 불가능)
  // 그러면 rvalue만 받을 수 있는 방법은?? 이것이 바로 rvalue reference입니다.
  MyString&& tmp_str = str1 + str2;
  str3.println();
  tmp_str.println(); // 분명 str1 + str2는 임시 객체이므로, 사라져야하지만, rvalue reference는 이를 소멸되지 않도록 붙잡을 수 있음
}