#ifndef SNAKE_H
#define SNAKE_H

#define MAX_SNAKE_SIZE 256

struct Point{
    int x;
    int y;
};

enum Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Snake{
public:
    Snake();
    void move();

    int length;
    int dir;
    int size;
    Point coordinate[MAX_SNAKE_SIZE];
};

#endif // SNAKE_H
