#include "Snake.h"
#include "widget.h"
#include <QDebug>

Snake::Snake(){
    size = 20;
    dir = RIGHT;
    length = 3;

    for(int i = 0; i < length; i++){
        coordinate[i].y = MAP_HEIGHT / 2;
        coordinate[length-i-1].x = size * i + MAP_WIDTH / 2;
    }
}

void Snake::move(){
    switch (this->dir) {
    case UP:{
        for(int i = 0; i < this->length-1; i++){
            this->coordinate[this->length-i-1].y = this->coordinate[this->length-i-2].y;
            this->coordinate[this->length-i-1].x = this->coordinate[this->length-i-2].x;
        }
        this->coordinate[0].y -= this->size;
        break;
    }
    case DOWN:{
        for(int i = 0; i < this->length-1; i++){
            this->coordinate[this->length-i-1].y = this->coordinate[this->length-i-2].y;
            this->coordinate[this->length-i-1].x = this->coordinate[this->length-i-2].x;
        }
        this->coordinate[0].y += this->size;
        break;
    }
    case LEFT:{
        for(int i = 0; i < this->length-1; i++){
            this->coordinate[this->length-i-1].x = this->coordinate[this->length-i-2].x;
            this->coordinate[this->length-i-1].y = this->coordinate[this->length-i-2].y;
        }
        this->coordinate[0].x -= this->size;
        break;
    }
    case RIGHT:{
        for(int i = 0; i < this->length-1; i++){
            this->coordinate[this->length-i-1].x = this->coordinate[this->length-i-2].x;
            this->coordinate[this->length-i-1].y = this->coordinate[this->length-i-2].y;
        }
        this->coordinate[0].x += this->size;
        break;
    }
    }
}
