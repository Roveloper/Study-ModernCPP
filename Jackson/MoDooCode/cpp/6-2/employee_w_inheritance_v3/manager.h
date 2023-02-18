#ifndef D651513F_89CB_4E1A_9DBF_B073A25F1AA1
#define D651513F_89CB_4E1A_9DBF_B073A25F1AA1

#include <iostream>
#include <string>
#include <employee.h>

class Manager : public Employee{
private:
  int year_of_service_; // 근속 연수

public:
  Manager(std::string name, int age, std::string position, int rank, int year_of_service);
  Manager(const Manager &manager);
  Manager() = default;
  void print_info() override;
  int salary() override;
};

#endif /* D651513F_89CB_4E1A_9DBF_B073A25F1AA1 */
