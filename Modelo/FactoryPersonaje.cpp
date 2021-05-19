#include "FactoryPersonaje.h"

#include "../Modelo/Mario.h"
#include "../Modelo/Mono.h"
#include "../Modelo/FuegoPiso.h"
#include "../Modelo/Barril.h"
#include "../Modelo/Modelo_Jugador.h"
#include "../Modelo/Modelo_Plataforma.h"
#include "../Modelo/ModeloPlataformaDerecha.h"
#include "../Modelo/FondoDos.h"
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

  }else if( nombre=="fondodos" )
  {
   return new FondoDos(posX,posY);

  }else if( nombre=="jugador" )
  {
   return new Modelo_Jugador(posX,posY);

  }else if( nombre=="barril" )
  {
   return new Barril(posX,posY);

  }
else if(nombre=="plataforma"){
  return new Modelo_Plataforma(posX,posY);

}else if(nombre=="plataforma_derecha"){
  return new ModeloPlataformaDerecha(posX,posY);

}
  else
  {
   return NULL;

  }


}
