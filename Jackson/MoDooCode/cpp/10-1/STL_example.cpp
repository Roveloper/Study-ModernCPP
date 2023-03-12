// STL --> Standard Template Library
// Container --> 임의 타입의 객체를 보관할 수 있는 컨테이너
// Iterator --> 컨테이너에 보관된 원소에 접근할 수 있는 반복자
// algorithm --> 반복자를 이용하여 작업을 수행하는 것
// 이 세 가지를 포함하는 것을 STL이라고 함

// Container
// 배열처럼 객체를 순차적으로 보관해주는 Sequence Container (vector, list, deque)
// 키를 바탕으로 대응되는 값을 보관해주는 Associative Container ()

// vector
// 임의 원소 접근 (at, []) --> O(1)
// 맨 뒤 원소 추가, 삭제 (push_back, pop_back) --> amortized O(1) 평균적으로 O(1) 최악의 경우 O(N)
// 임의의 위치 원소 추가 및 제거 (insert, erase) --> O(N)

// vector iterator
// vector.begin() --> vector의 첫번째 원소 위치
// vector.end() --> vector의 마지막 원소 위치 + 1
// vector.begin() == vector.end() 이면 비어있다는 뜻
// vector.cbegin(), vector.cend() --> const iterator를 얻을 수 있음 (값 변경 불가)
// vector.rbegin(), vector.rend() 도 사용 가능 (역방향 iterator)
// vector.crbegin(), vector.crend()로 const 역방향 iterator얻을 수 있음
// for문을 이용해서 반대로 돌면, vector.size는 size_t 타입으로 나오기 때문에, for문으로 0까지 서치하기가 쉽지 않음 (0에서 -1이 되면 언더플로우로 큰 값이 되므로)


// 반복자 사용 예시
#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
void print_vector(std::vector<T>& vec) {
  // 전체 벡터를 출력하기
  for (typename std::vector<T>::iterator itr = vec.begin(); itr != vec.end();
       ++itr) {
    std::cout << *itr << std::endl;
  }
}

template <typename T>
void print_vector_range_based(std::vector<T>& vec) {
  // 전체 벡터를 출력하기
  for (const auto& elem : vec) {
    std::cout << elem << std::endl;
  }
}

template <typename T>
void print_vector_range_based_reversed(std::vector<T>& vec) {
  // 전체 벡터를 출력하기
  for (const auto& elem : std::reverse(vec)) {
    std::cout << elem << std::endl;
  }
}


int main() {
  std::vector<int> vec;
  vec.push_back(10);
  vec.push_back(20);
  vec.push_back(30);
  vec.push_back(40);

  // int arr[4] = {10, 20, 30, 40}
  // *(arr + 2) == arr[2] == 30;
  // *(itr + 2) == vec[2] == 30;

  std::vector<int>::iterator itr = vec.begin() + 2;
  std::cout << "3 번째 원소 :: " << *itr << std::endl;\


    std::cout << "처음 벡터 상태" << std::endl;
  print_vector(vec);
  std::cout << "----------------------------" << std::endl;

  // vec[2] 앞에 15 추가
  vec.insert(vec.begin() + 2, 15);
  print_vector(vec);

  std::cout << "----------------------------" << std::endl;
  // vec[3] 제거
  vec.erase(vec.begin() + 3);
  print_vector(vec);
  std::cout << " range-based loop" << std::endl;
  print_vector_range_based(vec);
  print_vector_range_based_reversed(vec);
}