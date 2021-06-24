#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>
#include "../ModeloServidor/ModeloServidor.h"
#include "../ModeloServidor/Conexion.h"
#include "../Thread/Thread.h"
#include "../../Modelo/Modelo.h"
#include "../../Modelo/LTexture.h"
#include "../../lib/Logger.h"
#include "../../lib/Parser.h"
#include "../SocketServidor/SocketServidor.h"
#include <vector>
using namespace std;

//defines
#define CANT_MIN_ARGS 2
#define MAX_CLIENTS 4
#define ARG_POS_PORT 1
#define ARG_POS_CONFG 2
#define ARG_POS_LOG 3

// Structs for data transfer
int clients[MAX_CLIENTS] = {0 , 0 , 0, 0};
#include <pthread.h>

extern Logger logger;
Parser parser = Parser();


void *saludar(void *algo)
{
    int i;
  //  while (1)
        //printf("hilo funcion saludar soy un cliente");
        printf("hilo SOY CLIENTE NUMERO : %d\n", algo  );
}

void *handle_client(void *clientSocket)
{
    /* int i;
 while(1)
 printf("hilo  de conectado cliente saludar");*/
    printf("=== WELCOME TO THE CHATROOM ===\n");



    /*	pthread_t send_msg_thread; desencolar motodo de la clase modeloservidor
  if(pthread_create(&send_msg_thread, NULL, (void *) send_msg_handler, NULL) != 0){
		printf("ERROR: pthread\n");
    return EXIT_FAILURE;
	}*/
    /*ModeloServidor* modeloServidor= (ModeloServidor*)clientSocket;
	modeloServidor->receiveDataGeneral(clientSocket);
	modeloServidor->desencolar(int clients);*/

    /*pthread_t recv_msg_thread;
  if(pthread_create(&recv_msg_thread, NULL,  modeloservidor->receiveDataGeneral(), clientSocket) != 0){
		printf("ERROR: pthread\n");
		return EXIT_FAILURE;
	}*/
}

pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

/* Add clients to queue */
void queue_add(int cl)
{
    pthread_mutex_lock(&clients_mutex);

    for (int i = 0; i < MAX_CLIENTS; ++i)
    {
        if (!clients[i])
        {
            clients[i] = cl;
            break;
        }
    }

    pthread_mutex_unlock(&clients_mutex);
}

/* Remove clients to queue */
void queue_remove(int uid)
{
    pthread_mutex_lock(&clients_mutex);

    /*for(int i=0; i < MAX_CLIENTS; ++i){
		if(clients[i]){
			if(clients[i]->uid == uid){
				clients[i] = NULL;
				break;
			}
		}
	}*/

    pthread_mutex_unlock(&clients_mutex);
}

bool validate_arguments(int argc, char *argv[])
{
    if (argc < CANT_MIN_ARGS)
    {
        cout << "Cantidad incorrecta de argumentos" << endl;
        cout << "Uso: ./nombre_del_programa [puerto] [archivo de configuracion] [nivel de log]" << endl;
        return false;
    }

    try
    {
        int port = std::stoi(argv[ARG_POS_PORT]);

        if (port <= 0)
        {
            cout << "Puerto no válido" << endl;
            return false;
        }

        return true;
    }
    catch (invalid_argument)
    {
        cout << "Puerto no válido";
        return false;
    }
    catch (out_of_range)
    {
        cout << "Puerto fuera de rango";
        return false;
    }
}


// First argument: port
int main(int argc , char *argv[])
{
    if (validate_arguments(argc, argv) == false)
    {
        return EXIT_FAILURE;
    }

    string archivo_configuracion = (argc > ARG_POS_CONFG) ? argv[ARG_POS_CONFG] : "default.json";
    string cli_log = (argc > ARG_POS_LOG) ? argv[ARG_POS_LOG] : "";
    int port = stoi(argv[ARG_POS_PORT]);

    parser.obtenerJson(archivo_configuracion);
    string nivel_log = ((cli_log == "error") || (cli_log == "debug") || (cli_log == "info")) ? cli_log : parser.obtenerNivelLog();
    logger.setNivelLog(nivel_log);
    logger.log("info","Inicio del juego.");


    //inicializo el modelo.
    Modelo* modelo=new Modelo();

    std::map<std::string, std::string> enemigos = parser.obtenerEnemigos();
    std::vector<std::string> fondos = parser.obtenerFondos();
    if (enemigos.find("fuego-1") != enemigos.end()) {
        modelo->escenario1("fueguito", std::stoi(enemigos["fuego-1"]));
    } else
    {
        modelo->escenario1("fueguito-default", std::stoi(enemigos["fuego-default-1"]));
    }
    int cantidad_jugadores = parser.obtenerCantidadJugadores();
    cout << "cantidad jugadores: " << cantidad_jugadores << endl;

    int server_socket;
    int client_socket;

    ModeloServidor* modeloServidor= new ModeloServidor(port);
    modeloServidor->CrearSocket(port);
    modeloServidor->bindSocket();
    modeloServidor->escuchar();
    modeloServidor->aceptandoConexiones();




    int commands_count = 0;
    int status = 0;

    //TODO: esto no va.
    modeloServidor->initializeData(&client_view);


    //keep communicating with client
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

    //TODO: borrar esto
    struct Command client_command;
    struct View client_view;
    while (commands_count < 20)
    {
        printf("Commands count: %d\n", commands_count + 1);

        // Receive data (command)
        if (modeloServidor->receiveData(&client_socket, &client_command) < 0){
            perror("Receive Data Error");
            status = -1;
        }
        printf("Incomming command action: %d\n", client_command.action);
        //--------------------

        // Process model
        modeloServidor->processData(client_command.action, &client_view);
        //--------------------

        // Send data (view)
        if (modeloServidor->sendData(&client_socket, &client_view) < 0){
            perror("Send Data Error");
            status = -1;
        }
        printf("Send data: pos(X,Y) = (%d,%d)\n\n", client_view.positionX, client_view.positionY);
        //--------------------

        commands_count++;
    }

    //TODO: ver esto
    //
    int quit=0;

    //SDL_Event e;
    while(quit!=1){
        while(controlador.desencolarEvento()!=0){
            quit= controlador.descifrarEvento();
            if(quit==32)
            {
                if (enemigos.find("fuego-2") != enemigos.end()) {
                    modelo->escenario2("fueguito", std::stoi(enemigos["fuego-2"]));
                } else
                {
                    modelo->escenario2("fueguito-default", std::stoi(enemigos["fuego-default-2"]));
                }
                vista->escenario2();
            }
            mario->traducirTecla(quit);
            mario->mover();
            mario->imprimirPosicion();
            mario->imprimirVelocidad();
            //TODO: aca hay que ingresar el username del socket/thread actual en vez de esto hardcodeado
            modelo->recibirTecla(quit,"Jugador1");
            modelo->acciones();
            vista->render(quit);

        }
        mario->aplicarGravedad();
        mario->mover();
        modelo->acciones();
        //TODO: aca hay que ingresar el username socket/thread actual en vez de esto hardcodeado
        modelo->recibirTecla(0,"Jugador1");
        vista->render(quit);
        //modelo->getModeloJugador(0)->caminar();
        //modelo->getMono()->caminar();
        //printf("Evento numero: %d\n",modelo->getModeloJugador(7)->getFrame());
    }
    //

    close(client_socket);
    printf("Client socket number %d closed\n",client_socket);
    modeloServidor->closeSocket();
    //printf("Server socket number %d closed\n",server_socket);

    return 0;
}


