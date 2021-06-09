#ifndef MODELOSERVIDOR_H
#define MODELOSERVIDOR_H
#include "../SocketServidor/SocketServidor.h"
#include <vector>
 using namespace std;
 #include <pthread.h>
#include <stdio.h>
#define MAX_CLIENTS 4
// Structs for data transfer


class ModeloServidor
{
    public:
        ModeloServidor(int port);
        virtual ~ModeloServidor();
         //void  initializeData(struct View* client_view);
         void  initializeData( );
         //void  processData(int action, struct View* view);
         void  processData(int action) ;
        int CrearSocket(int puerto);
        int bindSocket( );
        int escuchar();
        int aceptandoConexiones();
        int  receiveData( );
        int  getCliente();
        int  getPosicionX();
        int cargarComandos(Comando comando);
        void imprimirComandos();
        void* receiveDataGeneral(int socketCliente  );
        void  desencolar(int clients);

         int  socketAceptando(SocketServidor* unSocket);
         void  send_message(int clients, Modelo* modelito);
          int sendDataGeneral(int cliente, Modelo* modelito );
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
     int client_socket;//este es el cliente que fue ya aceptado por el servidor
   Comando* comando;
   Modelo modelo;

    int positionX;
    int positionY;
    int action;
    SocketServidor* socketServidor;


//












    private:
};

#endif // MODELOSERVIDOR_H
