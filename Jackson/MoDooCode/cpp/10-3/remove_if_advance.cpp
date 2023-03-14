#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

template <typename Iter> void print(Iter begin, Iter end) {
    while (begin != end) {
        std::cout << "[" << *begin << "] ";
        begin++;
    }
    std::cout << std::endl;
}
struct is_odd {
    int num_delete;

    is_odd() : num_delete(0) {}

    bool operator()(const int &i) {
        if (num_delete >= 2)
            return false; // 멤버변수로 조건을 걸어서 특정 조건에서만 멈추도록하였음

        if (i % 2 == 1) {
            num_delete++;
            return true;
        }

        return false;
    }
};

struct is_odd2 {
    int *num_delete;

    is_odd2(int *num_delete) : num_delete(num_delete) {}

    bool operator()(const int &i) {
        if (*num_delete >= 2)
            return false; // 멤버변수로 조건을 걸어서 특정 조건에서만 멈추도록하였음

        if (i % 2 == 1) {
            (*num_delete)++;
            return true;
        }

        return false;
    }
};
int main() {
    std::vector<int> vec;
    vec.push_back(5);
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    std::cout << "처음 vec 상태 ------" << std::endl;
    print(vec.begin(), vec.end());

    std::cout << "벡터에서 홀수인 원소 앞의 2개 제거 ---" << std::endl;
    vec.erase(std::remove_if(vec.begin(), vec.end(), is_odd()),
              vec.end()); // 실제 적용되는 is_odd가 복사되어 처리가 되기 때문에, 객체 내부의 상태가
                          // 바뀌는 경우는 허용하지 않습니다
    print(vec.begin(), vec.end()); // ??? 근데 왜 3개가 지워졌지...?

    // 그렇다면 외부에서 집어넣는다면 가능할까?
    std::vector<int> vec2 = {5, 3, 1, 2, 3, 4};

    int erase_cnt = 0;
    vec2.erase(std::remove_if(vec2.begin(), vec2.end(), is_odd2(&erase_cnt)), vec2.end());
    // 이렇게 pointer로 전달해주면 가능은 합니다... 근데... 쌩포인터라니... 뭔가 맘에 들지 않아요
    // 그리고 관리해야할 변수가 자꾸 늘어나서 불편합니다. (외부 변수를 내부에서 바꾸는 시스템도 영
    // 별로....)

    print(vec2.begin(), vec2.end());

    // 제일 좋은 것은 erase하는 곳에서 모든 것을 해결하는 것이 좋습니다. (저렇게 함수 객체를
    // struct로 생성해서 사용하는 것도 좀 불편...) 이럴 때 나오는 것이 바로 lambda 함수

    std::vector<int> v3 = {5, 3, 1, 2, 3, 4};
    v3.erase(std::remove_if(v3.begin(), v3.end(), [](int i) -> bool { return i % 2 == 1; }),
             v3.end());

    print(v3.begin(), v3.end());

    std::vector<int> v4 = {5, 3, 1, 2, 3, 4};
    {
        int erase_cnt = 0;
        v4.erase(std::remove_if(v4.begin(), v4.end(),
                                [&erase_cnt](int i) -> bool { // reference를 캡쳐하는 것이 아니라, 값을 캡쳐하게 되면, 복사본을 가지게 되며, 이 값은 const이므로 수정할 수 없습니다
                                    // 만약 클래스 정의 내에서 해당 객체의 멤버 변수에 접근하고 싶다면, 레퍼런스로 멤버 변수를 캡처하는 것이 아니라, this를 캡처하시면 됩니다 (this는 레퍼런스 전달이 안됩니다)
                                    // [] 는 아무것도 캡쳐 안함, [&a, b]는 a는 reference로, b는 복사로 캡쳐, [&]는 외부의 모든 변수를 reference로 캡쳐한다는 뜻, [=]는 외부의 모든 변수를 복사본으로 캡쳐한다는 뜻
                                    if (erase_cnt >= 2) {
                                        return false;
                                    }
                                    if (i % 2 == 1) {
                                        ++erase_cnt;
                                        return true;
                                    }
                                    return false;
                                }),
                 v4.end());
    }

    // lambda function
    // [capture list] (input parameters) -> return type { function body }
    // return type 생략 시, 컴파일러가 알아서 추론해줌
    print(v4.begin(), v4.end());
}