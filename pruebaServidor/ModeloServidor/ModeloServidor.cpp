#include "ModeloServidor.h"

ModeloServidor::ModeloServidor()
{
    //ctor
}

ModeloServidor::~ModeloServidor()
{
    //dtor
}

 void ModeloServidor::initializeData(struct View* client_view)
{
   (*client_view).positionX = 0;
   (*client_view).positionY = 0;
}
void ModeloServidor::processData(int action, struct View* view)
{
    switch ( action )
    {
        case 1:
            (*view).positionY += 1;
            break;
        case 2:
            (*view).positionY -= 1;
            break;
        case 3:
            (*view).positionX += 1;
            break;
        case 4:
            (*view).positionX -= 1;
            break;
    }
}






 int ModeloServidor::CrearSocket(int puerto)
 {
    this->socketServidor= new SocketServidor(  puerto);
    this->socketServidor->crearSocket();
    return 0;
 }



 int  ModeloServidor::receiveData(int* client_socket, struct Command* client_command)
{
 this->socketServidor->recibirData(client_socket, client_command);
 return 0;
 }

 int  ModeloServidor::sendData(int* client_socket, struct View* client_view)
 {
    this->socketServidor->enviarData(client_socket, client_view);
    return 0;
 }

int ModeloServidor::bindSocket( )
{
 this->socketServidor->bindSocket();
return 0;
}
int ModeloServidor::escuchar()
{
 this->socketServidor->escuchar();
return 0;
}
int ModeloServidor::aceptandoConexiones()
{
 this->socketServidor->aceptandoConexiones();
return 0;
}

int ModeloServidor::closeSocket()
{
 this->socketServidor->cerrar();
 return 0;
}
