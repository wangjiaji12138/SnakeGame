#ifndef COLOUR_H
#define COLOUR_H
#include <SDL.h>
#include "randomizer.h"

class Colour {
public:
    enum class clr { Red, Orange, Yellow, Green, Cerulean, Blue, Purple };
    
    static SDL_Color ToSDLColor(clr colour);
    
    static SDL_Color RandomColor();
    
    static size_t Count() { return 7; }
private:
    static Randomizer random_color;
};

#endif