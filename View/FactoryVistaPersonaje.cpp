#include "FactoryVistaPersonaje.h"
#include "../View/VistaFondo.h"
#include "../View/VistaMario.h"
#include "../View/VistaMono.h"
#include "../View/VistaFueguito.h"
#include "../View/VistaFuegoPiso.h"
#include "../View/Vista_Jugador.h"
FactoryVistaPersonaje::FactoryVistaPersonaje(Modelo_Jugador* jugadores)
{
    this->personaje=jugadores;
}

FactoryVistaPersonaje::~FactoryVistaPersonaje()
{
    //dtor
}


 Vista_Jugador* FactoryVistaPersonaje::getVistaPersonaje(string nombre)
 {

    if (nombre=="mario" )
 {
    return new VistaMario(this->personaje) ;

 }else if( nombre=="mono" )
 {
    return new VistaMono(this->personaje);

 }else if( nombre=="fuegopiso" )
  {
   return new VistaFuegoPiso(this->personaje);

  }else if( nombre=="fueguito" )
  {
   return new VistaFueguito(this->personaje);

  }else if( nombre=="jugador" )
  {
   return new Vista_Jugador(this->personaje);

  }else if( nombre=="fondo" )
  {
   return new VistaFondo(this->personaje);

  }else
  { return NULL;}
 }
