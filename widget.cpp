#include "widget.h"
#include "ui_widget.h"
#include "time.h"
#include "stdlib.h"
#include <QPainter>
#include <QBrush>
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <QMessageBox>
#include <QLabel>
#include <QPushButton>
#include <QSlider>

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget){
    ui->setupUi(this);
    this->setFixedSize(MAP_WIDTH + CTRL_AREA, MAP_HEIGHT);
    this->setWindowTitle("Snake Game");
    timer = new QTimer(this);
    this->initGame();
    this->initCtrl();

    connect(timer, &QTimer::timeout, [=](){
        snake->move();

        if(snake->eatFood(food->x, food->y)){
            int beforeX = food->x;
            int beforeY = food->y;
            do{
                food->x = (arc4random() % (MAP_WIDTH / snake->size)) * snake->size;
                food->y = (arc4random() % (MAP_HEIGHT / snake->size)) * snake->size;
            }while((food->x == beforeX && food->y == beforeY) or food->inSnake(snake));

            score += 100;
            snake->grow();
        }

        if(snake->collide()){
            QMessageBox::information(this, "Message", "Your Score: " + QString::number(score));
            initGame();
            timer->stop();
            playFlag = false;
            startPauseBtn->setText("Start");
        }
        update();
    });
}

void Widget::initGame(){
    score = 0;
    snake = new Snake();
    food = new Food(snake);
    speed = 100;
}

void Widget::initCtrl(){
    startPauseBtn = new QPushButton(this);
    startPauseBtn->setGeometry(MAP_WIDTH + 50, MAP_HEIGHT - 80, 100, 60);
    startPauseBtn->setText("Start");
    QFont font;
    font.setPixelSize(22);
    startPauseBtn->setFont(font);
    connect(startPauseBtn, &QPushButton::clicked, [=](){
        if(playFlag){
            startPauseBtn->setText("Resume");
            playFlag = false;
            speed = 100;
            timer->stop();
        }else{
            startPauseBtn->setText("Pause");
            playFlag = true;
            speed -= speedCtrl->value();
            timer->start(speed);
        }
    });

    QLabel* label = new QLabel("Speed", this);
    label->setFont(font);
    label->move(MAP_WIDTH + 65, 250);

    speedCtrl = new QSlider(Qt::Horizontal, this);
    speedCtrl->setGeometry(MAP_WIDTH + 40, 300, 120, 30);
}

void Widget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawLine(MAP_WIDTH, 0, MAP_WIDTH, MAP_HEIGHT);
    QFont font;
    font.setPixelSize(30);
    painter.setFont(font);
    painter.drawText(MAP_WIDTH + 60, 50, "Score");
    painter.drawText(MAP_WIDTH + 90, 90, QString::number(this->score));

    //painter.setPen(QColor(0,0,0,0));

    for(int i = 0; i < snake->length; i++){
        int posX = snake->coordinate[i].x;
        int posY = snake->coordinate[i].y;
        if(i == 0){
            painter.setBrush(QBrush(QColor(0, 255, 0)));
            //painter.drawEllipse(posX,posY,snake->size,snake->size);
            painter.drawRect(posX, posY, snake->size, snake->size);
        }else{
            painter.setBrush(QBrush(QColor(200, 255, 200)));
            painter.drawRect(posX, posY, snake->size, snake->size);
        }
    }
    bugFlag = false;

    painter.setBrush(QBrush(Qt::red));
    painter.drawEllipse(food->x, food->y, snake->size, snake->size);
}

void Widget::keyPressEvent(QKeyEvent *event){
    //ASCII
    //w a s d == 87 65 83 68
    if(bugFlag){
        return;
    }
    switch (event->key()) {
    case 87:
        if(snake->dir != DOWN)
        snake->dir = UP;
        bugFlag = true;
        break;
    case 83:
        if(snake->dir != UP)
        snake->dir = DOWN;
        bugFlag = true;
        break;
    case 65:
        if(snake->dir != RIGHT)
        snake->dir = LEFT;
        bugFlag = true;
        break;
    case 68:
        if(snake->dir != LEFT)
        snake->dir = RIGHT;
        bugFlag = true;
        break;
    }
}

Widget::~Widget(){
    delete ui;
    delete snake;
    delete food;
}
