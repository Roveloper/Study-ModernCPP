#include <iostream>
#include <fstream>
#include <string>

int main() {
  std::ifstream in("test.txt");

  if (!in.is_open()) {
    std::cout << "파일을 찾을 수 없습니다!" << std::endl;
    return 0;
  }

  std::string s;
  while (in) {
    getline(in, s); // std::string에 정의되어 있으며, istream 객체를 첫번째 인자로 받고, 두번째로 입력 받은 문자열을 저정할 string 객체를 받음 (버퍼의 크기를 지정하지 않아도 되는 장점이 있음), 알아서 개행문자 또는 파일의 끝이 나올 때 까지 읽어들임
    std::cout << s << std::endl;
  }
  return 0;
}

// in.eof()의 경우는 while문제 사용하지 말 것 --> eof함수는 파일 위치 지시자가 파일에 끝에 도달한 이후에 true를 리턴하기 때문에, while문에서 사용하면, 파일의 끝에 도달한 이후에 한번 더 while문을 돌게 됨 (따라서, data에 아무것도 없는 상태로 한번을 더 돌 수 있음)
// 따라서 while(in.eof()) 와 같은 형식 대신, while(in)을 사용하는 것이 좋음 (실제로 in의 경우, 읽을 수 있는 상태에서만 true를 리턴하기 때문에, while(in)을 사용하면, 파일의 끝에 도달한 이후에는 false를 리턴하므로, while문을 빠져나감