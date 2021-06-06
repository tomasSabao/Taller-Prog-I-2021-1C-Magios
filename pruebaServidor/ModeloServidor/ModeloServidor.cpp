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
        case 3://izquierda

             this->modelo.positionY=this->modelo.positionY -1;

            break;
        case 2:
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
  pthread_mutex_t colaMutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_lock(&colaMutex);

    this->colaComando.push_back(  comandato);
    pthread_mutex_unlock(&colaMutex);
    return 0;
}

void ModeloServidor::imprimirComandos()
{
  printf("muevo derecha: %d\n", this->modelo.positionX );

    pthread_mutex_t colaMutex = PTHREAD_MUTEX_INITIALIZER;
  for (int i = 0; i < this->colaComando.size(); i++) {

        pthread_mutex_lock(&colaMutex);
        printf("muevo derecha: %d\n", this->colaComando[i].action );


         pthread_mutex_unlock(&colaMutex);

        }

}


 int ModeloServidor::CrearSocket(int puerto)
 {
    this->socketServidor= new SocketServidor(  puerto);
    this->socketServidor->crearSocket();


    return 0;
 }





int ModeloServidor::getCliente()
{

 return this->client_socket;

}


 int  ModeloServidor::receiveData(  )
{
 int result=this->socketServidor->recibirData( );
 this->cargarComandos(*this->socketServidor->getClientComand());
 this->comando=this->socketServidor->getClientComand();
  printf("recibe el comando action: %d\n", this->comando->action );
 return result;
 }



  void* ModeloServidor::receiveDataGeneral( int socketCliente )
{
 int result=this->socketServidor->recibirDataGeneral( socketCliente);
 this->cargarComandos(*this->socketServidor->getClientComand());
 //this->comando=this->socketServidor->getClientComand();
  printf("recibe el comando action: %d\n", this->comando->action );
 //return result;
 }

void ModeloServidor::desencolar(int clients)//es un vector que tiene clientes
{

    Comandito* comandato=comando;
  pthread_mutex_t colaMutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_lock(&colaMutex);

    int action=this->colaComando.back(   ).action;
    this->processData(action);
    this->colaComando.pop_back(   );

    this->send_message(clients,&this->modelo);
    pthread_mutex_unlock(&colaMutex);

    //return 0;
}


 /* Send message to all clients except sender */
void ModeloServidor::send_message(int clients, Modelito* modelito){
 pthread_mutex_t colaMutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&colaMutex);

	/*for(int i=0; i<MAX_CLIENTS; ++i){
		this->sendDataGeneral(clients{i},*modelito);

	}*/

	pthread_mutex_unlock(&colaMutex);
}

 int  ModeloServidor::sendData( )
 {
    int result=this->socketServidor->enviarData(  &this->modelo);
    return result;
 }

  int  ModeloServidor::sendDataGeneral(int cliente, Modelito* modelito )
 {
    int result=this->socketServidor->enviarDataGeneral(cliente,  modelito);
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
this->colaSocketCliente.push_back(  this->client_socket);
 printf("acepto al socket %d\n", 1);
 return result;

}

int ModeloServidor::closeSocket()
{
 return this->socketServidor->cerrar();

}

int ModeloServidor::socketAceptando(SocketServidor* unSocket)
{
this->socketServidor=unSocket;


int a=this->bindSocket( );

int b=this->escuchar();




int c=this->aceptandoConexiones();

if(a+b+c==0)
{

//this->colaSocket.push_back(  this->socketServidor);
 printf("acepto al socket %d\n", 1);

}



}
