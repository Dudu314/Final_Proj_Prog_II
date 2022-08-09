#include "moves.h"

Moves::Moves(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    moves = 0;

    setPlainText(QString("Moves: ") + QString::number(moves));
    setDefaultTextColor(Qt::black);
    setFont(QFont("times",18));
}

void Moves::increase()
{
    moves++;

    setPlainText(QString("Moves: ") + QString::number(moves));
    setDefaultTextColor(Qt::black);
    setFont(QFont("times",18));
}

int Moves::getMoves()
{
    return moves;
}
