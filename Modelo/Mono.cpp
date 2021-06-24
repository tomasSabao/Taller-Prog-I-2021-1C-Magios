#include "Mono.h"

Mono::Mono(int posicion_x,int posicion_y):Modelo_Jugador(NULL,posicion_x,posicion_y)
{
    this->nombre="mono";
    this->posicion_x=posicion_x;
    this->posicion_y=posicion_y;
}

Mono::~Mono()
{
    //dtor
}

void Mono::caminar()
{
   this->setearEpilepsia(30,4);
   //printf("El valor es epilepi %d.\n", this->getCantFrameActualizar());
   //printf("El valor es sdf epilepi framsfs %d.\n",  this->frames / this->getCantFrameActualizar());

    if(this->frames / this->getCantFrameActualizar() >= this->getCantFrameDelPersonaje() )
    {
        this->frames = 0;
    }

    this->frames+= 1;

    // this->frames++;
    //this->frames=this->frames%WALKING_ANIMATION_FRAMES;
}
