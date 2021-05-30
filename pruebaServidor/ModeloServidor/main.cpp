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

// Structs for data transfer

//------------------------

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







    int commands_count = 0;
    int status = 0;

    printf("inicializa data: %d\n",  2);
    modeloServidor->initializeData( );
    printf("termino %d\n",  2);

    //keep communicating with client


    while (commands_count < 20)
    {
        printf("Commands count: %d\n", commands_count + 1);

        // Receive data (command)
        if (modeloServidor->receiveData( ) < 0){
            perror("Receive Data Error");
            status = -1;
        }
         printf("Incomming command action: %d\n", modeloServidor->comando->action );
        //--------------------

        // Process model
        modeloServidor->processData(modeloServidor->comando->action  );
        //--------------------

        // Send data (view)
        if (modeloServidor->sendData( ) < 0){
            perror("Send Data Error");
            status = -1;
        }
        printf("Send data: pos(X,Y) = (%d,%d)\n\n", modeloServidor->modelo->positionX, modeloServidor->modelo->positionY);
        //--------------------*/

        commands_count++;
    }

     close(modeloServidor->client_socket);
    printf("Client socket number %d closed\n",modeloServidor->client_socket);
    modeloServidor->closeSocket();
    //printf("Server socket number %d closed\n",server_socket);*/

    return 0;
}


