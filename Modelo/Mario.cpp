#include "Mario.h"

Mario::Mario(int posicion_x,int posicion_y):Modelo_Jugador(posicion_x,posicion_y)
{
     this->nombre="mario";
     this->posicion_x=posicion_x;
     this->posicion_y=posicion_y;
}

Mario::~Mario()
{
    //dtor
}
