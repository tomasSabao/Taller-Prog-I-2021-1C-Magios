#include "Modelo.h"

Modelo::Modelo()
{   this->jugador= new Modelo_Jugador();

}

Modelo::~Modelo()
{
    //dtor
}





Modelo_Jugador* Modelo::getModeloJugador()
{
    return  this->jugador ;

}





