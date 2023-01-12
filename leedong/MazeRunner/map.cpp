#include "map.h"
#include <iostream>
#include <fstream>

using namespace std;

vector <vector<char>> Map::load(const char *fname, vector <vector<char>> map)
{
//    int height = 10;
//    int width = 20;

//    vector<vector<int>> map(height,vector<int>(width)); // map size

    ifstream fin(fname);
    if(!fin)
    {
        cout << fname << "not open" << endl;
    }

    int c;
    int j = 0;
    int i = 0;
    while((c=fin.get()) != EOF)
    {
        if ('1' == (char)c) { map[i][j] = ' '; /*cout << " ";*/ }

        else if ('0' == (char)c) { map[i][j] = 'B'; /*cout << "B";*/ }

        else if ('5' == (char)c) { map[i][j] = 'S'; /*cout << "S";*/ } // 시작 지점

        else if ('9' == (char)c) { map[i][j] = 'G'; /*cout << "G";*/ } // 끝 지점

        else cout << (char)c;
        j++;
        if (20==j)
        {j=0; i++;}
    }
    fin.close();

    return map;
}

