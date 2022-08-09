#ifndef PIECE_H
#define PIECE_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <vector>
#include <algorithm>

using namespace std;

class Piece: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Piece(QGraphicsItem *parent = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void checkNeighbor();
    void swapp(int i);
    int index;
public slots:
};

#endif // PIECE_H
