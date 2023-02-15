#include "employeelist.h"

EmployeeList::EmployeeList(int alloc_employee)
    : alloc_employee_(alloc_employee) {
  employee_list_ = new Employee *[alloc_employee_];
  current_employee_ = 0;
};

void EmployeeList::add_employee(Employee *em) {
  if (alloc_employee_ == current_employee_) {
    reserve(2 * alloc_employee_);
  }
  employee_list_[current_employee_] = em;
  ++current_employee_;
}

int EmployeeList::current_employee() { return current_employee_; }

void EmployeeList::print_employee_info() {
  int total_pay = 0;
  for (int i = 0; i < current_employee_; ++i) {
    employee_list_[i]->print_info();
    total_pay += employee_list_[i]->salary();
  }
  std::cout << "Total pay --> " << total_pay << std::endl;
}

void EmployeeList::reserve(int alloc_employee) {
  auto tmp = employee_list_;
  employee_list_ = new Employee *[alloc_employee];
  for (int i = 0; i < current_employee_; ++i) {
    employee_list_[i] = tmp[i];
  }
  alloc_employee_ = alloc_employee;
}

EmployeeList::~EmployeeList() {
  for (int i = 0; i < current_employee_; ++i) {
    delete employee_list_[i];
  }
  delete[] employee_list_;
}
