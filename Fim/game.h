#ifndef GAME_H
#define GAME_H

#include "piece.h"
#include "mytimer.h"
#include "moves.h"
#include "blank.h"

#include <QThread>
#include <QGraphicsScene>
#include <QWidget>
#include <QGraphicsView>
#include <iostream>
#include <QTimer>


using namespace std;

class Game: public QGraphicsView
{
public:
    Game(int n=4,QPixmap path = QPixmap(":/img/nuncaUsarAOutraImagem.jpg"));
    int n;
    QPixmap pPath;
    int n_n;
    float size;
    float dist;
    int n_grid;
    int emptyP;
    bool started = false;
    bool winned = false;
    vector <Piece*> vec;
    vector <Piece*> checked;
    QGraphicsScene * scene;
    void checkVec();
    void mixIt(int moves);
    bool winCondicion();
    MyTimer * myTimer;
    Moves * moves;
    Blank * blanky;
};

#endif // GAME_H
