#include "ui.h"
#include <iostream>
#include <cstring>
#include <windows.h>

using namespace std;

bool UI::Title()
{
    bool start_detect = false;
    cout << "Maze Runner game" << endl; // title 크게 만들어야 함
    Sleep(5000); //5초 대기
    cout << "Loading...." << endl; //Loding
    Sleep(5000);

    start_detect = true;
    return start_detect;
}

//게임동안 시간을 재야함
