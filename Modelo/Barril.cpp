#include "Barril.h"

Barril::Barril(int posicion_x,int posicion_y):Modelo_Jugador(posicion_x,posicion_y)
{
   this->nombre="barril";
     this->posicion_x=posicion_x;
     this->posicion_y=posicion_y;
}

Barril::~Barril()
{
    //dtor
}
