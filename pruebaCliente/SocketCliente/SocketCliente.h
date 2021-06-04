#ifndef SOCKETCLIENTE_H
#define SOCKETCLIENTE_H
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

        typedef struct Command  Comandito;
        typedef struct Modelo  Modelito;

class SocketCliente
{
    public:
        SocketCliente(char* host, int puerto);
        virtual ~SocketCliente();
        int crearSocket();
        int conectar();
        int recibirData();
        int enviarData(Comandito* comando);
        Modelito* getServerModel();
        int cerrar();


    protected:
        //Comandito comando;
        Modelito modelo;

        struct sockaddr_in server_addr;
        int puerto;
        char* host;
        int skt;
        //Comando* comando;
        // Structs for data transfer

    private:
};

#endif // SOCKETCLIENTE_H
