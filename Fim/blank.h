#ifndef BLANK_H
#define BLANK_H

#include "piece.h"

class Blank: public Piece
{
public:
    Blank();
    void blanked(bool blank);
};

#endif // BLANK_H
