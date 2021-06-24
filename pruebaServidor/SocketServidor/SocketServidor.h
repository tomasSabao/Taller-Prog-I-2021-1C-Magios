#ifndef SOCKETSERVIDOR_H
#define SOCKETSERVIDOR_H
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>

//#include "Thread.h"



struct Comando
{
    int action;
    int tipo;
    int nombre;
    int password;
};

struct Modelo
{
    int positionX;
    int positionY;
};


typedef struct Comando Comando;
typedef struct Modelo Modelo;

class SocketServidor
{
  public:
    SocketServidor(int puerto);
    virtual ~SocketServidor();
    int crearSocket();
    int bindSocket();
    int escuchar();
    int aceptandoConexiones();
    int  enviarDataGeneralComando(int client_socket, Comando* comando);
    int recibirData();
    int cerrar();
    int getClientSocket();
    int getSocket();
    int enviarDataGeneral(int client_socket, Modelo *modelo);
    int recibirDataGeneral(int client_socket);
    //std::vector<Comando>  returnComandosSocket( );

    int enviarData(Modelo *modelo);
    Comando *getClientComand();
    int cargarComandosSocket(Comando comando);

  protected:
    Comando comando;
    //Modelo* modelo;
    int server_socket;
    struct sockaddr_in server_addr;
    int puerto;
    int client_socket;
   //  std::vector<Comando> colaComandito;
    Comando* comandoPuntero;
    // Structs for data transfer

  private:
};

#endif // SOCKETSERVIDOR_H
