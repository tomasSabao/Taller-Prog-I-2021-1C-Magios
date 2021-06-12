#include "ModeloServidor.h"
#include "Thread.h"
ModeloServidor::ModeloServidor(int port = 5050)
{
  Modelo m;
  this->modelo = m;
  this->modelo.positionX=0;
  this->modelo.positionY=0;
  /*this->CrearSocket(port);
  this->bindSocket();
  this->escuchar();
  this->numeroThread=0;*/
  //this->colaComando=NULL;
}
 int ModeloServidor::getNumeroThread()
 {
    return this->numeroThread;
 }
 int ModeloServidor::guardarCliente( int clienteSocket )
    {

        pthread_mutex_t colaMute = PTHREAD_MUTEX_INITIALIZER;
        pthread_mutex_lock(&colaMute);

        this->numeroThread=  this->numeroThread+1 ;
         printf("numero thread : %d\n", this->numeroThread  );

        this->colaSocketCliente.push_back(clienteSocket);
        printf("guardo el cliente en la cola cliente %d\n",clienteSocket);

         pthread_mutex_unlock(&colaMute);
        return  0;
    }

  void *ModeloServidor::hello_helperRecieve(void *context)

    {

        while(1)
        {
         ((ModeloServidor *)context)->receiveDataGeneral( );

        }

        return NULL;

    }


     void *ModeloServidor::hello_helperDesencolar(void *context)

    {

        while(1)
        {

        ((ModeloServidor *)context)->desencolar();
        }

        return NULL;
//
    }




   void *ModeloServidor::receiveDataGeneral( )
{
    if (!this->colaSocketCliente.empty())
  {
     int socketClienteActual=this->colaSocketCliente[this->numeroThread-1];
     printf("saque el socket de la cola de clientes numero : %d\n", socketClienteActual);
     bool result = this->socketServidor->recibirDataGeneral(socketClienteActual);
     if(result== true){
        this->cargarComandos(*this->socketServidor->getClientComand());
         printf("guarde el comando definitivamente a la coladecomando : %d\n",this->socketServidor->getClientComand()->action );
        }
  }


 return NULL;


}

void* ModeloServidor::desencolar( ) //es un vector que tiene clientes
{


  pthread_mutex_t colaMutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_lock(&colaMutex);

  while(!this->colaComando.empty()&&!this->colaSocketCliente.empty())
  {

     int action = this->colaComando.back().action;

     printf("desencole el camondo de cargarcomando %d\n",  action);
     this->processData(action);
     printf("procese ese action\n");
     this->colaComando.pop_back();


     for (int i = 0; i < this->colaSocketCliente.size(); i++) {


            this->sendDataGeneral(this->colaSocketCliente[i],&this->modelo);

        }

  }



pthread_mutex_unlock(&colaMutex);
  //return 0;
}


ModeloServidor::~ModeloServidor()
{
  //dtor
}

void *ModeloServidor::manejoCliente( )
{
    return NULL;
}
void ModeloServidor::initializeData()
{

  this->modelo.positionX = 0;
  this->modelo.positionY = 0;

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

void ModeloServidor::processData(int action)
{
  switch (action)
  {
  case 1: //derecha
    printf("muevo a eje y inicial: %d\n", this->modelo.positionY);
    this->modelo.positionY = this->modelo.positionY + 1;
    printf("muevo a eje y siguiente: %d\n", this->modelo.positionY);

    break;
  case 3: //izquierda

    this->modelo.positionY = this->modelo.positionY - 1;

    break;
  case 2:
    this->modelo.positionX = this->modelo.positionX + 1;
    break;
  case 4:
    this->modelo.positionX = this->modelo.positionX - 1;
    break;
  }
}



int ModeloServidor::cargarComandos(Comando comando)
{


  pthread_mutex_t colaMutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_lock(&colaMutex);
  Comando comandato = comando;
  printf("recibi el camondo de cargarcomando %d\n", comando.action);
  this->colaComando.push_back(comandato);
  pthread_mutex_unlock(&colaMutex);
  return 0;
}


void ModeloServidor::imprimirComandos()
{
  printf("muevo derecha: %d\n", this->modelo.positionX);

  pthread_mutex_t colaMutex = PTHREAD_MUTEX_INITIALIZER;
  for (int i = 0; i < this->colaComando.size(); i++)
  {

    pthread_mutex_lock(&colaMutex);
    printf("muevo derecha: %d\n", this->colaComando[i].action);

    pthread_mutex_unlock(&colaMutex);
  }
}

int ModeloServidor::CrearSocket(int puerto)
{
  this->socketServidor = new SocketServidor(puerto);
  this->socketServidor->crearSocket();

  return 0;
}

int ModeloServidor::getCliente()
{

  return this->client_socket;
}




int ModeloServidor::sendDataGeneral(int cliente, Modelo *modelito)
{
  int result = this->socketServidor->enviarDataGeneral(cliente, modelito);
  return result;
}

int ModeloServidor::bindSocket()
{
  return this->socketServidor->bindSocket();
}
int ModeloServidor::escuchar()
{
  return this->socketServidor->escuchar();
}

int ModeloServidor::aceptandoConexiones()
{
  int result = this->socketServidor->aceptandoConexiones();

  if(result==1)
  {

    printf("acepto algo que no era un socket valido, no guardo cliente");

  }else{

      this->client_socket = this->socketServidor->getClientSocket();
      this->guardarCliente(this->socketServidor->getClientSocket());
  }


  return result;
}

int ModeloServidor::closeSocket()
{
  return this->socketServidor->cerrar();
}



