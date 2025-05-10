#include "renderer.h"
#include <iostream>
#include <string>
using namespace std;
Renderer::Renderer(const size_t screen_width, const size_t screen_height,
                   const size_t grid_width, const size_t grid_height)
    :   screen_width(screen_width),
        screen_height(screen_height),
        grid_width(grid_width),
        grid_height(grid_height) {
    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        cerr << "SDL could not initialize.\n";
        cerr << "SDL Error: " << SDL_GetError() << "\n";
    }

    // create a window that will be shown right now and displayed at the center of the computer screen
    sdl_window =  SDL_CreateWindow("Snake Game",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    screen_width, screen_height,SDL_WINDOW_SHOWN);
    if(nullptr == sdl_window) {
        cerr << "Window could not be created.\n";
        cerr << "SDL Error: " << SDL_GetError() << "\n";
    }
    
    // create a renderer that:
    // 1.bind to our window created before,
    // 2.automatically choose the best renderer drive
    // 3.use hardware acceleration(GPU rendering)
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if(nullptr == sdl_renderer) {
        cerr << "Renderer could not be created.\n";
        cerr << "SDL Error: " << SDL_GetError() << "\n";
    }
}

Renderer::~Renderer(){
    // you'd better destroy window manually to avoid the memory leak
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

void Renderer::Render(Snake const &snake, Food const &food) {
    // clear the screen,set the backgrond clour and alpha value
    // it will repeat every frame to make sure no older element left
    SDL_SetRenderDrawColor(sdl_renderer, 0x1E,0x1E,0x1E,0xFF);
    SDL_RenderClear(sdl_renderer);

    // render food
    SDL_SetRenderDrawColor(sdl_renderer, food.color.r, food.color.g, food.color.b, food.color.a);

    // food block
    SDL_Rect block;
    block.w = screen_width / grid_width;
    block.h = screen_height / grid_height;
    // convert grid coordinates to pixel coordinates
    block.x = food.x * block.w;
    block.y = food.y * block.h;
    SDL_RenderFillRect(sdl_renderer,&block);

    // render snake's body
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF,0xFF,0xFF,0xFF);
    for(SDL_Point const &point : snake.body) {
        block.x = point.x * block.w;
        block.y = point.y * block.h;
        SDL_RenderFillRect(sdl_renderer,&block);
    }

    // render snake's head
    block.x = static_cast<int>(snake.head_x) * block.w;
    block.y = static_cast<int>(snake.head_y) * block.h;
    if(snake.alive) {
        SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
    }
    else{   // dead snake is red(laugh to dead)
        SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
    }
    SDL_RenderFillRect(sdl_renderer, &block);

    // update Screen
    SDL_RenderPresent(sdl_renderer);
}

void Renderer::InitTTF() {
    if(TTF_Init()== -1){
        cerr << "TTF could not be initialized.\n";
        cerr << "TTF Error: " << TTF_GetError() << "\n";
        return;
    }
    font = TTF_OpenFont(fontFilePath.c_str(),48);
    if(!font){
        cerr << "Could not open font file.\n";
        cerr << "TTF Error: " << TTF_GetError() << "\n";
        return;
    }
}

void Renderer::RenderGameOver(int score, int size) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x1E,0x1E,0x1E,0xFF);
    SDL_RenderClear(sdl_renderer);

    SDL_Color textClour = {0xFF, 0x00, 0x00, 0xFF};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "GAME OVER", textClour);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(sdl_renderer, textSurface);

    SDL_Rect textRect;
    textRect.w = 300;
    textRect.h = 100;
    textRect.x = (screen_width-textRect.w)/2;
	textRect.y = (screen_height-textRect.h)/2;
	


    SDL_RenderCopy(sdl_renderer, textTexture, nullptr, &textRect);
    SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score,int fps) {
    string title("Snake Score: " +to_string(score) + " FPS: " + to_string(fps));
    SDL_SetWindowTitle(sdl_window,title.c_str());
}