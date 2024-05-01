#ifndef WIDGET_H
#define WIDGET_H

#include "Snake.h"
#include "Food.h"
#include <QWidget>
#include <QSlider>

#define MAP_WIDTH 800
#define MAP_HEIGHT 600
#define CTRL_AREA 200

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void initGame();
    void initCtrl();
protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

    Snake* snake;
    Food* food;
    QTimer* timer;
    QSlider* speedCtrl = NULL;
    bool bugFlag = false;
    bool playFlag = false;
    int score = 0;
    int speed = 100;

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
