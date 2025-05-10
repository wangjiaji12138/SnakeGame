#include "colour.h"


Randomizer Colour::random_color(0, 7);

SDL_Color Colour::ToSDLColor(clr colour) {
    static const std::array<SDL_Color, 7> sdlColours = {{
        {255,   0,   0, 255},    // Red
        {255, 165,   0, 255},    // Orange
        {255, 255,   0, 255},    // Yellow
        {0,   255,   0, 255},    // Green
        {0,   191, 255, 255},    // Cerulean
        {0,     0, 255, 255},    // Blue
        {128,   0, 128, 255}     // Purple
    }};
    
    auto index = static_cast<size_t>(colour);
    if (index < sdlColours.size()) {
        return sdlColours[index];
    }
    return {0, 0, 0, 255};  // 默认黑色
}

SDL_Color Colour::RandomColor() {
    int randomIndex = random_color.RandomNum();
    clr randomClr = static_cast<clr>(randomIndex);
    return ToSDLColor(randomClr);
}