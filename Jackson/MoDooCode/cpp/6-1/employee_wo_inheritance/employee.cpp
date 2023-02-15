#include "employee.h"

Employee::Employee(std::string name, int age, std::string position, int rank)
    : name_(name), age_(age), position_(position), rank_(rank){};
Employee::Employee(const Employee &employee) {
  name_ = employee.name_;
  age_ = employee.age_;
  position_ = employee.position_;
  rank_ = employee.rank_;
}

void Employee::print_info() {
  std::cout << name_ << " ( " << age_ << " ) [ " << position_ << "(" << rank_
            << ") ] ==> " << salary() << std::endl;
}

int Employee::salary() { return 200 + rank_ * 50; }