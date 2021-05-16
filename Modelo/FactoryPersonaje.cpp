#include "FactoryPersonaje.h"

#include "../Modelo/Mario.h"
#include "../Modelo/Mono.h"
#include "../Modelo/FuegoPiso.h"
#include "../Modelo/Barril.h"
#include "../Modelo/Modelo_Jugador.h"
FactoryPersonaje::FactoryPersonaje()
{
    //ctor
}

FactoryPersonaje::~FactoryPersonaje()
{
    //dtor
}


Modelo_Jugador* FactoryPersonaje::getPersonaje(string nombre, int posX, int posY)
{

 if (nombre=="mario" )
 {
    return new Mario(posX,posY) ;

 }else if( nombre=="mono" )
 {
    return new Mono(posX,posY);

 }else if( nombre=="fuegopiso" )
  {
   return new FuegoPiso(posX,posY);

  }else if( nombre=="fueguito" )
  {
   return new Fueguito(posX,posY);

  }else if( nombre=="fondo" )
  {
   return new Fondo(posX,posY);

  }else if( nombre=="jugador" )
  {
   return new Modelo_Jugador(posX,posY);

  }else if( nombre=="barril" )
  {
   return new Barril(posX,posY);

  }else
  {
   return NULL;

  }


}
