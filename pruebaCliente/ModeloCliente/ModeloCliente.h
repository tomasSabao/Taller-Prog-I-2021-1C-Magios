#ifndef MODELOCLIENTE_H
#define MODELOCLIENTE_H
#include "../SocketCliente/SocketCliente.h"
#include <vector>
#include <pthread.h>
#include <iostream>
#include "../../Mensaje/Mensaje.h"
#include "../../Mensaje/Codificador.h"
#include "../../Mensaje/Decodificador.h"
#include <string>

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
        int sendData(Comando* comando);
        int closeSocket();
        void ImprimirModeloActualizado();
        int cargarComandos(Comando comando);

        static void* hello_helperRecieve(void *context);
        static void* hello_helperSend(void *context);
        static void* hello_helperIngresarDatos(void *context);
        static void* threadLogin(void *context);
        void* recibirDatosUsuario();
        void* desencolar();
        void* hiloLogin();
        // Structs for data transfer
        int skt; //este es el cliente que fue ya aceptado por el servidor
        
        //nuevas funciones realizadas con la libreria mensaje
        //enviarMensaje reemplaza a enviarData
        int enviarMensaje(void* msj, int tamanio_msj);
        //aca voy a tener un problema, porque tengo una unica direccion de memoria
        //donde guardo el mensaje. Solucionarlo con un memcpy a una posicion de memoria
        //otra
        //cargarMensaje reemplaza a cargarComandos
        int cargarMensaje(Mensaje* msj);
        //desencolar mensaje SOLO DESENCOLA, NO MANDA
        Mensaje* desencolarMensaje();
        //reemplaza a desencolar()
        int desencolarYMandarMensaje();
        //reemplaza a receive_data
        int recibirMensaje(int tamanio_msj,void* buff);
        //getter
        bool getEstaConectado();
        //funcion que simplemente recibe la tecla apretada
        int recibirUsuarioContrasenia();
        static void* funcionParaThread(void* contexto);
        //esta vacia
        static void* threadFunctionLogin(void* contexto);
        static void* threadFunctionEnviar(void* contexto);
        static void* threadFunctionRecibir(void* contexto);
        static void* funcionThreadTomarInput(void* contexto);
        static void* funcionThreadRecibir(void* contexto);
        static void* funcionThreadDesencolarYEnviar(void* contexto);
        static void* funcionThreadDesencolarYProcesar(void* contexto);
        void* recibirDataGeneral2();

        int desencolarYProcesarMensaje();
        int desencolarYEnviarMensaje();
        int procesarMensaje(Mensaje* msj);
        //encola mensaje para ser procesado
        void encolarMensaje(Mensaje* msj);
        //encola mensajes para ser enviado
        void encolarMensajeAEnviar(Mensaje* msj);
        int enviarMensaje(Mensaje* msj, int tamanio_bytes);
        bool getEstaConectadoServidor();
        void manejadora();

        bool estaConectado=false;




    protected:
        Modelo* modelo;
        Modelo_Jugador* modelo_jugador;
        int positionX;
        int positionY;
        int action;
        SocketCliente* socketCliente;
        std::vector<Comando> colaComando;
        Comando* unComando;
        bool activo;
        int indentificadorCliente;
        int contador;
        
        std::vector<Mensaje*> colaMensajes;
        std::vector<Mensaje*> colaMensajesAProcesar;
        //agregamos los codificadores, decodificadores y dos tipos de mensaje
        Codificador codificador;
        Decodificador decodificador;
        Mensaje envio_msj_login;
        Mensaje recibir_msj_login;
        Mensaje envio_msj_tecla;
        Mensaje recibo_msj_actualizacion;
        bool estaConectadoAlServidor=false;

    private:
};

#endif // MODELOCLIENTE_H
