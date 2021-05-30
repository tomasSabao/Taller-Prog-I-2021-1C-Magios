#include "FueguitoDefault.h"

FueguitoDefault::FueguitoDefault(int posicion_x,int posicion_y):Modelo_Jugador(posicion_x,posicion_y)
{
     this->nombre="fueguito-default";
     this->posicion_x=posicion_x;
     this->posicion_y=posicion_y;
}

FueguitoDefault::~FueguitoDefault()
{
    //dtor
}
