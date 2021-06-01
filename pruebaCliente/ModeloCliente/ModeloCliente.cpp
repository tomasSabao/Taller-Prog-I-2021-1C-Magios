#include "ModeloCliente.h"


ModeloCliente::ModeloCliente()
{
    Modelo m;
    this->modelo= &m;
}

ModeloCliente::~ModeloCliente()
{
    //dtor
}

int ModeloCliente::crearSocket(int puerto, char* host)
{
    this->socketCliente= new SocketCliente(puerto, host);
    this->socketCliente->crearSocket();
    return 0;
}

void ModeloCliente::initializeData()
{
     this->modelo->positionX=0 ;
     this->modelo->positionY=0 ;

    // this->View.positionX=0;
}

int ModeloCliente::receiveData()
{
    int result=this->socketCliente->recibirData();
    return result;
}

int ModeloCliente::sendData(Command* comando)
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
