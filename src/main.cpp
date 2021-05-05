
//Using SDL, SDL_image, standard IO, and strings

#include <stdio.h>
#include <string>
#include "../View/Vista.h"
#include "../Modelo/Modelo.h"
#include "../include/Controlador.h"
#include "../Modelo/LTexture.h"
#include "../View/Vista_Jugador.h"
#include "../View/VistaMono.h"
#include "Test.h"




int main( int argc, char* args[] )
{
     Modelo* modelo=new Modelo();
     //Modelo_Jugador* jugador=modelo->getModeloJugador();
     //VistaMono *vistaMono = new vistaMono(jugador);


  //Modelo* modelo=new Modelo();
    // Modelo_Jugador* jugador=modelo->getModeloJugador();
     Controlador controlador(modelo);
    Vista* vista=new Vista(modelo);
    vista->init();
    vista->loadMedia();



    int quit=0;

    //SDL_Event e;
    while(quit!=1){
        while(controlador.desencolarEvento()!=0){
            quit= controlador.descifrarEvento();

         }


             vista->render();
            modelo->getModeloJugador()->caminar();
            //modelo->getMono()->caminar();
            printf("Evento numero: %d\n",modelo->getModeloJugador()->getFrame());


    }

}
