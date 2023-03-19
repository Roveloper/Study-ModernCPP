#include <iostream>
#include <string>

void* operator new(std::size_t count) {
  std::cout << count << " bytes 할당 " << std::endl;
  return malloc(count);
}

// 문자열에 "very" 라는 단어가 있으면 true 를 리턴함
bool contains_very(const std::string& str) {
  return str.find("very") != std::string::npos;
}

bool contains_very_sv(const std::string_view str) {
  return str.find("very") != std::string::npos;
}

std::string_view return_sv() {
  std::string s = "this is a string";
  std::string_view sv = s;
  return sv;
}

int main() {
  // 암묵적으로 std::string 객체가 불필요하게 생성된다.
  std::cout << std::boolalpha << contains_very("c++ string is very easy to use")
            << std::endl;

  std::cout << contains_very("c++ string is not easy to use") << std::endl; // char*를 전달했음에도 const std::string& 으로 변환되어 호출되면서, 메모리 할당이 수행됨 (속도 저하 발생)
  // 근데 그렇다고 contains_very 함수의 입력을 const char*로 변경하면, string 대신 c_str을 통해 전달해줘야하며, const char*로 변환하는 과정에서 문자열의 길이 정보를 계산해서 사용해야함
  // 따라서, 효율적인 계산을 위해서는 const std::string& 타입과 const char* 타입을 받는 두 가지 함수를 만들어야 한다는 단점이 존재함

  // 혜성같이 C++17에서 string_view가 도입되면서 해결됨 (ㅋㅋ.. 근데 C++17 안쓰는 회사들 많죠?ㅋㅋㅋ)
  std::cout << "============string view 사용 시============" << std::endl;
  std::cout << std::boolalpha << contains_very_sv("c++ string is very easy to use") << std::endl;
  std::cout << contains_very_sv("c++ string is not easy to use") << std::endl;
  std::string str = "some long long long long long long long string";
  std::cout << contains_very_sv(str) << std::endl;
  // string_view는 문자열을 "읽기"만 하는 클래스입니다. (소유하지 않기 때문에, 읽고 있는 문자열이 삭제되면 문제가 될 수 있습니다)
  // 장점으로는 읽기만 수행하므로, 메모리 할당이 불필요하며, 해당 문자열의 시작 주소값만 복사하면 됩니다.
  // 단점은 당연히, 수정이 불가능합니다. substr의 경우, string_view 타입의 새로운 substr을 생성하면서, 시작하는 위치만 복사해오면 되므로 O(1)로 수행됩니다. (string의 경우 O(n))

  std::cout <<"string -------------" << std::endl;
  std::string s = "sometimes string is very slow";
  std::cout << "---------------------" << std::endl;
  std::cout << s.substr(0, 20) << std::endl << std::endl;

  std::cout << "string view--------------" << std::endl;
  std::string_view sv = s;
  std::cout <<  "---------------------" << std::endl;
  std::cout << sv.substr(0, 20) << std::endl << std::endl;

  std::string_view sv2 = return_sv(); // 나오면서 객체는 소멸되었으므로, string_view가 보고있는 부분이 없어진 상태임

  std::cout << sv2 << std::endl;

}