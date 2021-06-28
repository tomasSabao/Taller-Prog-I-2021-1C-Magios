#ifndef MODELOSERVIDOR_H
#define MODELOSERVIDOR_H
#include "../SocketServidor/SocketServidor.h"
#include "../ModeloServidor/Conexion.h"
#include "../Mensaje/Codificador.h"
#include "../Mensaje/Decodificador.h"
#include "../Mensaje/Mensaje.h"
#include "../ModeloServidor/Conexion.h"
#include "../../Modelo/Modelo.h"
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
        ModeloServidor(Modelo* modeloJuego, int port=5050);
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
        void* recibirDataGeneral2(int socket_de_ese_thread);
        int guardarConexion(Conexion* unaConexion);

        void* receiveDataGeneral(int socket);
        void* desencolar();
        int guardarCliente(int clienteSocket);
        int socketAceptando(SocketServidor* unSocket);
        void send_message(int clients, Modelo* modelito);
        int sendDataGeneral(int cliente, Modelo* modelito);
        int sendDataGeneralComando(int cliente, Comando* comando);
        void *manejoCliente();
        static void * hello_helperRecieve(void *context);
        static void * hello_helperDesencolar(void *context);
        Comando login(Comando comando);
        //int cargarComandos();
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

        int getPosicionY();
        int getAction();
        int sendData();
        int closeSocket();
        // Structs for data transfer
        std::vector<Conexion> colaConexiones;
        Mensaje buffer_login;
        Mensaje buffer_rta_login;
        Modelo* modelo_juego;

    protected:
        std::vector<Comando> colaComando;
        std::vector<Modelo> colaModelo;
        std::vector<int> colaSocketCliente;
        std::vector<pthread_t*> colaThread;
        //void* receiveDataGeneral;
        //std::vector< Thread*> colaThread;
        int client_socket;//este es el cliente que fue ya aceptado por el servidor
        Comando* comando;
        Modelo modelo;
        Modelo_Jugador* modelo_jugador;
        int numeroThread;
        int cantidadJugadoresActuales;
        int positionX;
        int positionY;
        int action;
        SocketServidor* socketServidor;
        int id;
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

    private:
};

struct Tupla
{
    ModeloServidor* unModelo;
    int idSocket;
};
typedef struct Tupla Tupla;

#endif // MODELOSERVIDOR_H
