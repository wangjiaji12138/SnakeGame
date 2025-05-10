#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(Snake &snake, Snake::Direciton input, Snake::Direciton opposite) const{
    // you are not allowed to return back if you are longer than 1
    if(snake.direction != opposite || snake.size==1) snake.direction = input;
    return;
}

void Controller::HandleInput(bool &running, Snake &snake) const {
    SDL_Event e;
    while(SDL_PollEvent(&e)){   // deal with an event in the queue of SDL
        if(e.type == SDL_QUIT || !snake.alive){
            running = false;
        }
        else if(e.type == SDL_KEYDOWN){
            switch (e.key.keysym.sym)
            {
            case SDLK_UP:
                ChangeDirection(snake,Snake::Direciton::kUp,Snake::Direciton::kDown);
                break;
            
            case SDLK_DOWN:
                ChangeDirection(snake,Snake::Direciton::kDown,Snake::Direciton::kUp);
                break;

            case SDLK_LEFT:
                ChangeDirection(snake,Snake::Direciton::kLeft,Snake::Direciton::kRight);
                break;

            case SDLK_RIGHT:
                ChangeDirection(snake,Snake::Direciton::kRight,Snake::Direciton::kLeft);
                break;
            default:
                break;
            }
        }
    }
}