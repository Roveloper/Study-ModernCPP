#pragma once

#include <iostream>
#include <Windows.h>
#include <conio.h>

using std::cout;
using std::endl;
using std::cin;

constexpr int UP = 0;
constexpr int DOWN = 1;
constexpr int LEFT = 2;
constexpr int RIGHT = 3;
constexpr int SUBMIT = 4;

class Game {
public:
    int KeyControl();
    void init();
    void titleDraw();
    void infoDraw();
    int menuDraw();
    void gotoxy(int x, int y);
};
