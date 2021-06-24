#include "FuegoPiso.h"

FuegoPiso::FuegoPiso(int posicion_x,int posicion_y):Modelo_Jugador(NULL,posicion_x,posicion_y)
{
     this->nombre="fuegopiso";
     this->posicion_x=posicion_x;
     this->posicion_y=posicion_y;
}

FuegoPiso::~FuegoPiso()
{
    //dtor
}

void FuegoPiso::caminar()
{

this->setearEpilepsia(20,4);
   //printf("El valor es epilepi %d.\n", this->getCantFrameActualizar());
   //printf("El valor es sdf epilepi framsfs %d.\n",  this->frames / this->getCantFrameActualizar());


   //aca los frames a mostrar
    if(  this->frames / this->getCantFrameActualizar() >= this->getCantFrameDelPersonaje() )
        {
            this->frames = 0;
        }


    //aca implmento el movimiento de los barriales, segun su frame, le aplico el movimiento mover

     if(  this->frames / this->getCantFrameActualizar() == 0 )//frame 0
        {
            this->mover();
        }
     else if(this->frames / this->getCantFrameActualizar() ==1)//frame 1
     {
          this->mover();
     }else if(this->frames / this->getCantFrameActualizar() ==2)//frame 2
     {
          this->mover();
     }
     else if (this->frames / this->getCantFrameActualizar() >= 3)//me pase del los frame en el cual tengo los sprite entonces reseteo el frame
     {
        this->frames = 0;
         //this->mover();

     }

    this->frames+= 1;
}
