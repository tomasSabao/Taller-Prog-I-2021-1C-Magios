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

struct Modelito
{
    int positionX;
    int positionY;
};

typedef struct Comando Comando;
typedef struct Modelito Modelito;


class SocketServidor
{
  public:
    SocketServidor(int puerto);
    virtual ~SocketServidor();
    int crearSocket();
    int bindSocket();
    int escuchar();
    int aceptandoConexiones();
    int enviarDataGeneralComando(int client_socket, Comando* comando);
    int recibirData();
    int cerrar();
    int getClientSocket();
    int getSocket();
    int enviarDataGeneral(int client_socket, Modelito *modelito);
    int recibirDataGeneral(int client_socket);
    //std::vector<Comando>  returnComandosSocket( );

    int enviarData(Modelito *modelito);
    Comando *getClientComand();
    int cargarComandosSocket(Comando comando);

  protected:
    Comando comando;
    //Modelito* modelo;
    int server_socket;
    struct sockaddr_in server_addr;
    int puerto;
    int client_socket;
    //std::vector<Comando> colaComandito;
    Comando* comandoPuntero;
    // Structs for data transfer

  private:
};

#endif // SOCKETSERVIDOR_H
