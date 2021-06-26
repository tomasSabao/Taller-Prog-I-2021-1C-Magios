#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>
#include "../ModeloServidor/ModeloServidor.h"
//#include "ModeloServidor.h"
//#include "../SocketServidor/SocketServidor.h"



// First argument: port
int main(int argc , char *argv[])
{
    int server_socket;
    int client_socket;


    int port = atoi(argv[1]);





  //SocketServidor* socket=new SocketServidor( port);
   ModeloServidor* modeloServidor= new ModeloServidor();
   modeloServidor->CrearSocket(port);
   modeloServidor->bindSocket();
   modeloServidor->escuchar();
   modeloServidor->aceptandoConexiones();







    struct Command client_command;
    struct View client_view;

    int commands_count = 0;
    int status = 0;
    modeloServidor->initializeData(&client_view);
    

    //keep communicating with client


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

     close(client_socket);
    printf("Client socket number %d closed\n",client_socket);
    modeloServidor->closeSocket();
    //printf("Server socket number %d closed\n",server_socket);

    return 0;
}


