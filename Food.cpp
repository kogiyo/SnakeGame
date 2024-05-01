#include "Food.h"
#include "stdlib.h"
#include "widget.h"

Food::Food(Snake* snake)
{
    this->x = (arc4random() % (MAP_WIDTH / snake->size)) * snake->size;
    this->y = (arc4random() % (MAP_HEIGHT / snake->size)) * snake->size;
}
