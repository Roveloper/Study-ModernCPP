#ifndef D485DDC5_1A45_4994_94EA_8437291F9948
#define D485DDC5_1A45_4994_94EA_8437291F9948

#include <iostream>
#include <string>

class Employee {
protected:
  std::string name_;
  int age_;
  std::string position_; // 직책
  int rank_;

public:
  Employee(std::string name, int age, std::string position, int rank);
  Employee(const Employee &employee);
  Employee() = default;
  virtual void print_info();
  virtual int salary();
};

#endif /* D485DDC5_1A45_4994_94EA_8437291F9948 */
