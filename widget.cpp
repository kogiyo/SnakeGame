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

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    srand(unsigned(time(NULL)));
    this->setFixedSize(MAP_WIDTH + CTRL_AREA, MAP_HEIGHT);
    this->setWindowTitle("Snake Game");
    timer = new QTimer(this);
    this->initGame();
    this->initCtrl();

    connect(timer, &QTimer::timeout, [=](){
        snake->move();

        if(snake->coordinate[0].x == food->x && snake->coordinate[0].y == food->y){
            int beforeX = food->x;
            int beforeY = food->y;
            do{
                food->x = (arc4random() % (MAP_WIDTH / snake->size)) * snake->size;
                food->y = (arc4random() % (MAP_HEIGHT / snake->size)) * snake->size;
            }while(food->x == beforeX && food->y == beforeY);

            score += 100;
            snake->length++;

            snake->coordinate[snake->length-1].y = snake->coordinate[snake->length-2].y;
            snake->coordinate[snake->length-1].x = snake->coordinate[snake->length-2].x;

        }
        for(int i = 1; i < snake->length; i++){
            if(snake->coordinate[0].x == snake->coordinate[i].x && snake->coordinate[0].y == snake->coordinate[i].y){
                QMessageBox::information(this, "Message", "Your Score: " + QString::number(score));
                initGame();
                timer->stop();
                playFlag = false;
            }
        }
        if(snake->coordinate[0].x >= MAP_WIDTH || snake->coordinate[0].x < 0 ||
            snake->coordinate[0].y >= MAP_HEIGHT || snake->coordinate[0].y < 0){
            QMessageBox::information(this, "Message", "Your Score: " + QString::number(score));
            initGame();
            timer->stop();
            playFlag = false;
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
    QPushButton* startBtn = new QPushButton(this);
    startBtn->setGeometry(MAP_WIDTH + 50, MAP_HEIGHT - 160, 100, 60);
    startBtn->setText("Start");
    QFont font;
    font.setPixelSize(22);
    startBtn->setFont(font);
    connect(startBtn, &QPushButton::clicked, [=](){
        if(playFlag){
            return;
        }
        playFlag = true;
        speed -= speedCtrl->value();
        timer->start(speed);
    });

    QPushButton* closeBtn = new QPushButton(this);
    closeBtn->setGeometry(MAP_WIDTH + 50, MAP_HEIGHT - 80, 100, 60);
    closeBtn->setText("Pause");
    closeBtn->setFont(font);
    connect(closeBtn, &QPushButton::clicked, [=](){
        playFlag = false;
        speed = 100;
        timer->stop();
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

Widget::~Widget()
{
    delete ui;
    delete snake;
    delete food;
}
