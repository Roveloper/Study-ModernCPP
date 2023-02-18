#ifndef A1BD474E_8E5F_416A_B998_1AB0AD868663
#define A1BD474E_8E5F_416A_B998_1AB0AD868663

#include <employee.h>
#include <manager.h>
#include <iostream>

class EmployeeList {
private:
  int alloc_employee_;
  int current_employee_;
  int current_manager_;
  Employee **employee_list_;
  Manager **manager_list_;

public:
  EmployeeList(int alloc_employee);
  void add_employee(Employee *em);
  void add_manager(Manager *ma);
  int current_employee();
  int current_manager();
  int total_employee();
  void print_employee_info();
  void reserve(int alloc_employee);
  ~EmployeeList();
};

#endif /* A1BD474E_8E5F_416A_B998_1AB0AD868663 */
