#include <string.h>
#include <iostream>

class string {
  char *str;
  int len;

  public:
    string(char c, int n);
    string(const char *s);
    string(const string &s);
    ~string();

    void add_string(const string &s);
    void copy_string(const string &s);
    int strlen();
    void print_string();
};

string::string(char c, int n) {
  len = n;
  str = new char[n + 1];
  for (int idx=0; idx < n; idx++) {
    str[idx] = c;
  }
  str[n] = '\0';
  std::cout << "n개 생성자 호출" << std::endl;
}

string::string(const char *s) {
  len = sizeof(s) / sizeof(char);
  str = new char[len + 1];
  strcpy(str, s);
  std::cout << "char 배열 복사 생성자 호출" << std::endl;
}

string::string(const string &s) {
  len = s.len;
  str = new char[s.len + 1];
  strcpy(str, s.str);
  std::cout << "찐 복사 생성자 호출" << std::endl;
}

string::~string() {
  if (str) {
    delete[] str;
  }
}

void string::add_string(const string &s) {
  len += s.len;
  char *old_str = str;
  str = new char[len + 1];
  strcpy(str, old_str);
  strcat(str, s.str);
  delete[] old_str;
}

void string::copy_string(const string &s) {
  len = s.len;
  str = new char[s.len + 1];
  strcpy(str, s.str);
}

int string::strlen() {
  return len;
}

void string::print_string() {
  for (int i=0; i<len; i++) {
    std::cout << str[i];
  }
}

int main() {
  string a_str('c', 10);
  string b_str(a_str);
  string c_str("Hello");

  a_str.print_string();
  std::cout << std::endl;
  b_str.print_string();
  std::cout << std::endl;
  c_str.print_string();
  std::cout << std::endl;

  a_str.add_string(c_str);
  b_str.copy_string(a_str);

  a_str.print_string();
  std::cout << std::endl;
  b_str.print_string();
  std::cout << std::endl;
  c_str.print_string();
  std::cout << std::endl;

  return 0;  
}

