#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>
#include "SocketCliente/SocketCliente.h"
#include "ModeloCliente/ModeloCliente.h"

// Structs for data transfer

//------------------------

// First argument: port
int main(int argc , char *argv[])
{

    Comandito command;
    Modelito model;
    int port = atoi(argv[2]);
    char* host = argv[1];


    ModeloCliente* unModeloCliente= new ModeloCliente();
    //SocketCliente* socket = new SocketCliente(host, port);
    unModeloCliente->crearSocket(host,port);
    unModeloCliente->conectar();
    //socket->crearSocket();
    //socket->conectar();

    int commands_count = 0;
    int status = 0;

    //keep communicating with client
    int commands [20]={2,1,2,1,1,1,2,1,1,1,1,1,2,1,2,1,1,1,2,1};

    //keep communicating with server
    for(int i=0; i<20; i++)
    {

        // Set data to send
        //socket->comando->action = commands[i];
        command.action = commands[i];

        unModeloCliente->sendData(&command);
        printf("loop:  %d\n", i);

        //--------------------
        printf("Commands count: %d\n", i + 1);

        // Send data (command)
      /*  if (socket->enviarData(&command) < 0) {
        //if (socket->enviarData(socket->comando) < 0) {
            perror("Send Data Error");
            status = -1;
        }*/
        //printf("Send data: action = %d\n", socket->comando->action);
        printf("Send data: action = %d\n", command.action);
        //--------------------

        // Receive data (view)
        if (unModeloCliente->receiveData() < 0) {
            perror("Receive Data Error");
            status = -1;
        }

        //TODO: process client Data to show in here:
        //modeloCliente->processData(modeloCliente->comando->action);

         unModeloCliente->ImprimirModeloActulizado();
        //--------------------
    }

    unModeloCliente->closeSocket();
    //printf("Server socket number %d closed\n",server_socket);
    return 0;
}


//TODO:
/*
int main(int argc , char *argv[])
{
    struct Command command;
    struct Modelo model;
    int port = atoi(argv[2]);
    char* host = argv[1];

    ModeloCliente* modeloCliente = new ModeloCliente();
    modeloCliente->crearSocket(host, port);
    modeloCliente->conectar();


    SocketCliente* socket = new SocketCliente(host, port);
    socket->crearSocket();
    socket->conectar();

    int commands_count = 0;
    int status = 0;

    //keep communicating with client
    int commands [20]={1,4,2,3,1,4,2,3,2,4,1,4,2,3,2,4,1,3,2,4};

    //keep communicating with server
    for(int i = 0; i < 20; i++)
    {
        printf("Commands count: %d\n", commands_count + 1);

        // Initialize Data | Set data to send
        modeloCliente->initializeData(commands[i]);

        // Receive data (command)
        if (modeloCliente->sendData(modeloCliente->comando) < 0) {
            perror("Send Data Error");
            status = -1;
        }
        printf("Incomming command action: %d\n", modeloCliente->comando->action);

        //--------------------

        // Receive data (view)
        if (modeloCliente->receiveData() < 0) {
            perror("Receive Data Error");
            status = -1;
        }

        printf("Receive data: pos(X,Y) = (%d,%d)\n\n", modeloCliente->modelo->positionX, modeloCliente->modelo->positionY);
        //--------------------
    }

    modeloCliente->closeSocket();
    //printf("Server socket number %d closed\n",server_socket);
    return 0;
}
*/
