#include "manager.h"

Manager::Manager(std::string name, int age, std::string position, int rank,
                 int year_of_service)
    : name_(name), age_(age), position_(position), rank_(rank),
      year_of_service_(year_of_service){};
Manager::Manager(const Manager &manager) {
  name_ = manager.name_;
  age_ = manager.age_;
  position_ = manager.position_;
  rank_ = manager.rank_;
  year_of_service_ = manager.year_of_service_;
}
void Manager::print_info() {
  std::cout << name_ << " ( " << age_ << " ) [ " << position_ << "(" << rank_
            << ") ] [ Working " << year_of_service_ << " years ]==> "
            << salary() << std::endl;
}
int Manager::salary() { return 200 + rank_ * 50 + 5 * year_of_service_; }