#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>
#include "SocketCliente/SocketCliente.h"

// Structs for data transfer

//------------------------

// First argument: port
int main(int argc , char *argv[])
{

    struct Command command;
    struct Modelo model;
    int port = atoi(argv[2]);
    char* host = argv[1];

    SocketCliente* socket = new SocketCliente(host, port);
    socket->crearSocket();
    socket->conectar();

    int commands_count = 0;
    int status = 0;

    //keep communicating with client
    int commands [20]={1,4,2,3,1,4,2,3,2,4,1,4,2,3,2,4,1,3,2,4};

    //keep communicating with server    
    for(int i=0; i<20; i++)
    {
        
        // Set data to send
        //socket->comando->action = commands[i];
        command.action = commands[i];
        printf("loop:  %d\n", i);

        //--------------------
        printf("Commands count: %d\n", i + 1);

        // Send data (command)
        if (socket->enviarData(&command) < 0) {
        //if (socket->enviarData(socket->comando) < 0) {
            perror("Send Data Error");
            status = -1;
        }
        //printf("Send data: action = %d\n", socket->comando->action);
        printf("Send data: action = %d\n", command.action);
        //--------------------

        // Receive data (view)
        if (socket->recibirData() < 0) {
            perror("Receive Data Error");
            status = -1;
        }

        //TODO: process client Data to show in here:
        //modeloCliente->processData(modeloCliente->comando->action);

        printf("Receive data: pos(X,Y) = (%d,%d)\n\n", socket->modelo->positionX, socket->modelo->positionY);
        //--------------------           
    }

    socket->cerrar();
    //printf("Server socket number %d closed\n",server_socket);*/
    return 0;
}
