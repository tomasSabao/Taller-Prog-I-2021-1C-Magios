#ifndef SOCKETSERVIDOR_H
#define SOCKETSERVIDOR_H
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>




      struct  Command {
           int action;
        }  ;


     struct  Modelo {
            int positionX;
            int positionY;
        }  ;

class SocketServidor
{
    public:
        SocketServidor(int puerto);
        virtual ~SocketServidor();
        int crearSocket();
        int bindSocket( );
        int escuchar();
        int aceptandoConexiones();

        int recibirData(     );
        int cerrar();
        int getClientSocket();


  int enviarData(   Modelo*  modelo);
         Command* getClientComand();



    protected:
    Command* comando;
     //Modelo* modelo;
    int server_socket;
    struct sockaddr_in server_addr;
    int puerto;
    int client_socket ;
    //Comando* comando;
    // Structs for data transfer



    private:
};

#endif // SOCKETSERVIDOR_H
