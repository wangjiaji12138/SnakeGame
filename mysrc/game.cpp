#include "game.h"
#include <iostream>
#include "SDL.h"
using namespace std;
Game::Game(size_t grid_width, size_t grid_height)
    : snake(grid_width,grid_height),
      engine(dev()),
      random_w(0,static_cast<int>(grid_width-1)),
      random_h(0,static_cast<int>(grid_height-1)) {
    PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               size_t target_frame_duration) {
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    bool running = true;

    while(running) {
        frame_start = SDL_GetTicks();

        controller.HandleInput(running, snake);
        Update();
        renderer.Render(snake, food);

        frame_end = SDL_GetTicks();

        frame_count++;
        frame_duration = frame_end - frame_start;

        if(frame_end - title_timestamp >= 1000) {
            renderer.UpdateWindowTitle(score,frame_count);
            frame_count++;
            title_timestamp = frame_end;
        }

        if(frame_duration < target_frame_duration) {
            SDL_Delay(target_frame_duration - frame_duration);
        }
    }
}

void Game::PlaceFood() {
    int x,y;
    while(true) {
        x = random_w(engine);
        y = random_h(engine);

        if(!snake.SnakeCell(x,y)) {
            food.x = x;
            food.y = y;
            return;
        }
    }
}

void Game::Update() {
    if(!snake.alive) return;

    snake.Update();
    int new_x = static_cast<int>(snake.head_x);
    int new_y = static_cast<int>(snake.head_y);

    if(food.x == new_x && food.y == new_y) {
        score++;
        PlaceFood();
        snake.GrowBody();
        snake.speed +=0.02;
    }
}

int Game::GetScore() const { return score;}
int Game::GetSize() const { return snake.size;}