#include <iostream>
#include <unordered_set>

// 나만의 클래스를 unordered_set이나 unordered_map에 넣으려면 2가지가 필요
// 해당 객체의 hash함수가 필요
// operator==가 필요 (중복 여부를 이를 통해서 확인할 것이기 때문)
// std::hash는 기본적으로 bool, char, signed char, unsigned char, char16_t, short, int, long, fload, double 등에 대해서는 사용 가능
// https://en.cppreference.com/w/cpp/utility/hash

template <typename K>
void print_unordered_set(const std::unordered_set<K>& m) {
  // 셋의 모든 원소들을 출력하기
  for (const auto& elem : m) {
    std::cout << elem << std::endl;
  }
}

class Todo {
  int pri_;
  std::string job_;

  public:
   Todo(int p, std::string job) : pri_(p), job_(job) {};
   bool operator==(const Todo& t) const {
    if (pri_ == t.pri_ && job_ == t.job_) return true;
    return false;
   }
   friend std::ostream& operator<<(std::ostream& os, const Todo& t);
   friend struct std::hash<Todo>;
};

std::ostream& operator<<(std::ostream& os, const Todo& t) {
  os << "중요도 [ " << t.pri_ << "] -> " << t.job_ << std::endl;
  return os;
}

template <>
struct std::hash<Todo> {
  size_t operator()(const Todo& t) const {
    std::hash<std::string> hash_func;

    return t.pri_ ^ (hash_func(t.job_));
  }
};

int main() {
  std::unordered_set<Todo> todos;

  todos.insert(Todo(1, "공부 하기"));
  todos.insert(Todo(2, "청소 하기"));
  todos.insert(Todo(3, "출근 하기"));
  todos.insert(Todo(2, "빨래 하기"));
  todos.insert(Todo(2, "영화 보기"));

  print_unordered_set(todos);
}