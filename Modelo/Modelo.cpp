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

Modelo::Modelo()
{   this->jugador= new Modelo_Jugador();
//    this->mono=new Mono();
this->modelosPersonajes=std::vector<Modelo_Jugador*>();
this->modelosPersonajes.push_back( new Modelo_Jugador());
this->modelosPersonajes.push_back( new Modelo_Jugador());
this->modelosPersonajes.push_back( new Mono());
this->modelosPersonajes.push_back( new Fondo());
this->modelosPersonajes.push_back( new Fueguito());
this->modelosPersonajes.push_back( new Fueguito());
this->modelosPersonajes.push_back( new FuegoPiso());
this->modelosPersonajes.push_back( new Mario());



}

Modelo::~Modelo()
{
    //dtor
}





Modelo_Jugador* Modelo::getModeloJugador(int posicion)
{
    return  this->modelosPersonajes[posicion] ;

}


void Modelo::acciones()
{
      this->modelosPersonajes[persona]->caminar() ;
       this->modelosPersonajes[persona2]->caminar() ;
      this->modelosPersonajes[mono]->caminar() ;
      this->modelosPersonajes[fondo]->caminar() ;
      this->modelosPersonajes[fueguito1]->caminar();
       this->modelosPersonajes[fueguito2]->caminar();
        this->modelosPersonajes[fuegoPiso]->caminar();


        this->modelosPersonajes[mario]->fijarAnimacionMovimiento();


}





