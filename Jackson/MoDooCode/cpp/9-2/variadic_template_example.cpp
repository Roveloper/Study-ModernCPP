#include <cstring>
#include <iostream>
#include <string>

template <typename T> void print(T arg) { std::cout << arg << std::endl; }

template <typename T, typename... Types> void print(T arg, Types... args) {
    std::cout << arg << " , ";
    print(args...);
}
// 순서를 반대로하면, 마지막 호출에서 print(arg)를 찾을 수 없어서 컴파일 오류가 발생합니다.

size_t GetStringSize(const char *s) { return strlen(s); }
size_t GetStringSize(const std::string &s) { return s.size(); }

template <typename String, typename... Strings>
size_t GetStringSize(const String &s, Strings... strs) {
    return GetStringSize(s) + GetStringSize(strs...);
}

template <typename String> std::string StrCat(const String &s) { return std::string(s); }

void AppendToString(const std::string &concat_str) { return; }

template <typename String, typename... Strings>
void AppendToString(std::string &concat_str, const String &s, Strings... strs) {
    concat_str.append(s);
    AppendToString(concat_str, strs...);
}

template <typename String, typename... Strings>
std::string StrCat(const String &s, Strings... strs) {
    std::string result = std::string(s);
    result.reserve(GetStringSize(s, strs...));
    AppendToString(result, strs...);
    return result;
}

int main() {
    print(1, 3.1, "abc");
    print(1, 2, 3, 4, 5, 6, 7);

    std::cout << StrCat(std::string("this"), " ", "is", " ", std::string("a"), " ",
                        std::string("sentence"))
              << std::endl;

    return 0;
}