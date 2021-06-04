#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>
#include "../ModeloServidor/ModeloServidor.h"
#include "../Thread/Thread.h"
//#include "ModeloServidor.h"
//#include "../SocketServidor/SocketServidor.h"

// Structs for data transfer

//------------------------
void *saludar(void* algo)
{
 int i;
 while(1)
 printf("hilo funcion saludar");

}
// First argument: port
int main(int argc , char *argv[])
{
    int server_socket;
    int client_socket;


    int port = atoi(argv[1]);


    //Thread* hilo= new Thread();
    //hilo->crearThread(saludar);


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
         printf("Incomming command action: %d\n", modeloServidor->getAction() );
        //--------------------

        // Process model
        modeloServidor->processData(modeloServidor->getAction()  );
        //--------------------

        // Send data (view)
        if (modeloServidor->sendData( ) < 0){
            perror("Send Data Error");
            status = -1;
        }
        printf("Send data: pos(X,Y) = (%d,%d)\n\n", modeloServidor->getPosicionX(), modeloServidor->getPosicionY());
        //--------------------*/

        commands_count++;
    }


modeloServidor->imprimirComandos();
     close(modeloServidor->getCliente());
    printf("Client socket number %d closed\n",modeloServidor->getCliente());
    modeloServidor->closeSocket();
    //printf("Server socket number %d closed\n",server_socket);*/

    return 0;
}


