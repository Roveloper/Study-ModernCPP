#include <iostream>
#include <fstream>
#include <string>

int main() {
  std::ofstream out("test.txt"); //out filestream이므로, 파일에 출력하는 것, 파일이 존재하지 않을 경우, 해당 파일을 생성한 후, 성공하면 출력 (이미 존재한다면, 해당 파일의 내용이 모두 지워지고 덮어씌워짐)

  std::string s;
  if (out.is_open()) {
    out << "이걸 쓰자~~";
  }

  out.close();
  out.open("test.txt", std::ios::app); // ios::app은 기존 파일의 끝에 이어서 쓰기 append mode를 뜻하는 듯?
  // ios::binary는 이진 파일을 읽고 쓸 때 사용
  // ios::app은 파일의 끝에 이어서 쓰기
  // ios::ate는 자동으로 파일 끝에서부터 읽기 또는 쓰기를 실시 (파일을 열 때, 위치 지정자가 파일 끝에 위치하도록 함) 거의 사용할 일이 없음
  // ios::trunc는 파일을 열 때, 기존 파일의 내용을 지우고 열기 (기본 값)
  // ios::in, std::ios::out은 파일을 읽을 지, 쓸지 지정하지만 해당 값은 ifstream, ofstream을 생성할 때 모두 설정되어 있음

  if (out.is_open()) {
    out << "덧붙이기~";
  }

  return 0;
}