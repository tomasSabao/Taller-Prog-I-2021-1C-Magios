#ifndef MODELOSERVIDOR_H
#define MODELOSERVIDOR_H
#include "../SocketServidor/SocketServidor.h"
#include "../ModeloServidor/Conexion.h"
#include <vector>
 using namespace std;
 #include <pthread.h>
#include <stdio.h>
//#define MAX_CLIENTS 4
#include "Thread.h"
#include <iostream>
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
         int  guardarCliente( Conexion* unaConexion );
         bool    cargarClientesAdmitidos(Conexion* unaConexion) ;

      int  socketAceptando(SocketServidor* unSocket);
         void  send_message(int clients, Modelo* modelito);
          int sendDataGeneral(int cliente, Modelo* modelito );
          void *manejoCliente( );
          static void * hello_helperRecieve(void *context);
           static void * hello_helperDesencolar(void *context);
           void  eliminarHiloClienteDemas(Conexion* unaConexion );
        //int cargarComandos();


int  getPosicionY();
void  activarTodasLasConexiones();

bool  verificarSiHayAlgunDesconectado();

int  getAction();
void  procesoYEnvioATodosClientes();

void  lanzarHilo();
void bloquearHiloMain();

        int  sendData( );
        int closeSocket();
        // Structs for data transfer




    protected:
     std::vector<Comando> colaComando;
     std::vector<Modelo> colaModelo;
     std::vector<int> colaSocketCliente;
     std::vector<Conexion*> colaConexiones;
     std::vector<pthread_t*> colaHilos;
     int MAX_CLIENTS=2;
     bool preparadoParaJugar;
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
