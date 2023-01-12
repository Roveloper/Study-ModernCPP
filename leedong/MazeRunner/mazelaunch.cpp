#include "mazelaunch.h"
#include "map.h"
#include <fstream>
#define WIDTH  115 //창의 크기
#define HEIGHT 29
#define P_COUNT 3  // unit 크기

struct Player
{
    int x;
    int y;
};

Player g_Player;

char screen[HEIGHT][WIDTH];
char Player_Unit[P_COUNT+1] = "LDH"; //unit

HANDLE h_console;

/* 콘솔 화면 창을 초기화 하는 함수*/
void MazeLaunch::Initial(void)
{
    CONSOLE_CURSOR_INFO cs_cursor;

    cs_cursor.bVisible = FALSE; // cursor 위치를 안보이게 FALSE 설정
    cs_cursor.dwSize = 1;

    h_console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(h_console, &cs_cursor);
}

/* 매개변수 x,y의 위치에 커서를 이동시키는 함수 */
void MazeLaunch::MoveCurSor(int x, int y)
{
    COORD coord;

    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(h_console, coord);
}

/* 콘솔 화면의 전체 내용을 지우는 함수 */
void MazeLaunch::ClearScreen(void)
{
    int x, y;

    for(y = 0; y < HEIGHT; y++)
    {
        for(x = 0; x < WIDTH; x++)
        {
            // 커서 위치 옮기기
            MazeLaunch::MoveCurSor(x,y);

            // 공백문자로 덮어 씌움
            printf("%c",' ');
        }
    }
}

/* 지우는 함수로, 이차원 배열 screen에 있는 내용을 지운다. */
void MazeLaunch::Clear(void)
{
    int i;

    for(i = 0; i < HEIGHT; i++)
    {
        // 이차원 배열의 요소에 공백문자를 덮어 씌우고
        memset(screen[i], ' ', WIDTH);

        // 각 행의 맨 마지막 자리에 Null문자를 삽입한다.
        screen[i][WIDTH-1] = NULL;
    }
}

/* 그리는 함수로, 이차원 배열screen에 있는 오브젝트들을 렌더한다. */
void MazeLaunch::Draw(void)
{
    int i;

    DrawPlayer();

    for(i=0; i < HEIGHT; i++)
    {
        MoveCurSor(0, i);       // 각 행의 위치로 커서를 이동시키고
        printf(screen[i]);      // 이차원 배열의 내용을 렌더(각 행은 문자열이다.)
    }
}

/* 플레이어를 그려주는 함수로 이차원 배열screen에 플레이어를 저장한다. */
void MazeLaunch::DrawPlayer(void)
{
    int i;

    int x = g_Player.x - P_COUNT / 2; // 플레이어 캐릭터의 맨 왼쪽 x위치
    int y = g_Player.y;               // 플레이어의 캐릭터 y위치

    // 플레이어 캐릭터의 y위치가 맵을 벗어나면 이차원 배열에 저장하지 않는다.
    if(y < 0 || y >= HEIGHT) return;

    // 이차원 배열에 플레이어를 저장한다.
    for(i = 0; P_COUNT > i; i++)
    {
        // 플레이어의 가장 왼쪽서부터 맵 범위 안에 있으면 저장한다.-------------------------------------------
        if(x >= 0 && x < WIDTH)
        {
            screen[y][x] = Player_Unit[i];
        }
        x++; // 오른쪽으로 이동시키기 위해 증가 연산
    }
}

/* 초기 위치 설정 함수 */
void MazeLaunch::InitObject(void)
{
    g_Player.x = 112;
    g_Player.y = 10;
}

/* 키 입력을 통해 플레이어를 움직이는 함수 */
void MazeLaunch::PlayerAction(void)
{
    int step = 1; // step씩 이동
    if (GetAsyncKeyState(VK_LEFT)) {g_Player.x -= step;}

    if (GetAsyncKeyState(VK_RIGHT)) {g_Player.x += step;}

    if (GetAsyncKeyState(VK_UP)) {g_Player.y -= step;}

    if (GetAsyncKeyState(VK_DOWN)) {g_Player.y += step;}
}

/* 플레이어가 맵 영역을 벗어났는지 체크해서 위치를 조정하는 함수 */
void MazeLaunch::Block(void)
{
    int leftPosX = g_Player.x - P_COUNT / 2;
    int rightPosX = g_Player.x + P_COUNT;

    if (leftPosX < 0) {g_Player.x = 1;}

    if (rightPosX > WIDTH + 1) {g_Player.x = WIDTH - P_COUNT + 1;}

    if (g_Player.y < 1) {g_Player.y = 1;}

    if (g_Player.y >= HEIGHT -1) {g_Player.y = HEIGHT - 1;}

}

/* map불러오는 함수 */
void MazeLaunch::Load_map(void)
{
    vector <vector<char>> map;
    vector <vector<char>> new_map;

    for(unsigned int i=0; i<HEIGHT; i++)
    {
        for(unsigned int j=0; j<WIDTH; j++)
        {
            map[i][j] = screen[i][j];
        }
    }

    Map map_load;
    const char* file = "C:/Users/Lenovo/Documents/MazeRunner/map1.txt";
    new_map =map_load.load(file, map);

    for(unsigned int i=0; i<HEIGHT; i++)
    {
        for(unsigned int j=0; j<WIDTH; j++)
        {
            screen[i][j] = new_map[i][j];
            if (screen[i][j] != ' ')
            {printf(&screen[i][j]);}
        }
    }

}
