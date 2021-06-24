#ifndef MODELOSERVIDOR_H
#define MODELOSERVIDOR_H
#include "../SocketServidor/SocketServidor.h"
#include "../ModeloServidor/Conexion.h"
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
        ModeloServidor(int port=5050);
        virtual ~ModeloServidor();
        void initializeData();
        void processData(Comando comando);
        void* crearThread(void *algunaFuncion(void*));
        int CrearSocket(int puerto);
        int bindSocket();
        int escuchar();
        int aceptandoConexiones();
        int getNumeroThread();
        int receiveData();
        int getCliente();
        int getPosicionX();
        int cargarComandos(Comando comando);
        void imprimirComandos();

        void* receiveDataGeneral(int socket);
        void* desencolar();
        int guardarCliente(int clienteSocket);
        int guardarConexion(Conexion* unaConexion);
        int socketAceptando(SocketServidor* unSocket);
        void send_message(int clients, Modelo* modelito);
        int sendDataGeneral(int cliente, Modelo* modelito);
        int sendDataGeneralComando(int cliente, Comando* comando);
        void *manejoCliente();
        static void * hello_helperRecieve(void *context);
        static void * hello_helperDesencolar(void *context);
        Comando login(Comando comando);
        //int cargarComandos();

        int getPosicionY();
        int getAction();
        int sendData();
        int closeSocket();
        // Structs for data transfer
        std::vector<Conexion> colaConexiones;


    protected:
        std::vector<Comando> colaComando;
        std::vector<Modelo> colaModelo;
        std::vector<int> colaSocketCliente;
        std::vector< pthread_t*> colaThread;
        //void* receiveDataGeneral;
        //std::vector< Thread*> colaThread;
        int client_socket;//este es el cliente que fue ya aceptado por el servidor
        Comando* comando;
        Modelo modelo;
        int numeroThread;
        int cantidadJugadoresActuales;
        int positionX;
        int positionY;
        int action;
        SocketServidor* socketServidor;
        int id;

    private:
};

struct Tupla
{
    ModeloServidor* unModelo;
    int idSocket;
};

typedef struct Tupla Tupla;
#endif // MODELOSERVIDOR_H
