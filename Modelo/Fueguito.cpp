#include "Fueguito.h"

Fueguito::Fueguito(int posicion_x,int posicion_y):Modelo_Jugador(posicion_x,posicion_y)
{
     this->nombre="fueguito";
     this->posicion_x=posicion_x;
     this->posicion_y=posicion_y;
}

Fueguito::~Fueguito()
{
    //dtor
}

void Fueguito::moverDer()

{
    this->posicion_x+=1;// el 2 seria la velocidad , si queres mas velocidad, entonces aumentas
}


void Fueguito::moverIz()

{
    this->posicion_x-=1;// el 2 seria la velocidad , si queres mas velocidad, entonces aumentas
}

void Fueguito::caminar()
{

this->setearEpilepsia(35,5);
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
            this->moverDer();
            if(this->posicion_x<0  )
         {
          this->moverDer();
         }else if( this->posicion_x>770)
          {
          this->moverIz();
          }
        }
     else if(this->frames / this->getCantFrameActualizar() ==1)//frame 1
     {

        this->moverIz();
         if(this->posicion_x<0  )
         {
          this->moverDer();
         }else if( this->posicion_x>770)
          {
          this->moverIz();
          }

     }else if(this->frames / this->getCantFrameActualizar() ==2)//frame 2
     {      this->moverDer();
     if(this->posicion_x<0  )
         {
          this->moverDer();
         }else if( this->posicion_x>770)
          {
          this->moverIz();
          }
          //this->posicion_x=0;
     }
     else if(this->frames / this->getCantFrameActualizar() ==3)//frame 2
     {
          //this->posicion_x=0;
          this->moverIz();
          if(this->posicion_x<0  )
         {
          this->moverDer();
         }else if( this->posicion_x>770)
          {
          this->moverIz();
          }
     }
     else if (this->frames / this->getCantFrameActualizar() >= 4)//me pase del los frame en el cual tengo los sprite entonces reseteo el frame
     {
        this->frames = 0;
         //this->mover();

     }


    this->frames+= 1;
}
