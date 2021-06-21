#ifndef MODELOSERVIDOR_H
#define MODELOSERVIDOR_H
#include "../SocketServidor/SocketServidor.h"
#include "../mensaje/Codificador.h"
#include "../mensaje/Decodificador.h"
#include "../mensaje/Mensaje.h"
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



         //reemplazo con las funciones que usan mensaje, codificador, decodificador
         int recibirMensaje();

         void* funcionThreadDesencolar(void* contexto);
         static void* funcionThreadRecibir(void* contexto);
         
         //este valor reemplaza a receiveDataGeneral()
         void* recibirDataGeneral2();

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


    Mensaje buffer_login;

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

    Codificador codificador;
    Decodificador decodificador;

    Mensaje msj_login_fallo;
    Mensaje msj_login_funciono;
    //aca es donde quiero copiar el mensaje x. Se va a redimensionar
    //constantemente

    Mensaje buffer_tecla;




//












    private:
};

#endif // MODELOSERVIDOR_H
