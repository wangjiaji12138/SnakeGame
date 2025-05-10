#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <random>
#include "SDL.h"
using namespace std;
class Randomizer{
public:
    Randomizer(int lowerBound, int upperBound)
        :   engine(dev()),
            random_distribution(lowerBound,static_cast<int>(upperBound-1)){}
            
    int RandomNum(){ return random_distribution(engine); };
private:
    random_device dev;
    // Mersenne Twister Engine
    mt19937 engine;

    uniform_int_distribution<int> random_distribution;
};
#endif