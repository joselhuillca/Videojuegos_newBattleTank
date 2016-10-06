#include "Objeto.h"

Objeto::Objeto(int x, int y, int id)
{
    //ctor
    ID_obj=id;
    pos_x = x;
    pos_y = y;

    Direction = 0;
    vida = 0;
}

Objeto::~Objeto()
{
    //dtor
}
