#include "ModeloServidor.h"

ModeloServidor::ModeloServidor()
{
 Modelo m;
 this->modelo= &m;


}

ModeloServidor::~ModeloServidor()
{
    //dtor
}

 void ModeloServidor::initializeData( )
{

     this->modelo->positionX=0 ;
     this->modelo->positionY=0 ;

    // this->View.positionX=0;

}




void ModeloServidor::processData(int action )
{
    switch ( action )
    {
        case 1://derecha

             this->modelo->positionX=this->modelo->positionX +1;

            break;
        case 2://izquierda

            this->modelo->positionY=this->modelo->positionY +1;

            break;
        case 3:

            break;
        case 4:

            break;
    }
}



 int ModeloServidor::CrearSocket(int puerto)
 {
    this->socketServidor= new SocketServidor(  puerto);
    this->socketServidor->crearSocket();
    return 0;
 }



 int  ModeloServidor::receiveData(  )
{
 int result=this->socketServidor->recibirData( );
 this->comando=this->socketServidor->getClientComand();
  printf("recibe el comando action: %d\n", this->comando->action );
 return result;
 }

 int  ModeloServidor::sendData(  )
 {
    int result=this->socketServidor->enviarData(  this->modelo);
    return result;
 }

int ModeloServidor::bindSocket( )
{
 return this->socketServidor->bindSocket();

}
int ModeloServidor::escuchar()
{
 return this->socketServidor->escuchar();

}
int ModeloServidor::aceptandoConexiones()
{
  int result=this->socketServidor->aceptandoConexiones();
this->client_socket=this->socketServidor->getClientSocket();
 return result;

}

int ModeloServidor::closeSocket()
{
 return this->socketServidor->cerrar();

}
