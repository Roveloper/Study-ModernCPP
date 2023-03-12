#include <iostream>
#include <array>

void print_array(const std::array<int, 5>& arr) {
  for (int i = 0; i < arr.size(); ++i) {
    std::cout << arr[i] << ", ";
  }
  std::cout << std::endl;
}

template <typename T>
void print_array_template(const T& arr) {
  for (int i = 0; i < arr.size(); ++i) {
    std::cout << arr[i] << ", ";
  }
  std::cout << std::endl;
}

int main() {
  std::array<int, 5> arr = {1, 2, 3, 4, 5}; 
  // C 스타일의 배열은 크기를 컴파일 타임에 지정함에도 불구하고, 이에 대한 정보를 가지고 있지 않았습니다.
  // 이에 대한 문제를 해결하면서, 편의성을 추가한 것이 std::array입니다.
  // 마찬가지로 동적인 크기를 가지고 있는 것이 아닌, 컴파일 타임에 크기가 결정됩니다.

  print_array(arr);

  std::array<int, 7> arr_7 = {5, 3, 2, 1, 4, 6, 7};
  // print_array(arr_7); // std::array<int, 5>를 입력으로 받게 정의된 함수이므로, 컴파일 오류 발생
  print_array_template(arr);
  print_array_template(arr_7);

  return 0;
}