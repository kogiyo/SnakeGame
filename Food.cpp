#include "Food.h"
#include "stdlib.h"
#include "widget.h"

Food::Food(Snake* snake){
    this->x = (arc4random() % (MAP_WIDTH / snake->size)) * snake->size;
    this->y = (arc4random() % (MAP_HEIGHT / snake->size)) * snake->size;
    this->placeFood(snake);
}

void Food::placeFood(Snake *snake){
    int beforeX = this->x;
    int beforeY = this->y;
    do{
        this->x = (arc4random() % (MAP_WIDTH / snake->size)) * snake->size;
        this->y = (arc4random() % (MAP_HEIGHT / snake->size)) * snake->size;
    }while((this->x == beforeX && this->y == beforeY) or this->inSnake(snake));
}

bool Food::inSnake(Snake *snake){
    for(int i = 0; i < snake->length-1; i++){
        if(snake->coordinate[i].x == this->x && snake->coordinate[i].y == this->y){
            return true;
        }
    }
    return false;
}
