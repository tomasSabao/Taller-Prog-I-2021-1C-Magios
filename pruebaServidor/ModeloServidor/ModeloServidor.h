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

         static void* funcionThreadRecibir(void* contexto);

         static void* funcionThreadDesencolarYEnviar(void* contexto);

         static void* funcionThreadDesencolarYProcesar(void* contexto);



         int desencolarYProcesarMensaje();


         int desencolarYEnviarMensaje();

         int procesarMensaje(Mensaje* msj);
         //encola mensaje para ser procesado
         void encolarMensaje(Mensaje* msj);
         //encola mensajes para ser enviado
         int encolarMensajeAEnviar(Mensaje* msj);

         int enviarMensaje(Mensaje* msj,int tamanio_bytes);

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
    Mensaje buffer_rta_login;

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

    //esta es la cola de mensajes recibidos
    std::vector<Mensaje*> cola_mensajes;

    //esta es la cola de mensaje enviados
    std::vector<Mensaje*> cola_mensajes_a_enviar;


//












    private:
};

#endif // MODELOSERVIDOR_H
