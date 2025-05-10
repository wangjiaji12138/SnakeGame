#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "food.h"
#include "randomizer.h"
#include "colour.h"
#include <random>
using namespace std;
class Game{
public:
    Game(size_t grid_width, size_t grid_height);
    void Run (Controller const &controller,Renderer &renderer,size_t target_frame_duration);
    void Over(Controller const &controller,Renderer &renderer);
    int GetScore() const;
    int GetSize() const;

private:
    random_device dev;
    mt19937 engine;

    Randomizer random_w;
    Randomizer random_h;

    Snake snake;
    Food food;

    int score{0};

    void CreateFood();
    void Update();
};


#endif