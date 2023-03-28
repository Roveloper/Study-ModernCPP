#include <iostream>
#include <vector>
#include <memory>
#include <string>

class A{
  std::string s;
  std::weak_ptr<A> other;

  public:
    A() = default;
    A(const std::string& s) : s(s) {
      std::cout <<  "get resources" << std::endl;
    }
    ~A() {
      std::cout << "call destructor" << std::endl;
    }

    void set_other(std::weak_ptr<A> o) {
      other= o; // weak_ptr이나 shared_ptr로 이미 제어 블록을 가지고 있는 객체만을 전달할 수 있음, 일반 포인터는 전달할 수 없음
    }

    void access_other() {
      std::shared_ptr<A> o = other.lock(); // 해당 객체가 존재한다면 shared_ptr을 반환, 존재하지 않는다면 nullptr로 생성된 shared_ptr을 반환
      // 객체가 소멸을 했다고 해서, 제어블록도 소멸하는 것은 아님! (제어 블록이 소멸해버리면, weak_ptr이 reference count를 확인할 수 있는 방법 조차 없어지므로)
      // 실제로는 shared_ptr의 ref count 뿐만 아니라, weak_ptr의 ref count도 확인하며, weak_ptr의 ref count도 모두 0이 되었을 때, 제어 블록이 소멸 됨
      if (o) {
        std::cout << "access: " << o->name() << std::endl;
      } else {
        std::cout << "already destroyed" << std::endl;
      }
    }
    std::string name() { return s;}
};

int main() {
  std::vector<std::shared_ptr<A>> vec;
  vec.push_back(std::make_shared<A>("자원 1"));
  vec.push_back(std::make_shared<A>("자원 2"));

  vec[0]->set_other(vec[1]);
  vec[1]->set_other(vec[0]); // 순환 참조로 만듦

  std::cout << "0 count = " << vec[0].use_count() << std::endl; // vec[0]과 vec[1].other가 참조하고 있음
  std::cout << "1 count = " << vec[1].use_count() << std::endl; // vec[1]과 vec[0].other가 참조하고 있음
  // 그렇지만 count는 1임 (왜냐면 other는 weak_ptr이니깐, count에 영향을 주지 않음)

  vec[0]->access_other(); // count가 존재하므로, 아직 객체는 살아있으며, 접근이 가능

  vec.pop_back(); // 해당 위치에서 vec[1]은 소멸됨 (vec[1]의 count가 0으로 바뀜)
  vec[0]->access_other(); // count가 0이므로 존재하지 않고, make_shared<A>(nullptr)이 리턴될 걸?
}