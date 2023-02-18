#include "manager.h"

Manager::Manager(std::string name, int age, std::string position, int rank,
                 int year_of_service)
    : Employee(name, age, position, rank), year_of_service_(year_of_service){};
Manager::Manager(const Manager &manager)
    : Employee(manager.name_, manager.age_, manager.position_, manager.rank_) {
  year_of_service_ = manager.year_of_service_;
}
void Manager::print_info() {
  std::cout << name_ << " ( " << age_ << " ) [ " << position_ << "(" << rank_
            << ") ] [ Working " << year_of_service_ << " years ]==> "
            << salary() << std::endl;
}
int Manager::salary() { return 200 + rank_ * 50 + 5 * year_of_service_; }