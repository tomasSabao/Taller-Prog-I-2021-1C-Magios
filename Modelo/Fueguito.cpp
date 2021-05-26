#include "Fueguito.h"

Fueguito::Fueguito(int posicion_x,int posicion_y):Modelo_Jugador(posicion_x,posicion_y)
{
     this->nombre="fueguito";
     this->posicion_x=posicion_x;
     this->posicion_y=posicion_y;
}

Fueguito::~Fueguito()
{
    //dtor
}
