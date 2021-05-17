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


void Barril::caminar()
{

    if(  this->frames / 4 >= 4 )
        {
            this->frames = 0;
        }


            this->aumentarVelocidadY();
            this->mover();
            this->setGravedad(20);
             this->aplicarGravedad();

          this->frames+= 1;


   // this->frames++;
    //this->frames=this->frames%WALKING_ANIMATION_FRAMES;
}
