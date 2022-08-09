#ifndef MYTIMER_H
#define MYTIMER_H

#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>


class MyTimer: public QGraphicsTextItem
{
    Q_OBJECT
public:
    MyTimer(QGraphicsItem *parent = 0);
    int time;
    int getTime();
    bool stopped = false;
public slots:
    void increaseTimer();
};

#endif // MYTIMER_H
