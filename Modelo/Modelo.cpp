#include "Modelo.h"

Modelo::Modelo()
{   this->jugador= new Modelo_Jugador();
//    this->mono=new Mono();

}

Modelo::~Modelo()
{
    //dtor
}





Modelo_Jugador* Modelo::getModeloJugador()
{
    return  this->jugador ;

}



Mono* Modelo::getMono()
{
    return  this->mono;

}

