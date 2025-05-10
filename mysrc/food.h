#ifndef FOOD_H
#define FOOD_H
#include "SDL.h"
using namespace std;


class Food{
public:
    Food(size_t grid_width, size_t grid_height)
        :   color({0x00,0x00,0x00,0xFF}),
            grid_width(grid_width),
            grid_height(grid_height){}
    int x;
    int y;
    SDL_Color color;
private:
    SDL_Point food_point;
    int grid_width;
    int grid_height;
};


#endif