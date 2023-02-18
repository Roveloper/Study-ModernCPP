#include <employeelist.h>

int main() {
  std::cout << "Start Employee List Program" << std::endl;
  EmployeeList em_list(10);

  em_list.add_employee(new Employee("노홍철", 34, "평사원", 1));
  em_list.add_employee(new Employee("하하", 34, "평사원", 1));
  em_list.add_employee(new Manager("유재석", 41, "부장", 7, 12));
  em_list.add_employee(new Manager("정준하", 43, "과장", 4, 15));
  em_list.add_employee(new Manager("박명수", 43, "차장", 5, 13));
  em_list.add_employee(new Employee("정형돈", 36, "대리", 2));
  em_list.add_employee(new Employee("길", 36, "인턴", -2));
  em_list.print_employee_info();

  return 0;
}