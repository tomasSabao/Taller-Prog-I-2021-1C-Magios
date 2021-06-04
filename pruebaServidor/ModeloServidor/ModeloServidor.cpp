#include "ModeloServidor.h"

ModeloServidor::ModeloServidor()
{
 Modelito m;
 this->modelo= m;


}

ModeloServidor::~ModeloServidor()
{
    //dtor
}

 void ModeloServidor::initializeData( )
{

     this->modelo.positionX=0 ;
     this->modelo.positionY=0 ;

    // this->View.positionX=0;

}


int ModeloServidor::getPosicionX()
{
    return this->modelo.positionX;
}

int ModeloServidor::getPosicionY()
{
    return this->modelo.positionY;
}


int ModeloServidor::getAction()
{
    return this->comando->action;
}

void ModeloServidor::processData(int action )
{
    switch ( action )
    {
        case 1://derecha
                printf("muevo derecha: %d\n", this->modelo.positionX );
             this->modelo.positionY=this->modelo.positionY+1;

            break;
        case 2://izquierda

             this->modelo.positionY=this->modelo.positionY -1;

            break;
        case 3:
            this->modelo.positionX=this->modelo.positionX +1;
            break;
        case 4:
            this->modelo.positionX=this->modelo.positionX -1;
            break;
    }
}

int ModeloServidor::cargarComandos(Comandito comando)
{
  //Comandito* nuevoComando=new struct Command();
  //nuevoComando=comando;
  Comandito comandato=comando;

    this->colaComando.push_back(  comandato);
    return 0;
}

void ModeloServidor::imprimirComandos()
{
  printf("muevo derecha: %d\n", this->modelo.positionX );


  for (int i = 0; i < this->colaComando.size(); i++) {


        printf("muevo derecha: %d\n", this->colaComando[i].action );




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
 this->cargarComandos(*this->socketServidor->getClientComand());
 this->comando=this->socketServidor->getClientComand();
  printf("recibe el comando action: %d\n", this->comando->action );
 return result;
 }

 int  ModeloServidor::sendData(  )
 {
    int result=this->socketServidor->enviarData(  &this->modelo);
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

int ModeloServidor::getCliente()
{

 return this->client_socket;

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
