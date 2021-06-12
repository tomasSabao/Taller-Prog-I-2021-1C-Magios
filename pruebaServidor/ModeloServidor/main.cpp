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
#define MAX_CLIENTS 4

// Structs for data transfer
std::vector<Conexion> colaConexiones;
int clients[MAX_CLIENTS] = {0 , 0 , 0, 0};
#include <pthread.h>

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

     pthread_t hilos[MAX_CLIENTS];
    int i = 0;
    while (true)
    {
        i++;

        modeloServidor->aceptandoConexiones();




          int er2 = pthread_create(&hilos[i], NULL,   &ModeloServidor::hello_helperRecieve,   modeloServidor);


         printf("mas de un cliente");


    }

    pthread_join(envio,NULL);
		pthread_join(hilos[1],NULL);
       modeloServidor->closeSocket();
    int commands_count = 0;
    int status = 0;

    printf("inicializa data: %d\n", 2);
    modeloServidor->initializeData();
    printf("termino %d\n", 2);

    //keep communicating with client

    while (commands_count < 20)
    {
        printf("Commands count: %d\n", commands_count + 1);

        // Receive data (command)
        if (modeloServidor->receiveData() < 0)
        {
            perror("Receive Data Error");
            status = -1;
        }
        printf("Incomming command action: %d\n", modeloServidor->getAction());
        //--------------------

        // Process model
        modeloServidor->processData(modeloServidor->getAction());
        //--------------------

        // Send data (view)
        if (modeloServidor->sendData() < 0)
        {
            perror("Send Data Error");
            status = -1;
        }
        printf("Send data: pos(X,Y) = (%d,%d)\n\n", modeloServidor->getPosicionX(), modeloServidor->getPosicionY());
        //--------------------*/

        commands_count++;
    }

    modeloServidor->imprimirComandos();
    close(modeloServidor->getCliente());
    printf("Client socket number %d closed\n", modeloServidor->getCliente());
    modeloServidor->closeSocket();
    //printf("Server socket number %d closed\n",server_socket);*/

    return 0;
}
