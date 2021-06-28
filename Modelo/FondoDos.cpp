#include "FondoDos.h"

FondoDos::FondoDos(int posicion_x,int posicion_y):Modelo_Jugador("",posicion_x,posicion_y)
{
    this->nombre="fondodos";
    this->posicion_x=posicion_x;
    this->posicion_y=posicion_y;
}

FondoDos::~FondoDos()
{
    //dtor
}


void FondoDos::caminar()
{
    this->frames = 0;

}
