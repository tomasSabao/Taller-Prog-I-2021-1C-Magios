#include "Fondo.h"

Fondo::Fondo(int posicion_x,int posicion_y):Modelo_Jugador(posicion_x,posicion_y)
{
     this->nombre="fondo";
     this->posicion_x=posicion_x;
     this->posicion_y=posicion_y;
}

Fondo::~Fondo()
{
    //dtor
}


void Fondo::caminar()
{


            this->frames = 0;



}

