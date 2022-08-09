#include "blank.h"
#include "game.h"

extern Game * game;

Blank::Blank()
{
    this->setPixmap(QPixmap(":/img/Embaralhando copy.jpg"));
    this->setScale(0.5);
    this->setPos(50,75);
}

void Blank::blanked(bool blank)
{
    if(blank){
        game->scene->addItem(this);
    }else if(!blank){
        game->scene->removeItem(this);
    }

}
