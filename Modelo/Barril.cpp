#include "Barril.h"

Barril::Barril(int posicion_x,int posicion_y):Modelo_Jugador(NULL,posicion_x,posicion_y)
{
   this->nombre="barril";
     this->posicion_x=posicion_x;
     this->posicion_y=posicion_y;
}

Barril::~Barril()
{
    //dtor
}

void Barril::mover()

{
    this->posicion_y+=3;// el 2 seria la velocidad , si queres mas velocidad, entonces aumentas
}
void Barril::caminar()
{

this->setearEpilepsia(30,4);
   //printf("El valor es epilepi %d.\n", this->getCantFrameActualizar());
   //printf("El valor es sdf epilepi framsfs %d.\n",  this->frames / this->getCantFrameActualizar());


   //aca los frames a mostrar
    if(  this->frames / this->getCantFrameActualizar() >= 3 )
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


   // this->frames++;
    //this->frames=this->frames%WALKING_ANIMATION_FRAMES;
}
