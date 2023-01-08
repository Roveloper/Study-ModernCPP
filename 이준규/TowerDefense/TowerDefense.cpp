// TowerDefense.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.

#include <iostream>
#include <Windows.h>
// 게임하는 클래스 따로, 메뉴동작 하는 클래스를 따로따로 분리
constexpr int UP = 0;
constexpr int DOWN = 1;
constexpr int LEFT = 2;
constexpr int RIGHT = 3;
constexpr int SUBMIT = 4;

//const int UP 0;
//const int DOWN 1;
//const int LEFT 2;
//const int RIGHT 3;
using std::cout;
using std::endl;
using std::cin;


int KeyControl();
void init();
void titleDraw();
void infoDraw();
int menuDraw();
void gotoxy(int, int);

int main() {
    init();
    //titleDraw();
    //menuDraw();
    // block 이 걸릴 수도 있기에 while문 사용은...
    // timeout 을 걸어줘야 일정주기로 동작가능..?
    while (1) {
        titleDraw();
        int menuCode = menuDraw();
        if (menuCode == 0) {
            //Game start enumerate 써서 0, 1, 2 커서올릴시 0, 1, 2 표시되게
            // c++ 코드를 재사용 구조화를 신경쓰기에 클래스로 분리하는걸 신경쓰면서 코드 짜기
            // 가독성, 퀄리티를 신경쓸 것.
            // https://discord.com/channels/976814963362529320/976814964117471256/1061517109487743006
        }
        else if (menuCode == 1) {
        //else if (1 == menuCode) {// l-value = 수정가능한 값(변수, 기타등등..) a=1 (o) 1=a (x)
            //Game Information
            infoDraw();
        }
        else if (menuCode == 2) {
            //Game Exit 주석으로만 알 수있다..
        }
        system("cls");
    }
    //int keyCode = KeyControl();
    //cout << keyCode;
    


    return 0;
}

void init() {
    system("mode con cols=50 lines = 40 | title 타 워 디 펜 스");
}
void titleDraw() {
    // 메뉴 만들기
    cout << "\n\n\n";
    cout << "        @@@@@@    @@@@   @       @       @    @@@@@@   @@@@@@@      " << endl;
    cout << "          @@     @    @   @     @ @     @     @        @     @      " << endl;
    cout << "          @@     @    @    @   @   @   @      @@@@@@   @@@@@@       " << endl;
    cout << "          @@     @    @     @ @     @ @       @        @    @       " << endl;
    cout << "          @@     @    @      @       @        @        @     @      " << endl;
    cout << "          @@      @@@@                        @@@@@@   @      @     " << endl;
    cout << "" << endl;
    cout << "       @@@@@   @@@@@@  @@@@@@@  @@@@@@@   @@     @   @@@@@@@   @@@@@@@       " << endl;
    cout << "       @    @  @       @        @         @ @    @   @         @             " << endl;
    cout << "       @    @  @@@@@@  @@@@@@@  @@@@@@@   @  @   @   @@@@@@@   @@@@@@@       " << endl;
    cout << "       @    @  @       @        @         @   @  @         @   @             " << endl;
    cout << "       @    @  @       @        @         @    @ @         @   @             " << endl;
    cout << "       @@@@@   @@@@@@  @        @@@@@@@   @     @@   @@@@@@@   @@@@@@@       " << endl;
    cout << "" << endl;
    cout << "" << endl;

}

int menuDraw(){
    int x = 23;
    int y = 20;
    gotoxy(x - 2, y);
    cout << ">    Game Start  ";
    gotoxy(x, y+1);
    cout << "   Game Information";
    gotoxy(x, y+2);
    cout << "   Game Exit   ";
    while (1) {
        int n = KeyControl();
        switch (n) {
        case UP: {
            if (y > 20) {
                gotoxy(x - 2, y);
                cout << " "<<endl;
                gotoxy(x - 2, --y);
                cout << ">"<<endl;
            }
            break;
        }
        case DOWN: {
            if (y < 22) {
                gotoxy(x - 2, y);
                cout << " "<<endl;
                gotoxy(x - 2, ++y);
                cout << ">"<<endl;
            }
            break;
        }


        case SUBMIT: {
            return y - 20;
        }
        }


    }


}

int KeyControl() {
    char tmp = getchar();
    // 입력받는곳 분리.

    if (tmp == 'w' || tmp == 'W') {
        return UP;
    }
    else if (tmp == 'a' || tmp == 'A') {
        return LEFT;
    }
    else if (tmp == 's' || tmp == 'S') {
        return DOWN;
    }
    else if (tmp == 'd' || tmp == 'D') {
        return RIGHT;
    }
    else if (tmp == ' ') {
        return SUBMIT;
    }
    

}
void gotoxy(int x, int y) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(consoleHandle, pos);
}

void infoDraw() {
    system("cls");
    cout << "Check" << endl;
    while (1) {
        if (KeyControl() == SUBMIT) {
            break;
        }
    }
}
// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴
