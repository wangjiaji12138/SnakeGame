#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "snake.h"
#include "food.h"
#include "SDL.h"
#include "SDL_ttf.h"
using namespace std;
class Renderer {
public:
    Renderer(const size_t screen_width, const size_t screen_height,
             const size_t grid_width, const size_t grid_height);
    ~Renderer();
    void Render(Snake const &snake, Food const &food);
    void RenderGameOver(int score, int size);
    void UpdateWindowTitle(int score, int fps);
    
    void InitTTF();
    void CloseTTF();

private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;
    TTF_Font *font;
    string fontFilePath {"/System/Library/Fonts/Supplemental/AppleGothic.ttf"};
    const size_t screen_width;
    const size_t screen_height;
    const size_t grid_width;
    const size_t grid_height;
};
#endif