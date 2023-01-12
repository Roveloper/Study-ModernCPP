#ifndef MAP_H
#define MAP_H
#include <vector>
#include <mazelaunch.h>

using namespace std;

class Map
{
public:
    vector <vector<char>> load(const char* fname, vector <vector<char>> map);
};

#endif // MAP_H
