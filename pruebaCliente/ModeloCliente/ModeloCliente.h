#ifndef MODELOCLIENTE_H
#define MODELOCLIENTE_H
#include "../SocketCliente/SocketCliente.h"
#include <vector>
#include <pthread.h>
#include<iostream>
 using namespace std;
// Structs for data transfer

class ModeloCliente
{
    public:
        ModeloCliente();
        virtual ~ModeloCliente();
        //void  initializeData(struct View* client_view);
        //void  processData(int action, struct View* view);
        int crearSocket(char* host, int puerto);
        void initializeData(int action);
        int conectar();
        int receiveData();
        int sendData( Comando* comando);
        int closeSocket();
        void ImprimirModeloActualizado();
        int  cargarComandos(Comando comando);

        static void * hello_helperRecieve(void *context);
        static void * hello_helperSend(void *context);
        static void * hello_helperIngresarDatos(void *context);
        static void * threadLogin(void *context);
        void*  recibirDatosUsuario();
        void*  desencolar( ) ;
        void*  hiloLogin( ) ;

        // Structs for data transfer

        int skt;//este es el cliente que fue ya aceptado por el servidor

        //Comando comando;

    protected:
    Modelo* modelo;
        int positionX;
        int positionY;
        int action;
        SocketCliente* socketCliente;
        std::vector<Comando> colaComando;
        bool estaConectado;
        Comando* unComando;
        bool activo;
        int indentificadorCliente;
        int contador;

    private:
};

#endif // MODELOCLIENTE_H
