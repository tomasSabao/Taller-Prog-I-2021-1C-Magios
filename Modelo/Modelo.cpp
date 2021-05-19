#include "Modelo.h"
#define persona 0
#define persona2 1
#define mono 2
#define fondo 3
#define fueguito1 4
#define fueguito2 5
#define fuegoPiso 6
#define mario 7

#include <random>
#include <iostream>
#include <math.h>
#include "../Modelo/Modelo.h"
#include "../Modelo/Mario.h"
#include "../Modelo/FactoryPersonaje.h"
#include "../Modelo/Modelo_Plataforma.h"

Modelo::Modelo()
{


this->jugador= new Modelo_Jugador();
//    this->mono=new Mono();
//this->modelosPersonajes=std::vector<Modelo_Jugador*>();
this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("fondo"));

//this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("jugador",300,50));
//this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("jugador",500,20));
this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("fuegopiso",250,510));
this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("fuegopiso",500,510));

this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("mario",350,350));
this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("mono",500,12));








}

Modelo::~Modelo()
{
    //dtor
}

void Modelo::escenario2(int cantidad_fueguitos)
{
printf("Entre al esceneraio %d\n",modelosPersonajes.size());


 this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("barril",100,0));
this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("barril",200,0));

this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("barril",450,0));
this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("barril",0,0));



//meto cuatro plataformas que se mueven a izquierda
this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("plataforma",50,290));
this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("plataforma",130,290));
this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("plataforma",220,290));
this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("plataforma",300,290));

//meto una plataforma que se mueve a derecha
this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("plataforma_derecha",50,310));
     for (int i = 0; i < modelosPersonajes.size(); i++) {



        printf("nombre %s", this->modelosPersonajes[i]->getNombre().c_str());
        if(this->modelosPersonajes[i]->getNombre()=="fueguito"){
         this->modelosPersonajes[i]->setPosicionX(10000);
         this->modelosPersonajes[i]->setPosicionY(10000);

        }

        }


int posiciones_x[cantidad_fueguitos]={};
int posiciones_y[cantidad_fueguitos]={};
//esto es para la aleatoriedad
std::random_device rd_x;
std::random_device rd_y;
std::uniform_int_distribution<int> dist_x(0, 700);
std::uniform_int_distribution<int> dist_y(0, 500);

int posicion_x_aleatoria;
int posicion_y_aleatoria;
int i = 0;
int cantidad_fueguitos_generados = 0;
int dist=0;

while(i<cantidad_fueguitos){
    posicion_x_aleatoria=dist_x(rd_x);
    posicion_y_aleatoria=dist_y(rd_y);
    dist = 0;
    while(dist<cantidad_fueguitos_generados){
        if((sqrt(pow(posicion_x_aleatoria-posiciones_x[dist],2)+pow(posicion_y_aleatoria-posiciones_y[dist],2)) <= 40) || (sqrt(pow(posicion_x_aleatoria-500,2)+pow(posicion_y_aleatoria-12,2)) <= 130)){
            posicion_x_aleatoria=dist_x(rd_x);
            posicion_y_aleatoria=dist_y(rd_y);
            dist=-1;
        }
        dist++;
    }
    posiciones_x[i] = posicion_x_aleatoria;
    posiciones_y[i] = posicion_y_aleatoria;
    this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("fueguito",posicion_x_aleatoria,posicion_y_aleatoria));
    i++;
    cantidad_fueguitos_generados++;
}


printf("Entre al esceneraio %d\n",modelosPersonajes.size());

}



void Modelo::escenario1(int cantidad_fueguitos)


{


int posiciones_x[cantidad_fueguitos]={};
int posiciones_y[cantidad_fueguitos]={};
//esto es para la aleatoriedad
std::random_device rd_x;
std::random_device rd_y;
std::uniform_int_distribution<int> dist_x(0, 700);
std::uniform_int_distribution<int> dist_y(0, 500);

int posicion_x_aleatoria;
int posicion_y_aleatoria;
int i = 0;
int cantidad_fueguitos_generados = 0;
int dist=0;

while(i<cantidad_fueguitos){
    posicion_x_aleatoria=dist_x(rd_x);
    posicion_y_aleatoria=dist_y(rd_y);
    dist = 0;
    while(dist<cantidad_fueguitos_generados){
        if((sqrt(pow(posicion_x_aleatoria-posiciones_x[dist],2)+pow(posicion_y_aleatoria-posiciones_y[dist],2)) <= 40) || (sqrt(pow(posicion_x_aleatoria-500,2)+pow(posicion_y_aleatoria-12,2)) <= 130)){
            posicion_x_aleatoria=dist_x(rd_x);
            posicion_y_aleatoria=dist_y(rd_y);
            dist=-1;
        }
        dist++;
    }
    posiciones_x[i] = posicion_x_aleatoria;
    posiciones_y[i] = posicion_y_aleatoria;
    this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("fueguito",posicion_x_aleatoria,posicion_y_aleatoria));
    i++;
    cantidad_fueguitos_generados++;
}




printf("Entre al esceneraio%d\n",cantidad_fueguitos);
 //this->modelosPersonajes=std::vector<Modelo_Jugador*>();




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


        if  ( this->modelosPersonajes[i]->getNombre()=="barril")
        {

        this->modelosPersonajes[i]->caminar() ;

        }else if  ( this->modelosPersonajes[i]->getNombre()=="mario")
        {
        this->modelosPersonajes[i]->fijarAnimacionMovimiento();
        }else
        {
        this->modelosPersonajes[i]->caminar() ;

        if(this->modelosPersonajes[i]->getNombre()=="fueguito"){
            if(this->contador<300){
            this->modelosPersonajes[i]->setPosicionX(this->modelosPersonajes[i]->getPosicionX()+1);
        }
        else{
            this->modelosPersonajes[i]->setPosicionX(this->modelosPersonajes[i]->getPosicionX()-1);
        }
            if (this->contador>600){
                this->contador = 0;
            }

        }

        //condicion para la plataforma
        if(this->modelosPersonajes[i]->getNombre()=="plataforma"){
            this->modelosPersonajes[i]->caminar2();
        }
        if(this->modelosPersonajes[i]->getNombre()=="plataforma_derecha"){
            this->modelosPersonajes[i]->caminar2();
        }
        this->contador = this->contador+1;
    }


}

}
