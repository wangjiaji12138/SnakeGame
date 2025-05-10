#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "snake.h"
#include "SDL.h"
using namespace std;
class Renderer {
public:
    Renderer(const size_t screen_width, const size_t screen_height,
             const size_t grid_width, const size_t grid_height);
    ~Renderer();

    void Render(Snake const snake, SDL_Point const &food);
    void UpdateWindowTitle(int score, int fps);

private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;

    const size_t screen_width;
    const size_t screen_height;
    const size_t grid_width;
    const size_t grid_height;
};
#endif