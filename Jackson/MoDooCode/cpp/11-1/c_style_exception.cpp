#include <cstdio>
#include <cstdlib>
bool func1(int *addr);
bool func2(int *addr);
bool func3(int *addr);

bool func1(int *addr) {
  if (func2(addr)) {
    // Do something
  }
  return false;
}
bool func2(int *addr) {
  if (func3(addr)) {
    // Do something
  }
  return false;
}
bool func3(int *addr) {
  addr = (int *)malloc(100000000);
  if (addr == NULL) return false;
  return true;
}
int main() {
  int *addr;
  if (func1(addr)) {
    // 잘 처리됨
  } else {
    // 오류 발생
  }
}