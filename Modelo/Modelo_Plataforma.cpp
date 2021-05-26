#include "Modelo_Plataforma.h"

Modelo_Plataforma::Modelo_Plataforma(int posicion_x,int posicion_y):Modelo_Jugador(posicion_x,posicion_y)
{
     this->nombre="plataforma";
     this->posicion_x=posicion_x;
     this->posicion_y=posicion_y;
     this->ultima_animacion=0;
     this->ultima_direccion=0;
     this->setVelocidadHorizontal(1);
     this->setVelocidadVertical(1);
     this->reducirVelocidadX();

}

Modelo_Plataforma::~Modelo_Plataforma()
{
    //dtor
}

