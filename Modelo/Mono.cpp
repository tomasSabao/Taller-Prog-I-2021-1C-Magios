#include "Mono.h"

Mono::Mono(int posicion_x,int posicion_y):Modelo_Jugador(posicion_x,posicion_y)
{
    this->nombre="mono";
    this->posicion_x=posicion_x;
     this->posicion_y=posicion_y;
}
Mono::~Mono()
{
    //dtor
}
