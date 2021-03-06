#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>
#include "SocketCliente/SocketCliente.h"
#include "ModeloCliente/ModeloCliente.h"
#include <pthread.h>
using namespace std;
#include<iostream>

#define ARG_POS_HOST 1
#define ARG_POS_PORT 2

// Structs for data transfer

//------------------------

// First argument: port
int main(int argc , char *argv[])
{
    Comando command;
    Modelo model;
    int port = atoi(argv[ARG_POS_PORT]);
    char* host = argv[ARG_POS_HOST];

    ModeloCliente* unModeloCliente= new ModeloCliente();
    //SocketCliente* socket = new SocketCliente(host, port);
    unModeloCliente->crearSocket(host,port);
    unModeloCliente->conectar();
    //socket->crearSocket();
    //socket->conectar();

    int commands_count = 0;
    int status = 0;

    /*
    pthread_t ingresarDatos;
    pthread_t recv_msg_thread;
    pthread_t send_msg_thread;
    pthread_t hiloLogin2;
    
    if (pthread_create(&hiloLogin2, NULL, &ModeloCliente::threadLogin, unModeloCliente) != 0)
    {
        printf("ERROR: pthread\n");
        return EXIT_FAILURE;
    }

    if (pthread_create(&ingresarDatos, NULL, &ModeloCliente::hello_helperIngresarDatos, unModeloCliente) != 0)
    {
        printf("ERROR: pthread\n");
        return EXIT_FAILURE;
    }

    if (pthread_create(&recv_msg_thread, NULL, &ModeloCliente::hello_helperRecieve, unModeloCliente) != 0)
    {
        printf("ERROR: pthread\n");
        return EXIT_FAILURE;
    }

    if (pthread_create(&send_msg_thread, NULL, &ModeloCliente::hello_helperSend, unModeloCliente) != 0)
    {
        printf("ERROR: pthread\n");
        return EXIT_FAILURE;
    }

    pthread_join(ingresarDatos,NULL);
    pthread_join(recv_msg_thread,NULL);
    pthread_join(send_msg_thread,NULL);
    */

    //servidorMensaje
    pthread_t login_thread;
    pthread_t recibir_msg_thread;
    pthread_t enviar_msg_thread;
    pthread_t procesar_msg_thread;

    if (pthread_create(&login_thread,NULL, &ModeloCliente::funcionParaThread,unModeloCliente) != 0) {
        printf("ERROR: pthread login fallo\n");
        return EXIT_FAILURE;
    }

    if (pthread_create(&procesar_msg_thread,NULL, &ModeloCliente::funcionThreadDesencolarYProcesar,unModeloCliente)!=0){
        printf("ERROR: pthread procesar fallo\n");
        return EXIT_FAILURE;
    }

    if (pthread_create(&recibir_msg_thread,NULL, &ModeloCliente::funcionThreadRecibir,unModeloCliente)  != 0) {
        printf("ERROR: pthread recibir fallo\n");
        return EXIT_FAILURE;
    }

    if (pthread_create(&enviar_msg_thread, NULL, &ModeloCliente::threadFunctionEnviar,unModeloCliente) != 0) {
        printf("ERROR: pthread enviar fallo\n");
        return EXIT_FAILURE;
    }

    pthread_join(enviar_msg_thread,NULL);
    pthread_join(login_thread,NULL);
    pthread_join(recibir_msg_thread,NULL);
    pthread_join(procesar_msg_thread,NULL);
    //modeloServidor->closeSocket();
    //modeloServidor->closeSocket();
    //

    //TODO: process client Data to show in here:
    //modeloCliente->processData(modeloCliente->comando->action);

    unModeloCliente->ImprimirModeloActualizado();
    //--------------------

    unModeloCliente->closeSocket();
    //printf("Server socket number %d closed\n",server_socket);
    return 0;
}
