#include "../Modelo/Modelo_Jugador.h"
#define WALKING_ANIMATION_FRAMES 4
Modelo_Jugador::Modelo_Jugador()
{
     this->frames=0;


}

Modelo_Jugador::~Modelo_Jugador()
{
    //dtor
}


int Modelo_Jugador::getFrame()
{
 return this->frames;
}

void Modelo_Jugador::caminar()
{
/*
    if(  this->frames / 4 >= WALKING_ANIMATION_FRAMES )
        {
            this->frames = 0;
        }
     this->frames+= 1;
*/
    this->frames++;
    this->frames=this->frames%WALKING_ANIMATION_FRAMES;
}




