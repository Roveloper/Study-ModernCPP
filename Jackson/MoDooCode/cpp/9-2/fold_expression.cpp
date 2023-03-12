// 가변 길이 템플릿을 사용할 경우
// 무조건 재귀함수적인 호출 방식을 사용하며
// 그러므로, 마지막 재귀 호출 시, 종료를 위한 함수를 추가해야함
// C++17에서 추가된 Fold 형식을 사용하면 이를 간단하게 표현할 수 있음

#include <iostream>

template <typename... Ints>
int sum_all(Ints... nums) {
  return (... + nums);
  // return ((((1 + 4) + 2) + 3) + 10);
  // (E op ...) --> (E1 op (... op (En-1 op En))) 단항 우측 Fold
  // (... op E) --> (((E1 op E2) op ...) op En) 단항 좌측 Fold
  // (E op ... op I) --> (E1 op (... op (En-1 op (En op I)))) 이항 우측 Fold
  // (I op ... op E) --> (((I op E1) op E2) op ...) op En) 이항 좌측 Fold
  // fold 식에는 괄호가 포함되어있음!
}

template <typename Int, typename... Ints>
Int diff_from(Int start, Ints... nums) {
  return (start - ... - nums); // 이항 좌측 Fold
}

void do_something(int x) {
  std::cout << "Do something with " << x << std::endl;
}

template <typename... Ints>
void do_many_things(Ints... nums) {
  (do_something(nums), ...); // 단항 우측 Fold
}
int main() {
  std::cout << sum_all(1, 4, 2, 3, 10) << std::endl;
  std::cout << diff_from(100, 1, 4, 2, 3, 10) << std::endl;
  do_many_things(1, 3, 2, 4);
  return 0;
}