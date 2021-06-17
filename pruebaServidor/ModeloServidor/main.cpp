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

//#include "ModeloServidor.h"
#include "../SocketServidor/SocketServidor.h"
#include <vector>
using namespace std;

//defines
#define QTY_ARGUMENTS 2
#define ARG_POS_IP_PORT 1
//#define MAX_CLIENTS 2

// Structs for data transfer
std::vector<Conexion> colaConexiones;
//int clients[MAX_CLIENTS] = {0 , 0 , 0, 0};
#include <pthread.h>



pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

/* Add clients to queue
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
*/

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
    if (argc != QTY_ARGUMENTS)
    {
        cout << "Cantidad incorrecta de argumentos" << endl;
        cout << "Uso: ./nombre_del_programa [puerto] " << endl;
        return false;
    }

    try
    {
        int port = std::stoi(argv[ARG_POS_IP_PORT]);

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
int main(int argc, char *argv[])
{

    if (validate_arguments(argc, argv) == false)
    {
        return EXIT_FAILURE;
    }

    int server_socket;
    int client_socket;

    int port = stoi(argv[ARG_POS_IP_PORT]);


    ModeloServidor *modeloServidor = new ModeloServidor(5555);
    modeloServidor->CrearSocket(port);
   modeloServidor->bindSocket();
   modeloServidor->escuchar();

    pthread_t envio;
    pthread_t recivo;


     int err = pthread_create(&envio, NULL,   &ModeloServidor::hello_helperDesencolar,   modeloServidor);

     //pthread_t hilos[MAX_CLIENTS];
    int i = 0;
    int cantThread=0;
    while (true)
    {


        int esAceptado=modeloServidor->aceptandoConexiones();


/*
          if(esAceptado!=1)//
          {
             printf("cliente numero  %d aceptado , espere hasta que se conecte el maximo de 3 cupos \n", cantThread);
             printf("se lanza hilo  %d \n", cantThread);
             //modelo->lanzarthread
             int er2 = pthread_create(&hilos[cantThread], NULL,   &ModeloServidor::hello_helperRecieve,   modeloServidor);
             //modeloser->guardarthear()//
             cantThread=cantThread+1;
          }else
          {
             printf("no hay mas cupos, estan los %d clientes en juego \n", i);
          }


*/


         i++;
    }

    pthread_join(envio,NULL);
      modeloServidor->bloquearHiloMain();
       modeloServidor->closeSocket();




   /* modeloServidor->imprimirComandos();
    close(modeloServidor->getCliente());
    printf("Client socket number %d closed\n", modeloServidor->getCliente());
    modeloServidor->closeSocket();*/
    //printf("Server socket number %d closed\n",server_socket);*/

    return 0;
}
