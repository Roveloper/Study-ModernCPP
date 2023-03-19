#include <iostream>
#include <string>

int main() {
    std::u32string u32_str = U"이건 UTF-32 문자열";
    std::cout << u32_str.size() << std::endl;

    std::string u8_str =
        u8"이건 UTF-8 문자열"; // 한글은 3바이트, 그 외는 1바이트 사용 3 * 5 + 1 * 7 = 22
    std::cout << u8_str.size() << std::endl;

    size_t i = 0;
    size_t len = 0;

    while (i < u8_str.size()) {
        int char_size = 0;

        if ((u8_str[i] & 0b11111000) == 0b11110000) {
            char_size = 4;
        } else if ((u8_str[i] & 0b11110000) == 0b11100000) {
            char_size = 3;
        } else if ((u8_str[i] & 0b11100000) == 0b11000000) {
            char_size = 2;
        } else if ((u8_str[i] & 0b10000000) == 0b00000000) {
            char_size = 1;
        } else {
            std::cout << "이상한 문자 발견!" << std::endl;
            char_size = 1;
        }

        std::cout << u8_str.substr(i, char_size) << std::endl;

        i += char_size;
        len++;
    }
    std::cout << "문자열의 실제 길이 : " << len << std::endl;

    std::u16string u16_str = u"이건 UTF-16 문자열 입니다";
    std::cout << u16_str.size() << std::endl;

    u16_str = u"안녕하세요 환영합니다";
    std::string jaum[] = {"ㄱ", "ㄲ", "ㄴ", "ㄷ", "ㄸ", "ㄹ", "ㅁ", "ㅂ", "ㅃ", "ㅅ",
                          "ㅆ", "ㅇ", "ㅈ", "ㅉ", "ㅊ", "ㅋ", "ㅌ", "ㅍ", "ㅎ"};

    for (char16_t c : u16_str) {
        if (!(0xAC00 <= c && c <= 0xD7A3)) { // 유니코드 기준 한글의 범위
            continue;
        }

        int offset = c - 0xAC00;          // 시작 위치가 0xAC00
        int jaum_offset = offset / 0x24C; // 0x24C = 588, 한 초성당 588개의 자음이 있음
        std::cout << jaum[jaum_offset];
    }

    u16_str = u"🍑🍒";
    std::cout << u16_str.size() << std::endl; // 실제 문자열의 길이와 다를 수 있음
}