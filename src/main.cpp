
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
#include "../lib/Logger.h"

Logger logger = Logger();

int main( int argc, char* args[] )
{
   
     logger.log("info","inicia programa");
     Modelo* modelo=new Modelo();
     //Modelo_Jugador* jugador=modelo->getModeloJugador();
     //VistaMono *vistaMono = new vistaMono(jugador);


  //Modelo* modelo=new Modelo();
    // Modelo_Jugador* jugador=modelo->getModeloJugador();
     Controlador controlador(modelo);
    Vista* vista=new Vista(modelo);
    vista->init();
    vista->loadMedia();
    //
    Modelo_Jugador* mario=modelo->getModeloJugador(7);
    //

    int quit=0;

    //SDL_Event e;
    while(quit!=1){
        while(controlador.desencolarEvento()!=0){
            //
            quit= controlador.descifrarEvento();
            mario->traducirTecla(quit);
            mario->mover();
            mario->imprimirPosicion();
            mario->imprimirVelocidad();
            modelo->acciones();
            vista->render();

         }
            mario->aplicarGravedad();
            mario->mover();
            modelo->acciones();
             vista->render();
            //modelo->getModeloJugador(0)->caminar();


            //modelo->getMono()->caminar();
            printf("Evento numero: %d\n",modelo->getModeloJugador(0)->getFrame());


    }
    /*Test unTest;
    //unTest.testearMovimiento();
    unTest.testearCreacionVistaMario();*/
    return 0;

}
