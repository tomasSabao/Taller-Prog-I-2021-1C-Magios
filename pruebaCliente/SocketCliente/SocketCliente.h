#ifndef SOCKETCLIENTE_H
#define SOCKETCLIENTE_H
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>
#include "../Mensaje/Mensaje.h"


struct Command {
    int action;
    int tipo;
   	int nombre;
   	int password;
};

struct Modelito {
    int positionX;
    int positionY;
};
typedef struct Command Comando;
typedef struct Modelito Modelo;


class SocketCliente
{
    public:
        SocketCliente(char* host, int puerto);
        virtual ~SocketCliente();
        int crearSocket();
        int conectar();
        int recibirData();
        int recibirData(int tamanio_msj, Mensaje* msj);
        int enviarData(Comando* comando);
        int enviarData(void* msj,int tamanio_bytes);
        Modelito* getServerModel();
        int cerrar();
        int recibirDataComando();
        Comando* getServerComando();

    protected:
        //Comando comando;
        Modelito* modelo;
        Comando* unComando;
        struct sockaddr_in server_addr;
        int puerto;
        char* host;
        int skt;
        //Comando* comando;
        // Structs for data transfer

    private:
};

#endif // SOCKETCLIENTE_H
