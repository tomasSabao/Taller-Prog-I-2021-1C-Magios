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
#include "../lib/Parser.h"

#define CDAD_ARGUMENTOS 2
#define POS_ARCHIVO_CONFIGURACION 1

extern Logger logger;
Parser parser = Parser();

int main( int argc, char* argv[] )
{
    std::string archivo_configuracion;

    if (argc >= CDAD_ARGUMENTOS) {
        archivo_configuracion = argv[POS_ARCHIVO_CONFIGURACION];
    } else {
        archivo_configuracion = "lib/default.json";
    }

    parser.obtenerJson(archivo_configuracion);
    std::string nivel_log = parser.obtenerNivelLog();
    logger.setNivelLog(nivel_log);
    //continua el flujo

    logger.log("info","Inicio del juego.");

    std::map<std::string, std::string> enemigos = parser.obtenerEnemigos();
    std::vector<std::string> fondos = parser.obtenerFondos();

    Modelo* modelo=new Modelo();
    //Modelo_Jugador* jugador=modelo->getModeloJugador();
    //VistaMono *vistaMono = new vistaMono(jugador);

    //TODO: sacar este hardcodeo, ?hay que cambiar la imagen del enemigo cuando ponemos el tipo de enemigo por default?
    //enemigos.keys() -> la priemra key es el tipo de enemigo para nivel 1
    modelo->escenario1(std::stoi(enemigos["fuego-1"]));

    //Modelo* modelo=new Modelo();
    // Modelo_Jugador* jugador=modelo->getModeloJugador();
    Controlador controlador(modelo);
    Vista* vista=new Vista(modelo);
    vista->init();
    vista->loadMedia();
    //
    Modelo_Jugador* mario=NULL;
    for (int i = 0; i < modelo->getCantJugadores( ); i++) {

        if  (  modelo->getModeloJugador(i)->getNombre()=="mario")
        {
          mario=modelo->getModeloJugador(i);
        }

    }

    //
    int quit=0;

    //SDL_Event e;
    while(quit!=1){
        while(controlador.desencolarEvento()!=0){
            //
            quit= controlador.descifrarEvento();
            if(quit==32)
            {

            //TODO: sacar este hardcodeo, ?hay que cambiar la imagen del enemigo cuando ponemos el tipo de enemigo por default?
            //enemigos.keys() -> la priemra key es el tipo de enemigo para nivel 2
            modelo->escenario2(std::stoi(enemigos["fuego-2"]));
            vista->escenario2();
            }
            mario->traducirTecla(quit);
            mario->mover();
            mario->imprimirPosicion();
            mario->imprimirVelocidad();
            modelo->acciones();
            vista->render(quit);

         }
            mario->aplicarGravedad();
            mario->mover();
            modelo->acciones();
            vista->render(quit);
            //modelo->getModeloJugador(0)->caminar();


            //modelo->getMono()->caminar();
            //printf("Evento numero: %d\n",modelo->getModeloJugador(7)->getFrame());


    }
    /*Test unTest;
    //unTest.testearMovimiento();
    unTest.testearCreacionVistaMario();*/
    return 0;

}
