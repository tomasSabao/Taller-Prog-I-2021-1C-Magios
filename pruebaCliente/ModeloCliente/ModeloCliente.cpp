#include "ModeloCliente.h"


ModeloCliente::ModeloCliente()
{
    //Modelo m;
    //this->modelo = &m;

   // Comandito c;
    //this->comando = c;
}

ModeloCliente::~ModeloCliente()
{
    //dtor
}

int ModeloCliente::crearSocket(char* host, int puerto)
{
    this->socketCliente = new SocketCliente(host, puerto);
    this->socketCliente->crearSocket();
    return 0;
}

void ModeloCliente::initializeData(int action)
{
    //this->modelo->positionX=0 ;
    //this->modelo->positionY=0 ;

//    this->comando.action = action;
}


void ModeloCliente::ImprimirModeloActulizado()
 {

   printf("Receive data: pos(X,Y) = (%d,%d)\n\n", this->modelo->positionX, this->modelo->positionY );
 }

int ModeloCliente::receiveData()
{
    int result = this->socketCliente->recibirData();
    this->modelo = this->socketCliente->getServerModel();
    return result;
}

int ModeloCliente::sendData(Comandito* comando)
{
    int result = this->socketCliente->enviarData(comando);
    return result;
}

int ModeloCliente::conectar()
{
    return this->socketCliente->conectar();
}

int ModeloCliente::closeSocket()
{
    return this->socketCliente->cerrar();
}
