#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"
using namespace std;

class Snake{
public:
    enum class Direciton{ kUp, kDown, kLeft,kRight };
    Snake();
    Snake(int grid_width, int grid_height)
        :   head_x(grid_width/2),
            head_y(grid_height/2),
            grid_width(grid_width),
            grid_height(grid_height){}

    void Update();
    void GrowBody();
    bool SnakeCell(int x,int y);
    
    Direciton direction = Direciton::kUp;

    float speed{0.1f};
    int size{1};
    bool alive{true};
    float head_x;
    float head_y;
    vector<SDL_Point> body;

private:
    int grid_width;
    int grid_height;

    bool growing{false};

    void UpdateHead();
    void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);
};


#endif