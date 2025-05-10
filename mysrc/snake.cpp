#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() {
    // capture the head's cell before updating
    SDL_Point prev_cell {
        static_cast<int>(head_x),
        static_cast<int>(head_y)};
    UpdateHead();

    // capture the head's cell after updating
    SDL_Point current_cell {
        static_cast<int>(head_x),
        static_cast<int>(head_y)};
    // current_cell and prev_cell are casted by a float,maybe they will equal
    // we should make sure the head could move to a new place and update the remain body
    if(current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
        UpdateBody(current_cell,prev_cell);
    }
}

// head's coordinates + direciton
void Snake::UpdateHead(){
    switch (direction)
    {
    case Direciton::kUp:
        head_y -= speed;
        break;
    case Direciton::kDown:
        head_y += speed;
        break;

    case Direciton::kLeft:
        head_x -= speed;
        break;

    case Direciton::kRight:
        head_x += speed;
        break;

    default:
        break;
    }

    // fmod(a, b) = (a + b) % b 
    head_x = fmod(head_x + grid_width,grid_width);
    head_y = fmod(head_y + grid_height,grid_height);
}

void Snake::UpdateBody(SDL_Point& current_head_cell,SDL_Point& prev_head_cell) {
    // the prev head becomes a part of body
    body.push_back(prev_head_cell);

    // tail should be remove unless snake growing
    if(!growing) {
        body.erase(body.begin());
    }
    else {
        growing = false;
        size++;
    }
    
    // check if the snake crushed the remain body
    for(auto const &item : body) {
        if(current_head_cell.x == item.x && current_head_cell.y == item.y) {
            alive = false;
        }
    }
}

void Snake::GrowBody(){ growing = true; }

// inefficient way to check
bool Snake::SnakeCell(int x, int y){
    if(x == static_cast<int>(head_x) &&  y == static_cast<int>(head_y)){
        return true;
    }
    for(auto const &item : body){
        if(x == item.x && y == item.y){
            return true;
        }
    }
    return false;
}

// efficient way to check