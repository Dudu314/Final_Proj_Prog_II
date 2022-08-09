#ifndef MOVES_H
#define MOVES_H

#include <QGraphicsTextItem>
#include <QFont>

class Moves: public QGraphicsTextItem
{
    Q_OBJECT
public:
    Moves(QGraphicsItem *parent = 0);
    int moves;
    void increase();
    int getMoves();
};

#endif // MOVES_H
