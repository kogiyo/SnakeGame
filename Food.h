#ifndef FOOD_H
#define FOOD_H

#include "Snake.h"

class Food{
public:
    Food(Snake* snake);
    void placeFood(Snake* snake);
    bool inSnake(Snake* snake);
    int x;
    int y;
};

#endif // FOOD_H
