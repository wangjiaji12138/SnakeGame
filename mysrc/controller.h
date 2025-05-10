#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
public:
    void HandleInput(bool &running, Snake &snake) const;

private:
    void ChangeDirection(Snake &snake, Snake::Direciton input, Snake::Direciton opposite) const;
};

#endif