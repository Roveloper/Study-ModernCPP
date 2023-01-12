#include "game.h"

int Game::KeyControl() {
    // key control code
    char tmp = getchar();
    // �Է¹޴°� �и�.

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
    system("mode con cols=50 lines = 40 | title Ÿ �� �� �� ��");

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
    cout << "           Ÿ�����潺 ���ӹ��            " << endl;
    cout << "" << endl;
    cout << "�־��� ������ �̿��� Ÿ���� ��ġ" << endl;
    cout << "" << endl;
    cout << "�ð��� ���� ������ ü���� ����" << endl;
    cout << "" << endl;
    cout << "�λ��� �ѹ��̴� ����� �Ѱ� (��, ���Ͱ� 2���� ���� ���� �ƿ�)" << endl;
    cout << "" << endl;
    cout << "But ���帶�� 10��徿 ���޵Ǵµ� 0.1% Ȯ���� 1000��� ����" << endl;
    cout << "" << endl;
    cout << "�����̽��� �Է½� ����ȭ�� �̵�" << endl;

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
