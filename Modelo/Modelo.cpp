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


this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("mario",350,350));
this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("mono",500,12));








}

Modelo::~Modelo()
{
    //dtor
}

void Modelo::escenario2(std::string tipo_enemigo, int cantidad_fueguitos)
{
printf("Entre al esceneraio %d\n",modelosPersonajes.size());


 this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("barril",100,0));
this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("barril",200,0));

this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("barril",450,0));
this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("barril",0,0));


this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("fuegopiso",170,510));
this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("fuegopiso",315,510));
this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("fuegopiso",460,510));
this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("fuegopiso",610,510));
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
        
        if(this->modelosPersonajes[i]->getNombre()=="fueguito-default"){
         this->modelosPersonajes[i]->setPosicionX(10000);
         this->modelosPersonajes[i]->setPosicionY(10000);

        }

         if(this->modelosPersonajes[i]->getNombre()=="mono"){
         this->modelosPersonajes[i]->setPosicionX(100);
         this->modelosPersonajes[i]->setPosicionY(70);

        }



        }


int posiciones_x[cantidad_fueguitos]={};
int posiciones_y[cantidad_fueguitos]={};

int plataformas_y[5]={155,420,535};
std::uniform_int_distribution<int> plat_y(0, 2);


int plataformas_x_1_inicio[2] = {200,590};
int plataformas_x_1_fin[2] = {400,620};


int plataformas_x_2_inicio[5] = {0,220,380,530,680};
int plataformas_x_2_fin[5] = {120,300,450,600,790};


int* plataformas_x [3] = {plataformas_x_1_inicio,plataformas_x_2_inicio,plataformas_x_2_inicio};


//esto es para la aleatoriedad
std::random_device rd_x;
std::random_device rd_y;
std::uniform_int_distribution<int> dist_x_1(0, 2);
std::uniform_int_distribution<int> dist_x_2(0, 4);
int plat_rand_y;
int posicion_x_aleatoria;
int posicion_y_aleatoria;
int i = 0;
int cantidad_fueguitos_generados = 0;
int dist=0;
int plataforma;
while(i<cantidad_fueguitos){
    int plataforma_aleatoria_y = plat_y(rd_y);
    posicion_y_aleatoria=plataformas_y[plataforma_aleatoria_y];
    int* plataforma_aleatoria_x=plataformas_x[plataforma_aleatoria_y];
    if (sizeof(plataforma_aleatoria_x[0]>2)){
        plataforma = dist_x_2(rd_x);
        std::uniform_int_distribution<int> distribucion_x_1(plataformas_x_2_inicio[plataforma], plataformas_x_2_fin[plataforma]);
        posicion_x_aleatoria=distribucion_x_1(rd_x);
    }
    else{
        std::uniform_int_distribution<int> distribucion_x_1(plataformas_x_1_inicio[plataforma], plataformas_x_1_fin[plataforma]);
        posicion_x_aleatoria=distribucion_x_1(rd_x);
    }

;


    dist = 0;
    while(dist<cantidad_fueguitos_generados){
        if((sqrt(pow(posicion_x_aleatoria-posiciones_x[dist],2)+pow(posicion_y_aleatoria-posiciones_y[dist],2)) <= 40) || (sqrt(pow(posicion_x_aleatoria-500,2)+pow(posicion_y_aleatoria-12,2)) <= 130)){
        int plataforma_aleatoria_y = plat_y(rd_y);
        posicion_y_aleatoria=plataformas_y[plataforma_aleatoria_y];
        int* plataforma_aleatoria_x=plataformas_x[plataforma_aleatoria_y];
        if (sizeof(plataforma_aleatoria_x[0]>2)){
            plataforma = dist_x_2(rd_x);
            std::uniform_int_distribution<int> distribucion_x_1(plataformas_x_2_inicio[plataforma], plataformas_x_2_fin[plataforma]);
            posicion_x_aleatoria=distribucion_x_1(rd_x);
        }
        else{
            std::uniform_int_distribution<int> distribucion_x_1(plataformas_x_1_inicio[plataforma], plataformas_x_1_fin[plataforma]);
            posicion_x_aleatoria=distribucion_x_1(rd_x);
            }

            dist=-1;
        }
        dist++;
    }
    posiciones_x[i] = posicion_x_aleatoria;
    posiciones_y[i] = posicion_y_aleatoria;
    this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje(tipo_enemigo,posicion_x_aleatoria,posicion_y_aleatoria));
    i++;
    cantidad_fueguitos_generados++;
}


printf("Entre al escenario %d\n",modelosPersonajes.size());

}



void Modelo::escenario1(std::string tipo_enemigo, int cantidad_fueguitos)


{


int posiciones_x[cantidad_fueguitos]={};
int posiciones_y[cantidad_fueguitos]={};
int rectas_ordenada[4] = {388,350,222,185};
double rectas_pendiente[4] = {0.06,-0.06,0.06,-0.06};


//esto es para la aleatoriedad
std::random_device rd_x;
std::random_device rd_y;
std::random_device platform;
std::uniform_int_distribution<int> dist_x(0, 700);
std::uniform_int_distribution<int> dist_platform(0,3);

int random_platform;
int posicion_x_aleatoria;
int posicion_y_aleatoria;
int i = 0;
int cantidad_fueguitos_generados = 0;
int dist=0;


while(i<cantidad_fueguitos){
    posicion_x_aleatoria=dist_x(rd_x);
    random_platform =dist_platform(platform);
    posicion_y_aleatoria=posicion_x_aleatoria*rectas_pendiente[random_platform] + rectas_ordenada[random_platform];
    dist = 0;
    while(dist<cantidad_fueguitos_generados){
        if((sqrt(pow(posicion_x_aleatoria-posiciones_x[dist],2)+pow(posicion_y_aleatoria-posiciones_y[dist],2)) <= 40) || (sqrt(pow(posicion_x_aleatoria-500,2)+pow(posicion_y_aleatoria-12,2)) <= 130)){
            posicion_x_aleatoria=dist_x(rd_x);
            posicion_y_aleatoria=posicion_x_aleatoria*rectas_pendiente[random_platform] + rectas_ordenada[random_platform];
            dist=-1;
        }
        dist++;
    }
    posiciones_x[i] = posicion_x_aleatoria;
    posiciones_y[i] = posicion_y_aleatoria;
    this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje(tipo_enemigo,posicion_x_aleatoria,posicion_y_aleatoria));
    i++;
    cantidad_fueguitos_generados++;
}




printf("Entre al escenario%d\n",cantidad_fueguitos);
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
              if(this->contador<100){
              this->modelosPersonajes[i]->setPosicionX(this->modelosPersonajes[i]->getPosicionX()+1);
              }
              else{
                  this->modelosPersonajes[i]->setPosicionX(this->modelosPersonajes[i]->getPosicionX()-1);
              }
                  if (this->contador>600){
                      this->contador = 0;
                  }
          }
          else if (this->modelosPersonajes[i]->getNombre()=="fueguito-default") {
              if(this->contador<100){
              this->modelosPersonajes[i]->setPosicionX(this->modelosPersonajes[i]->getPosicionX()+1);
              }
              else{
                  this->modelosPersonajes[i]->setPosicionX(this->modelosPersonajes[i]->getPosicionX()-1);
              }
                  if (this->contador>200){
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
