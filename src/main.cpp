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

    if (enemigos.find("fuego-1") != enemigos.end()) {
        cout << "Se encontro fuego-1 con "<< enemigos["fuego-1"] << " enemigos" << endl;
        modelo->escenario1("fueguito", std::stoi(enemigos["fuego-1"]));
    }
    else
    {
        cout << "Se encontro fuego-default-1 con "<< enemigos["fuego-default-1"] << " enemigos" << endl;
        modelo->escenario1("fueguito-default", std::stoi(enemigos["fuego-default-1"]));
    }

    //Modelo* modelo=new Modelo();
    // Modelo_Jugador* jugador=modelo->getModeloJugador();
    Controlador controlador(modelo);
    
    Vista* vista=new Vista(modelo);

    vista->init();
    vista->loadMedia();
    //
    Modelo_Jugador* mario=NULL;
    for (int i = 0; i < modelo->getCantJugadores( ); i++) {
        
        cout << "loop de jugadores" << i << endl;

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

            if (enemigos.find("fuego-2") != enemigos.end()) {
                cout << "Se encontro fuego-2 con "<< enemigos["fuego-2"] << " enemigos" << endl;
                modelo->escenario2("fueguito", std::stoi(enemigos["fuego-2"]));
            }
            else
            {
                cout << "Se encontro fuego-default-2 con "<< enemigos["fuego-default-2"] << " enemigos" << endl;
                modelo->escenario2("fueguito-default", std::stoi(enemigos["fuego-default-2"]));
            }
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
