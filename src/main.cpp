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

#define CANTIDAD_MIN_ARGS 2
#define POS_ARCHIVO_CONFIGURACION 1
#define CONFIG_LEN 7
#define LOG_LEN 4

extern Logger logger;
Parser parser = Parser();

int main( int argc, char* argv[] )
{
    std::string archivo_configuracion = "default.json";
    std::string cli_log = "";

    for (int i = 0; i < argc; i++) {
        std::string arg = argv[i];
        if (arg.find("config=") != std::string::npos) {
            archivo_configuracion = arg.substr(CONFIG_LEN);
        }
        else if (arg.find("log=") != std::string::npos) {
            cli_log = arg.substr(LOG_LEN);
        }
    }

    parser.obtenerJson(archivo_configuracion);

    std::string nivel_log = ((cli_log == "error") || (cli_log == "debug") || (cli_log == "info")) ? cli_log : parser.obtenerNivelLog();
    /*
    if (!cli_log) {
        std::string nivel_log = parser.obtenerNivelLog();
    } else {
        std::string nivel_log = cli_log;
    }*/

    logger.setNivelLog(nivel_log);
    //continua el flujo

    logger.log("info","Inicio del juego.");

    std::map<std::string, std::string> enemigos = parser.obtenerEnemigos();
    std::vector<std::string> fondos = parser.obtenerFondos();

    Modelo* modelo=new Modelo();
    //Modelo_Jugador* jugador=modelo->getModeloJugador();
    //VistaMono *vistaMono = new vistaMono(jugador);

    if (enemigos.find("fuego-1") != enemigos.end()) {
        modelo->escenario1("fueguito", std::stoi(enemigos["fuego-1"]));
    }
    else
    {
        modelo->escenario1("fueguito-default", std::stoi(enemigos["fuego-default-1"]));
    }

    int cantidad_jugadores = parser.obtenerCantidadJugadores();
    cout << "cantidad jugadores: " << cantidad_jugadores << endl;

    char* u1 = "alejandro";
    char* p1 = "123456";
    char* u2 = "andrea";
    char* p2 = "986543";
    char* u3 = "andrea";
    char* p3 = "986545";

    cout << "valido usuario1: " << parser.validarJugador(u1, p1) << endl;
    cout << "valido usuario2: " << parser.validarJugador(u2, p2) << endl;
    cout << "valido usuario3: " << parser.validarJugador(u3, p3) << endl;

    //if ((parser.validarJugador(u1,p1)) && jugador.status != ESPERANDO_PARTIDA) {
    //    //OK.
    //}


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
                    modelo->escenario2("fueguito", std::stoi(enemigos["fuego-2"]));
                }
                else
                {
                    modelo->escenario2("fueguito-default", std::stoi(enemigos["fuego-default-2"]));
                }
                
                //vector<string> fondos = parser.obtenerFondos();
                vista->escenario2(fondos.at(1));
            }
            mario->traducirTecla(quit);
            mario->mover();
            mario->imprimirPosicion();
            mario->imprimirVelocidad();
            modelo->recibirTecla(quit,"Jugador1");
            modelo->acciones();
            vista->render(quit);

         }
            mario->aplicarGravedad();
            mario->mover();
            modelo->acciones();
            modelo->recibirTecla(0,"Jugador1");
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
