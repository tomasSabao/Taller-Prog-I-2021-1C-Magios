#ifndef MODELOSERVIDOR_H
#define MODELOSERVIDOR_H
#include "../SocketServidor/SocketServidor.h"
// Structs for data transfer


class ModeloServidor
{
    public:
        ModeloServidor();
        virtual ~ModeloServidor();
         void  initializeData(struct View* client_view);
         void  processData(int action, struct View* view);
        int CrearSocket(int puerto);
        int bindSocket( );
        int escuchar();
        int aceptandoConexiones();
        int  receiveData(int* client_socket, struct Command* client_command);

        int  sendData(int* client_socket, struct View* client_view);
        int closeSocket();

    protected:
    int positionX;
    int positionY;
    int action;
    SocketServidor* socketServidor;




    private:
};

#endif // MODELOSERVIDOR_H
