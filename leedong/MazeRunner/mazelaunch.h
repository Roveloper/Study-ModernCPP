#ifndef MAZELAUNCH_H
#define MAZELAUNCH_H
#include <windows.h>
#include <stdio.h>

class MazeLaunch
{
public:
    void Initial(void);
    void MoveCurSor(int x, int y);
    void ClearScreen(void);

    void Clear(void);
    void Draw(void);

    void DrawPlayer(void);
    void InitObject(void);
    void PlayerAction(void);

    void Block(void);
    void Load_map(void);
};

#endif // MAZELAUNCH_H
