#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits.h>

class Map
{
    int         _w;
    int         _h;
    int         _n;
    int         _map_y;
    int         _start_row;
    int         _start_col;
    std::string *_map;

    public:
        Map();
        ~Map();

        int     stepCount();
        void    printAnswer(int answer);
};

Map::~Map()
{
    delete[] _map;
}

Map::Map()
{
    _map_y = 0;
    std::cin >> _w >> _h; std::cin.ignore();
    std::cin >> _start_row >> _start_col; std::cin.ignore();
    std::cin >> _n; std::cin.ignore();
    std::cerr << _h << ' ' << _n << std::endl; 
    _map = new std::string[_h * _n];
    for (int i = 0; i < _n; i++) {
        for (int j = 0; j < _h; j++) {
            std::string map_row;
            getline(std::cin, map_row);
            _map[_map_y] = map_row;
            std::cerr << _map[_map_y++] << std::endl;
        }
    }
}

int     Map::stepCount()
{
    int answer = -1;
    int min_steps = INT_MAX;

    for (int i = 0; i < _n; i++) {
        int steps = 0;
        int y = _start_row + (_h * i);
        int x = _start_col;
        while (_map[y][x] != 'T') {
            if (_map[y][x] == '>')
                x++;
            else if (_map[y][x] == '<')
                x--;
            else if (_map[y][x] == 'v')
                y++;
            else if (_map[y][x] == '^')
                y--;
            else {
                steps = min_steps;
                break ;
            }
            if (y == _start_row  + (_h * i) && x == _start_col) {
                steps = min_steps;
                break ;
            }
            steps++;
        }
        if (steps < min_steps) {
            min_steps = steps;
            answer = i;
        }
    }
    return answer;
}

void    Map::printAnswer(int answer)
{
    if (answer != -1)
        std::cout << answer << std::endl;
    else
        std::cout << "TRAP" << std::endl;
}

int main()
{
    Map s_map;

    s_map.printAnswer(s_map.stepCount());
}
