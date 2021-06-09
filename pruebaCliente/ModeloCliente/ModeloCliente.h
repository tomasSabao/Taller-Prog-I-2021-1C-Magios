#ifndef MODELOCLIENTE_H
#define MODELOCLIENTE_H
#include "../SocketCliente/SocketCliente.h"

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
        // Structs for data transfer

        int skt;//este es el cliente que fue ya aceptado por el servidor

        //Comando comando;

    protected:
    Modelo* modelo;
        int positionX;
        int positionY;
        int action;
        SocketCliente* socketCliente;

    private:
};

#endif // MODELOCLIENTE_H
