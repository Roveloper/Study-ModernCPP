#include <iostream>
#include "ui.h"
#include "mazelaunch.h"
//#include "map.h"

using namespace std;

int main()
{
    UI ui;
    MazeLaunch Maze;


//    ui.Title();

    Maze.Initial();

    Maze.InitObject();

    Maze.ClearScreen();

    while(true)
    {
//        Maze.Load_map();

        Maze.PlayerAction();

        Maze.Block();

        Maze.Clear();

        Maze.Draw();

        Sleep(50);

    }


    return 0;
}

// map test

/*
#include <iostream>
#include <fstream>
#include "map.h"

using namespace std;

int main()
{
    Map map_load;
    const char* file = "C:/Users/Lenovo/Documents/MazeRunner/map1.txt";
    map_load.load(file);

    return 0;
}
*/
