#include "game.h"
#include "mainwindow.h"
#include <QEventLoop>

extern MainWindow w;

Game::Game(int n, QPixmap path)
{

    this->n = n;
    n_n = n*n;
    n_grid = n_n - 1;
    size = 420;
    dist = 5;
    float pieceSize = size/n;
    float sclDist = path.height()/(size+dist*(n-1));

    emptyP = n_grid;

    scene = new QGraphicsScene();

    scene->setSceneRect(0,0,600,600);

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(600,600);

    for(int i=0; i<n;i++){
        for(int y=0; y<n;y++){
            vec.push_back(new Piece);
            vec.at(i*n+y)->index = i*n+y;

            //vec.at(i*n+y)->setRect(0,0,pieceSize,pieceSize);
            //vec.at(i*n+y)->setScale(1/sclDist);

            vec.at(i*n+y)->setPixmap(path.copy((pieceSize + dist)*y*sclDist,(pieceSize + dist)*i*sclDist,pieceSize*sclDist,pieceSize*sclDist));
            vec.at(i*n+y)->setScale(1/sclDist);

            vec.at(i*n+y)->setPos(90+(pieceSize+dist)*y - (dist*floor(n/2)),110+(pieceSize+dist)*i - (dist*floor(n/2)));

            //vec.at(i*n+y)->setBrush(QColor(100 +(35)*y, 63+ (35)*i, 110, 255));

            scene->addItem(vec.at(i*n+y));
        }
    }

    scene->removeItem(vec.at(n_grid));

    myTimer = new MyTimer();
    myTimer->setPos(myTimer->x()+450, myTimer->y()+10);
    scene->addItem(myTimer);

    moves = new Moves();
    moves->setPos(moves->x()+10, moves->y()+10);
    scene->addItem(moves);

    blanky = new Blank;
    //blanky->setRect(0,0,500,500);
    //blanky->setBrush(QColor(235,235,235,255));
}

void Game::checkVec()
{
    checked.clear();
    for (int i = 0; i < n_n; i++){
        bool b_a = ((i % this->n) == this->emptyP%this->n) && (floor(i/this->n) + 1 == floor(this->emptyP/this->n));
        bool b_b = ((i % this->n) == this->emptyP%this->n) && (floor(i/this->n) - 1 == floor(this->emptyP/this->n));
        bool b_c = ((i % this->n) + 1 == this->emptyP%this->n) && (floor(i/this->n) == floor(this->emptyP/this->n));
        bool b_d = ((i % this->n) - 1 == this->emptyP%this->n) && (floor(i/this->n) == floor(this->emptyP/this->n));

        if(b_a || b_b || b_c || b_d){
            checked.push_back(vec.at(i));
        }
    }
}

void Game::mixIt(int moves)
{
    QEventLoop loop;
    QTimer::singleShot(4200,&loop,&QEventLoop::quit);
    loop.exec();
    blanky->blanked(true);

    for(int i = 0; i < moves; i++){
        checkVec();
        int r = floor(rand() % checked.size());
        for(unsigned int in= 0; in < vec.size(); in++){
            if(vec.at(in) == checked.at(r)){
                this->vec.at(in)->swapp(in);
                break;
            }
        }
    }

    QEventLoop loop1;
    QTimer::singleShot(2000,&loop1,&QEventLoop::quit);
    loop1.exec();
    blanky->blanked(false);

    started = true;
}

bool Game::winCondicion()
{
    if(started){
        int rightPlaces = 0;
        for(int i =0; i < n_n; i++){
            if(vec.at(i)->index == i)
                rightPlaces++;
        }
        if(rightPlaces == n_n){
            qDebug() << "Win!";
            scene->addItem(vec.at(n_grid));
            winned = true;

            QEventLoop loop2;
            QTimer::singleShot(3000,&loop2,&QEventLoop::quit);
            loop2.exec();

            this->close();

            return true;
        }else{
            return false;
        }
    }
    return false;
}
