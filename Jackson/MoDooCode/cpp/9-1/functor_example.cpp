#include <iostream>
#include <string>
#include <myvector.hpp>

template <typename Cont, typename Comp>
void bubble_sort(Cont& cont, Comp& comp) {
  for (int i = 0; i < cont.size(); ++i) {
    for (int j = i + 1; j < cont.size(); ++j) {
      if (!comp(cont[i], cont[j])) { // comp 객체를 통해서 비교를 수행!
        cont.swap(i, j);
      }
    }
  }
}

struct Comp1 {
  bool operator()(int a, int b) { return a > b; }
};

struct Comp2 {
  bool operator()(int a, int b) { return a < b; }
};

int main() {
  Vector<int> int_vec;
  int_vec.push_back(3);
  int_vec.push_back(1);
  int_vec.push_back(2);
  int_vec.push_back(8);
  int_vec.push_back(5);
  int_vec.push_back(3);

  std::cout << "before sort" << std::endl;
  for (int i = 0; i < int_vec.size(); ++i) {
    std::cout << int_vec[i] << ", ";
  }

  Comp1 comp1;
  bubble_sort(int_vec, comp1);

  std::cout << std::endl << std::endl << "after descending sort" << std::endl;
  for (int i = 0; i < int_vec.size(); ++i) {
    std::cout << int_vec[i] << ", ";
  }

  Comp2 comp2;
  bubble_sort(int_vec, comp2);
  
  std::cout << std::endl << std::endl << "after ascending sort" << std::endl;
  for(int i = 0; i < int_vec.size(); ++i) {
    std::cout << int_vec[i] << ", ";
  }

  std::cout << std::endl;

  return 0;
}