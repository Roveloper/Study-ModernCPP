#ifndef D485DDC5_1A45_4994_94EA_8437291F9948
#define D485DDC5_1A45_4994_94EA_8437291F9948

#include <iostream>
#include <string>

class Employee {
private:
  std::string name_;
  int age_;
  std::string position_; // 직책
  int rank_;

public:
  Employee(std::string name, int age, std::string position, int rank);
  Employee(const Employee &employee);
  Employee() = default;
  void print_info();
  int salary();
};

#endif /* D485DDC5_1A45_4994_94EA_8437291F9948 */
