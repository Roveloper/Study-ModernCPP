#include <iostream>
#include <memory>

// 그래도 난 복사가 꼭 필요한데...!? 다른 애한테 넘겨서 쟤한테 객체의 소멸에 대한 책임을 넘기면 되지 않나?
// 그렇습니다. 그렇기 위해서는 해당 객체를 가리키는 포인터를 넘겨줘야합니다.
// 기존 rvalue reference 방식을 생각해보면, 복사 생성을 통해서 객체를 넘겨주는 것이 아니라 (동시에 같은 객체가 2개가 존재하는 것이 아니라)
// 단순 내부 포인터를 바꿔주고, 기존 포인터를 nullptr로 만들어버리는 방식이므로 (하나의 객체만으로도 이동을 완성할 수 있습니다.)
// 이를 통해 소유권 이전이 가능합니다.

class A {
  int *data;

  public:
  A() {
    std::cout << "get resource" << std::endl;
    data = new int[100];
  }

  void some() {std::cout << "일반 포인터와 동일하게 사용 가능" << std::endl;}
  void print() {std::cout << "data : " << data[0] << std::endl;}

  ~A() {
    std::cout << "call destructor" << std::endl;
    delete[] data;
  }
};

void do_something() {
  std::unique_ptr<A> pa(new A());
  std::cout << "pa : ";
  pa->some();

  std::unique_ptr<A> pb = std::move(pa); // pa를 rvalue reference로 변경해서 pb에 전달
  // 그렇다고 pa라는 객체가 pb로 넘겨지는 이 순간에 바로 삭제되는 것은 아님
  // 그렇지만 pa에는 아무것도 남아있지 않고, nullptr를 참조하게 됨
  std::cout << "pb : ";
  pb->some(); // 함수 호출은 가능함, 왜냐면 해당 객체의 함수는 코드 상에 남아있기 때문 (내부 변수에 접근하지 않기 때문에)
  
  pa->some(); // 함수 호출은 가능함, 왜냐면 해당 객체의 함수는 코드 상에 남아있기 때문 (내부 변수에 접근하지 않기 때문에)
  pa->print(); // 하지만, 내부 변수에 접근하려고 하면, seg fault가 발생함 (data[0]에 접근)

  // 나는 소유권은 안옮길거고, 이따가 어차피 소멸되긴 하겠지만, 여기서부터 사용을 안할거니까 해제하고 싶어! 하는 경우에는 아래 명령어로 reset 가능
  pa.reset(nullptr);

  // 현재 pa는 nullptr를 참조하고 있으며, 이 상태를 댕글링 포인터라고 합니다. (좀비 상태라고 보면 되며, 다시 재참조를 해버리면 런타임 오류 발생)
}

int main() { do_something();}