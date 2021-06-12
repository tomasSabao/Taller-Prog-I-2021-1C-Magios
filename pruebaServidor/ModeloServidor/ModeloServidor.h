#ifndef MODELOSERVIDOR_H
#define MODELOSERVIDOR_H
#include "../SocketServidor/SocketServidor.h"
#include <vector>
 using namespace std;
 #include <pthread.h>
#include <stdio.h>
#define MAX_CLIENTS 4
#include "Thread.h"
// Structs for data transfer


class ModeloServidor
{
    public:
        ModeloServidor(int port);
        virtual ~ModeloServidor();

         void  initializeData( );

         void  processData(int action) ;
        int CrearSocket(int puerto);
        int bindSocket( );
        int escuchar();
        int aceptandoConexiones();
        int getNumeroThread();
        int  receiveData( );
        int  getCliente();
        int  getPosicionX();
        int cargarComandos(Comando comando );
        void imprimirComandos();
        void* receiveDataGeneral(  );
        void*  desencolar( );
         int  guardarCliente( int clienteSocket );

      int  socketAceptando(SocketServidor* unSocket);
         void  send_message(int clients, Modelo* modelito);
          int sendDataGeneral(int cliente, Modelo* modelito );
          void *manejoCliente( );
          static void * hello_helperRecieve(void *context);
           static void * hello_helperDesencolar(void *context);
        //int cargarComandos();


int  getPosicionY();



int  getAction();


        int  sendData( );
        int closeSocket();
        // Structs for data transfer




    protected:
     std::vector<Comando> colaComando;
     std::vector<Modelo> colaModelo;
     std::vector<int> colaSocketCliente;
//     std::vector< Thread*> colaThread;
     int client_socket;//este es el cliente que fue ya aceptado por el servidor
   Comando* comando;
   Modelo modelo;
   int numeroThread;

    int positionX;
    int positionY;
    int action;
    SocketServidor* socketServidor;


//












    private:
};

#endif // MODELOSERVIDOR_H
