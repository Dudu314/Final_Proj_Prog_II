#include "game.h"
#include "mainwindow.h"

#include <QTimer>
#include <QApplication>

Game * game;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.LoadDatabase("C:/Users/Eduardo Panizzon/Desktop/Database.dat");
    w.show();

//    game = new Game(5);
//    game->show();
//    game->mixIt(10);

    return a.exec();
}
