#include "game.h"
#include <iostream>
#include "SDL.h"
using namespace std;
Game::Game(size_t grid_width, size_t grid_height)
    : snake(grid_width,grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      food(grid_width,grid_height){
    CreateFood();
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

void Game::Over(Controller const &controller, Renderer &renderer) {
    renderer.InitTTF();
    Uint32 start_timestamp = SDL_GetTicks();
    while(SDL_GetTicks() - start_timestamp < 3000){
        renderer.RenderGameOver(score, snake.size);
        SDL_Delay(16);
    }
    
    // renderer.~Renderer();
}

void Game::Update() {
    if(!snake.alive) return;

    snake.Update();
    int new_x = static_cast<int>(snake.head_x);
    int new_y = static_cast<int>(snake.head_y);

    if(food.x == new_x && food.y == new_y) {
        score++;
        CreateFood();
        snake.GrowBody();
        snake.speed +=0.02;
    }
}

void Game::CreateFood() {
    int x,y;
    while(true) {
        x = random_w.RandomNum();
        y = random_h.RandomNum();

        if(!snake.SnakeCell(x,y)) {
            food.x = x;
            food.y = y;
            food.color = Colour::RandomColor();
            return;
        }
    }
}

int Game::GetScore() const { return score;}
int Game::GetSize() const { return snake.size;}