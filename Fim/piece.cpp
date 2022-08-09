#include "piece.h"
#include "game.h"
#include <QDebug>

extern Game * game;

Piece::Piece(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{

}

void Piece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->type() == QGraphicsSceneMouseEvent::GraphicsSceneMousePress && game->started && !game->winned)
    {
        //qDebug() << "Mouse Pressed ";
        this->checkNeighbor();
    }
}

void Piece::checkNeighbor()
{
    game->checkVec();

    bool swappable = false;
    int temp_i = -1;

    for(unsigned int i= 0; i < game->checked.size(); i++){
        if(game->checked.at(i) == this)
            swappable = true;
    }

    for(unsigned int i= 0; i < game->vec.size(); i++){
        if(game->vec.at(i) == this)
            temp_i = i;
    }

    if(swappable){
        swapp(temp_i);
//        qDebug() << "Swapped!";
    }else{
//        qDebug() << "Invalido!";
    }
}

void Piece::swapp(int in)
{
    swap(game->vec.at(in),game->vec.at(game->emptyP));

    QPointF temp = game->vec.at(in)->pos();
    game->vec.at(in)->setPos(game->vec.at(game->emptyP)->pos());
    game->vec.at(game->emptyP)->setPos(temp);

    game->emptyP = in;

    if(game->started)
    game->moves->increase();

    game->winned = game->winCondicion();

}
