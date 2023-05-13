#include <iostream>
#include <vector>

class A {
  public:
    A(std::initializer_list<int> l) {
      for (auto itr = l.begin(); itr != l.end(); ++itr) {
        std::cout << *itr << std::endl;
      }
    }
};

int main() {
  int arr[] = {1, 2, 3, 4}; // arr[4]
  std::vector<int> v = {1, 2, 3, 4};
  A a = {1, 2, 3, 4, 5};
}