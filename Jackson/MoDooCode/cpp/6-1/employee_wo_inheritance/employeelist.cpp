#include "employeelist.h"

EmployeeList::EmployeeList(int alloc_employee)
    : alloc_employee_(alloc_employee) {
  employee_list_ = new Employee *[alloc_employee_];
  manager_list_ = new Manager *[alloc_employee_];
  current_employee_ = 0;
  current_manager_ = 0;
};

void EmployeeList::add_employee(Employee *em) {
  if (alloc_employee_ == current_employee_) {
    reserve(2 * alloc_employee_);
  }
  employee_list_[current_employee_] = em;
  ++current_employee_;
}
void EmployeeList::add_manager(Manager *ma) {
  if (alloc_employee_ == current_manager_) {
    reserve(2 * alloc_employee_);
  }
  manager_list_[current_manager_] = ma;
  ++current_manager_;
}

int EmployeeList::current_employee() { return current_employee_; }
int EmployeeList::current_manager() { return current_manager_; }
int EmployeeList::total_employee() {
  return current_employee_ + current_manager_;
}

void EmployeeList::print_employee_info() {
  int total_pay = 0;
  for (int i = 0; i < current_employee_; ++i) {
    employee_list_[i]->print_info();
    total_pay += employee_list_[i]->salary();
  }
  for (int i = 0; i < current_manager_; ++i) {
    manager_list_[i]->print_info();
    total_pay += manager_list_[i]->salary();
  }

  std::cout << "Total pay --> " << total_pay << std::endl;
}

void EmployeeList::reserve(int alloc_employee) {
  auto em_tmp = employee_list_;
  employee_list_ = new Employee *[alloc_employee];
  for (int i = 0; i < current_employee_; ++i) {
    employee_list_[i] = em_tmp[i];
  }
  delete[] em_tmp;

  auto ma_tmp = manager_list_;
  manager_list_ = new Manager *[alloc_employee];
  for (int i = 0; i < current_manager_; ++i) {
    manager_list_[i] = ma_tmp[i];
  }
  delete[] ma_tmp;
  alloc_employee_ = alloc_employee;
}

EmployeeList::~EmployeeList() {
  for (int i = 0; i < current_employee_; ++i) {
    delete employee_list_[i];
  }
  delete[] employee_list_;

  for (int i = 0; i < current_manager_; ++i) {
    delete manager_list_[i];
  }
  delete[] manager_list_;
}
