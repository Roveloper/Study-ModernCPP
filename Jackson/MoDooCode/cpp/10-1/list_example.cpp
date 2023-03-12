#include <iostream>
#include <list>

// list의 경우 linked-list를 의미하며, 양방향 list를 사용합니다.
// 접근은 오래 걸리고, []이나 at 같은 연산자는 없습니다.
// but, 앞 뒤에 값을 추가하는데는 O(1)밖에 걸리지 않으므로, 이러한 경우에는 좋습니다.

template <typename T>
void print_list(std::list<T>& lst) {
  std::cout << "[ ";
  // 전체 리스트를 출력하기 (이 역시 범위 기반 for 문을 쓸 수 있습니다)
  for (const auto& elem : lst) {
    std::cout << elem << " ";
  }
  std::cout << "]" << std::endl;
}

int main() {
  std::list<int> lst;

  lst.push_back(1);
  lst.push_back(2);
  lst.push_back(3);
  lst.push_front(4);
  lst.push_front(10);

  for (const auto& val : lst) {
    std::cout << val << " ";
  }
  std::cout << std::endl;

  for (auto it = lst.begin(); it != lst.end(); ++it) { //list의 반복자의 경우 ++, --는 수행이 가능하지만, +5, +3 이런 특정한 위치로는 불가능하다고 합니다, Bidirectional Iterator입니다. 반대로 Vector의 경우는 RandomAccessIterator입니다.
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  std::list<int> lst2;

  lst2.push_back(10);
  lst2.push_back(20);
  lst2.push_back(30);
  lst2.push_back(40);

  std::cout << "처음 리스트의 상태 " << std::endl;
  print_list(lst2);

  for (std::list<int>::iterator itr = lst2.begin(); itr != lst2.end(); ++itr) {
    // 만일 현재 원소가 20 이라면
    // 그 앞에 50 을 집어넣는다.
    if (*itr == 20) {
      lst2.insert(itr, 50);
    }
  }

  std::cout << "값이 20 인 원소 앞에 50 을 추가 " << std::endl;
  print_list(lst2);

  for (std::list<int>::iterator itr = lst2.begin(); itr != lst2.end(); ++itr) { // vector와는 다르게, 중간에 값을 지우거나 추가해도 iterator가 무의미해지지 않음 (특정한 메모리 주소를 가리키고 있기 때문)
    // 값이 30 인 원소를 삭제한다.
    if (*itr == 30) {
      lst2.erase(itr);
      break;
    }
  }

  std::cout << "값이 30 인 원소를 제거한다" << std::endl;
  print_list(lst2);

  return 0;
}