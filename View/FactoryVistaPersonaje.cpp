#include "FactoryVistaPersonaje.h"
#include "../View/VistaFondo.h"
#include "../View/VistaMario.h"
#include "../View/VistaMono.h"
#include "../View/VistaFueguito.h"
#include "../View/VistaFueguitoDefault.h"
#include "../View/VistaFuegoPiso.h"
#include "../View/VistaBarril.h"
#include "../View/Vista_Jugador.h"
#include "../View/Vista_Plataforma.h"
#include "../View/VistaPlataformaDerecha.h"
#include "../View/VistaFondoDos.h"

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

  }else if( nombre=="fueguito-default" )
  {
   return new VistaFueguitoDefault(this->personaje);

  }else if( nombre=="jugador" )
  {
   return new Vista_Jugador(this->personaje);

  }else if( nombre=="fondo" )
  {
   return new VistaFondo(this->personaje);

  }else if( nombre=="fondodos" )
  {
   return new VistaFondoDos(this->personaje);

  }else if( nombre=="barril" )
  {
   return new VistaBarril(this->personaje);

  }
  else if(nombre=="plataforma")
    {
      return new Vista_Plataforma(this->personaje);
    }
  else if(nombre=="plataforma_derecha"){
    return new VistaPlataformaDerecha(this->personaje);
  }
  else
  { return NULL;}
 }
