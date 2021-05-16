#include "Modelo.h"
#define persona 0
#define persona2 1
#define mono 2
#define fondo 3
#define fueguito1 4
#define fueguito2 5
#define fuegoPiso 6
#define mario 7


#include "../Modelo/Modelo.h"
#include "../Modelo/Mario.h"

#include "../Modelo/FactoryPersonaje.h"

Modelo::Modelo()
{   this->jugador= new Modelo_Jugador();
//    this->mono=new Mono();
this->modelosPersonajes=std::vector<Modelo_Jugador*>();
this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("fondo"));
this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("jugador",300,50));
this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("jugador",500,20));
this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("mono",250,100));

this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("fueguito",150,100));
this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("fueguito",0,100));
this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("fuegopiso",350,100));
this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("mario",350,350));
this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("mono",500,150));
this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("mono",120,105));
this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("mono",400,100));


}

Modelo::~Modelo()
{
    //dtor
}





Modelo_Jugador* Modelo::getModeloJugador(int posicion)
{
    return  this->modelosPersonajes[posicion] ;

}


int Modelo::getCantJugadores( )
{
    return  this->modelosPersonajes.size();

}


void Modelo::acciones()
{


    for (int i = 0; i < modelosPersonajes.size(); i++) {
      this->modelosPersonajes[i]->caminar() ;


        if  ( this->modelosPersonajes[i]->getNombre()=="mario")
        {
        this->modelosPersonajes[mario]->fijarAnimacionMovimiento();
        }

        }

}





