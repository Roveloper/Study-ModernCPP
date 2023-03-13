#include <iostream>
#include <set>

#include <iostream>
#include <set>
#include <string>

template <typename T, typename C> void print_set(std::set<T, C> &s) {
    for (const auto &val : s) {
        std::cout << val;
    }
    std::cout << std::endl;
}

class Todo {
    int priority_;
    std::string job_desc_;

  public:
    Todo(int priority, std::string job_desc) : priority_(priority), job_desc_(job_desc){};

    // bool operator<(const Todo& rhs) const { // set을 사용하기 위해서는 operator<가 꼭 정의가 되어
    // 있어야함 (그리고 무조건 const ref를 받는 const함수여야 함)
    //   if (priority_ == rhs.priority_) { // 이를 나눠서 구현하지 않으면, 중요도가 같은 애들은 하나
    //   밖에 정의할 수 없게됩니다. (a < b도 false, b < a도 false이면 중복으로 판단)
    //     return (job_desc_ < rhs.job_desc_);
    //   }
    //   return (priority_ < rhs.priority_);
    // }

    friend std::ostream &operator<<(std::ostream &o, const Todo &td);
    friend struct TodoComp;
};

struct TodoComp {
    bool operator()(const Todo &t1, const Todo &t2) const {
        if (t1.priority_ == t2.priority_) {
            return (t1.job_desc_ < t2.job_desc_);
        }
        return (t1.priority_ < t2.priority_);
    }
};

std::ostream &operator<<(std::ostream &o, const Todo &td) {
    o << "[ 중요도: " << td.priority_ << "] " << td.job_desc_ << std::endl;
    return o;
}

int main() {
    std::set<Todo, TodoComp> todos; // 두 번째 템플릿 인자로 비교 함수 객체를 넘겨주면 사용할 수 있음

    todos.insert(Todo(1, "공부 하기"));
    todos.insert(Todo(2, "C++ 스터디"));
    todos.insert(Todo(3, "일찍 자기"));
    todos.insert(Todo(1, "친구 만나기"));
    todos.insert(Todo(2, "영화 보기"));

    print_set(todos);

    if (todos.find(Todo(2, "영화 보기")) != todos.end()) {
        todos.erase(todos.find(Todo(2, "영화 보기")));
    }
    if (todos.find(Todo(10, "잠자기")) != todos.end()) {
        todos.erase(todos.find(Todo(10, "잠자기")));
    }

    print_set(todos);
}