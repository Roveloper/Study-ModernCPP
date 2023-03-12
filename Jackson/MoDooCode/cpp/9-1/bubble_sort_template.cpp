#include <iostream>
#include <string>
#include "myvector.hpp"

template <typename Cont>
void bubble_sort(Cont& cont) {
  for (int i = 0; i < cont.size(); ++i) {
    for (int j = i + 1; j < cont.size(); ++j) {
      if (cont[i] > cont[j]) {
        cont.swap(i, j);
      }
    }
  }
}
// 특정 컨테이너를 받아서, 이를 정렬해주는 함수
// 당연히 이를 사용하려면, 표현되어있는 container.size(), container.swap(), container[]이 있어야함.
// 이가 없는 상황이라면, 컴파일 오류가 발생 (런타임 에러가 아님)
// 컴파일 시에 모든 템플릿이 인스턴스화 된다는 사실을 가지고 코드를 작성하는 것을 템플릿 메타 프로그래밍이라고 함.

// 만약 반대로 역순으로 sort하고 싶을 때는...?
// 1. bubble_sort 함수를 복사해서, bubble_sort_reverse 함수를 만들고, cont[i] > cont[j]를 cont[i] < cont[j]로 바꿔주면 됨.
// 2. operator<를 오버로딩해서 반대로 동작하도록 함
// 3. 비교를 >를 통해서 하는 것이 아닌, 특정 함수를 통해서 전달하여, 비교 함수를 통해 비교하도록 함 (functor 사용)

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
  std::cout << std::endl;

  bubble_sort(int_vec);

  std::cout << "after sort" << std::endl;
  for (int i = 0; i < int_vec.size(); ++i) {
    std::cout << int_vec[i] << ", ";
  }
  std::cout << std::endl;

  return 0;
}

