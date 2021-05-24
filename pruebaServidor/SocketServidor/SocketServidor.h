#ifndef SOCKETSERVIDOR_H
#define SOCKETSERVIDOR_H
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>

struct Command {
   int action;
};

struct View {
    int positionX;
    int positionY;
};

class SocketServidor
{
    public:
        SocketServidor(int puerto);
        virtual ~SocketServidor();
        int crearSocket();
        int bindSocket( );
        int escuchar();
        int aceptandoConexiones();
        int enviarData(int* client_socket, struct View* client_view);
        int recibirData(int* client_socket, struct Command* client_command);
        int cerrar();


    protected:
    int server_socket;
    struct sockaddr_in server_addr;
    int puerto;
    int client_socket ;


    private:
};

#endif // SOCKETSERVIDOR_H
