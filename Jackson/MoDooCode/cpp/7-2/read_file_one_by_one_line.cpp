// getline 으로 읽어들이기
#include <fstream>
#include <iostream>
#include <string>

int main() {
  // 파일 읽기 준비
  std::ifstream in("test.txt");
  char buf[100];

  if (!in.is_open()) {
    std::cout << "파일을 찾을 수 없습니다!" << std::endl;
    return 0;
  }

  while (in) {
    in.getline(buf, 100); // buf에 최대 99글자까지 읽어서 저장, 만약 '\n'을 만나면 그 전까지만 읽어들임
    // in.getline(buf, 100, '-'); // 위와 동일하지만 '\n'이 아닌, '-'을 만나면 멈추도록 할 수 있음
    // 하지만 in.getline 함수의 경우, 지정한 버퍼를 읽었는데도 '\n'이나, 지정한 구분자를 만나지 못하면, 버퍼를 다 채우고, failbit를 켜버리므로, 크기 제한 조건이 있습니다.
    std::cout << buf << std::endl;
  }

  return 0;
}