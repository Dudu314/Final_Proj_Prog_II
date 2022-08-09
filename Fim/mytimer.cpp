#include "mytimer.h"
#include "game.h"

extern Game * game;

MyTimer::MyTimer(QGraphicsItem *parent):QGraphicsTextItem(parent)
{
    time = 0;

    setPlainText(QString("Time: ") + QString::number(time) + QString(" s"));
    setDefaultTextColor(Qt::black);
    setFont(QFont("times",18));

    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(increaseTimer()));
    timer->start(1000);
}

int MyTimer::getTime()
{
    return time;
}

void MyTimer::increaseTimer()
{
    if(!stopped && game->started && !game->winned){
        time++;

        setPlainText(QString("Time: ") + QString::number(time) + QString(" s"));
        setDefaultTextColor(Qt::black);
        setFont(QFont("times",18));
    }
}
