// 연관 컨테이너는 키와 값으로 이루어짐
// 특정 키가 존재하는지 ? 질문 가능
// 존재한다면 이에 대응하는 값은 무엇인지? 질문 가능

// set, multiset --> 특정 키가 존재하는 지 여부를 확인 (값은 존재하지 않음)
// map, multimap --> 특정 키가 존재하는 지 여부를 확인하고, 해당 키에 대응하는 값이 무엇인지 확인 가능 (당연히 set, multiset에 비해 메모리 공간 많이 차지함)

#include <iostream>
#include <set>

template <typename T>
void print_set(std::set<T>& s) {
  std::cout << "[ " ;
  for (auto it = s.begin(); it != s.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << " ]" << std::endl;
}

template <typename T>
void print_set_range_loop(std::set<T>& s) {
  std::cout << "[ " ;
  for (const auto& val : s) {
    std::cout << val << " ";
  }
  std::cout << " ]" << std::endl;
}

int main() {
  std::set<int> s;
  s.insert(10);
  s.insert(50);
  s.insert(20);
  s.insert(40);
  s.insert(30);

  std::cout << "순차 정렬 되어 결과가 출력된다" << std::endl;
  print_set(s);

  std::cout << "20이 s의 원소인가요? :: ";
  auto itr = s.find(20); // key에 특정 값이 존재하는 지 확인 가능
  if (itr != s.end()) {
    std::cout << "Yes" << std::endl;
  } else {
    std::cout << "No" << std::endl;
  }

  std::cout << "25가 s의 원소인가요? :: ";
  itr = s.find(25); // key에 특정 값이 존재하는 지 확인 가능
  if (itr != s.end()) {
    std::cout << "Yes" << std::endl;
  } else {
    std::cout << "No" << std::endl;
  }
}

// 원소 추가 또는 삭제 --> O(logN) (왜냐하면 정렬되어야하기 때문)
// 원소 접근 --> BidirectionalIterator이며, 특정 값에 접근은 불가능하며, 하나씩만 접근 가능
// 원소가 존재하는지 여부 확인 --> O(logN) (내부 정렬된 상태를 찾기 때문에, 아마 Tree형태로 구성되어 있을 듯)
// Set은 특히 중복이 없음 (중요)
// 중복된 원소를 허용하고 싶으면? multiset을 사용하면 됨!

