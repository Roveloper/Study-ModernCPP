#include "game.h"

int Game::KeyControl() {
    // key control code
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
    else if (tmp == 'd' || tmp == 'D') {s
        return RIGHT;
    }
    else if (tmp == ' ') {
        return SUBMIT;
    }
}

void Game::init() {
    // init code
    system("mode con cols=50 lines = 40 | title 타 워 디 펜 스");

    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConsoleCursor;
    ConsoleCursor.bVisible = 0;
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

void Game::titleDraw() {
    // title draw code
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

void Game::infoDraw() {
    // info draw code
    system("cls");
    cout << "           타워디펜스 게임방법            " << endl;
    cout << "" << endl;
    cout << "주어진 코인을 이용해 타워를 설치" << endl;
    cout << "" << endl;
    cout << "시간에 따라 몬스터의 체력이 증가" << endl;
    cout << "" << endl;
    cout << "인생은 한번이니 목숨도 한개 (즉, 몬스터가 2바퀴 도는 순간 아웃)" << endl;
    cout << "" << endl;
    cout << "But 라운드마다 10골드씩 지급되는데 0.1% 확률로 1000골드 지급" << endl;
    cout << "" << endl;
    cout << "스페이스바 입력시 메인화면 이동" << endl;

    while (1) {
        if (KeyControl() == SUBMIT) {
            break;
        }
    }
}

int Game::menuDraw() {
    // menu draw code
    int x = 24;
    int y = 20;
    gotoxy(x - 2, y);
    cout << "> Game Start  ";
    gotoxy(x, y + 1);
    cout << "Game Information";
    gotoxy(x, y + 2);
    cout << "Game Exit   ";
    while (1) {
        int n = KeyControl();
        switch (n) {

        case UP: {
            if (y > 20) {
                gotoxy(x - 2, y);
                cout << " " << endl;
                gotoxy(x - 2, --y);
                cout << ">" << endl;
            }

            break;
        }
        case DOWN: {
            if (y < 22) {
                gotoxy(x - 2, y);
                cout << " " << endl;
                gotoxy(x - 2, ++y);
                cout << ">" << endl;
            }

            break;
        }


        case SUBMIT: {
            return y - 20;
        }
        }


    }


}

void Game::gotoxy(int x, int y) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(consoleHandle, pos);
}
