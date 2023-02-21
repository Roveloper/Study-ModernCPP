#include <iostream>
#include <fstream>
#include <string>

class Human {
  std::string name_;
  int age_;

  public:
   Human(const std::string& name, int age) : name_(name), age_(age) {}
   std::string get_info() {
    return "Name :: " + name_ + " / Age :: " + std::to_string(age_);
   }

   friend std::ofstream& operator<<(std::ofstream& o, Human& h);
};

std::ofstream& operator<<(std::ofstream& o, Human& h) {
  o << h.get_info();
  return o;
}

int main() {
  std::ofstream out("test.txt");

  Human h("김재훈", 30);
  out << h << std::endl;

  return 0;
}