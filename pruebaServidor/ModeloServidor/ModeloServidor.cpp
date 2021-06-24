#include "ModeloServidor.h"
#include "Thread.h"


ModeloServidor::ModeloServidor(int port)
{
    Modelito m;
    this->modelo = m;
    this->modelo.positionX=0;
    this->modelo.positionY=0;
    this->cantidadJugadoresActuales=0;
    this->id=0;
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

int ModeloServidor::guardarCliente(int clienteSocket)
{
    pthread_mutex_t colaMute = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&colaMute);

    this->numeroThread= this->numeroThread+1;
    printf("numero thread : %d\n", this->numeroThread);

    this->colaSocketCliente.push_back(clienteSocket);
    printf("guardo el cliente en la cola cliente %d\n",clienteSocket);

    pthread_mutex_unlock(&colaMute);
    return 0;
}

int ModeloServidor::guardarConexion(Conexion* unaConexion)
{
  pthread_mutex_t colaMute = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_lock(&colaMute);
  printf("numero thread : %d\n", unaConexion->getId());

  this->colaConexiones.push_back(*unaConexion);
  printf("guardo el cliente en la cola cliente %d\n",unaConexion->getConexion());

  pthread_mutex_unlock(&colaMute);
  return 0;
}


void *ModeloServidor::hello_helperRecieve(void *context)
{
  while(1)
  {

         ((Tupla *)context)->unModelo->receiveDataGeneral(((Tupla *)context)->idSocket);

        }

        return NULL;

}

    /*void *ModeloServidor::hello_helperRecieve2(void *context)
    {
        while(1)
        {
         ((ModeloServidor *)context)->receiveDataGeneral( );

        }
        return NULL;
    }

    void *ModeloServidor::receiveDataGeneral2(int socketdeesethread )
{
    if (!this->colaConexiones.empty())
  {
       //for (int i = 0; i < this->colaConexiones.size(); i++) {

         int socketDeEsteThread=socketdeesethread;
         printf("saque  RECIBE el socket de la cola de clientes numero : %d\n", socketDeEsteThread);
         bool result = this->socketServidor->recibirDataGeneral(socketDeEsteThread);
         if(result== true){
            this->cargarComandos(*this->socketServidor->getClientComand());
             printf("guarde el comando definitivamente a la coladecomando : %d\n",this->socketServidor->getClientComand()->action );
            }
  }

 //}
 return NULL;


}*/

void *ModeloServidor::hello_helperDesencolar(void *context)
{
  while(1)
  {
    ((ModeloServidor *)context)->desencolar();
  }

  return NULL;
//
}


/*
void* ModeloServidor::crearThread(void *algunaFuncion(void*))
{
    pthread_t hilos[3];
   pthread_create(&hilos[this->id],NULL, &ModeloServidor::hello_helperRecieve,NULL);
  return NULL;
}

void * ModeloServidor::receiveDataGeneral(void *context )
{
    ((ModeloServidor *)context)->desencolar();
    while(1)
        {
    if (!((ModeloServidor *)context)->colaConexiones.empty())
  {
    /* int socketClienteActual=this->colaSocketCliente[this->numeroThread-1];
     printf("saque el socket de la cola de clientes numero : %d\n", socketClienteActual);
     bool result = this->socketServidor->recibirDataGeneral(socketClienteActual);
     if(result== true){
        this->cargarComandos(*this->socketServidor->getClientComand());
         printf("guarde el comando definitivamente a la coladecomando : %d\n",this->socketServidor->getClientComand()->action );
        }
  }
    }
 return NULL;
}
*/

void *ModeloServidor::receiveDataGeneral(int socketdeesethread)
{
  if (!this->colaConexiones.empty())
  {
       //for (int i = 0; i < this->colaConexiones.size(); i++) {
      int socketDeEsteThread=this->colaConexiones[socketdeesethread-1].getConexion() ;
      printf("saque  RECIBE el socket de la cola de clientes numero : %d\n", socketDeEsteThread );
      bool result = this->socketServidor->recibirDataGeneral(socketDeEsteThread );
      if(result== true){
          this->cargarComandos(*this->socketServidor->getClientComand());
          printf("guarde el comando definitivamente a la coladecomando : %d\n",this->socketServidor->getClientComand()->action );
      }
  }
//}

 return NULL;
}

/*
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


}*/



Comando  ModeloServidor::login(Comando comando)
{
 printf("tipo es : %d\n",comando.tipo);

    int passwordjugador1=101;// la base
    int passwordjugador2=102;// la base
    int passwordjugador3=103;// la base
    int passwordjugador4=104;// la base
    int passwordjugador5=105;// la base
    int passwordjugador6=106;// la base

    int nombrejugador1=101;// la base
    int nombrejugador2=102;// la base
    int nombrejugador3=103;// la base
    int nombrejugador4=104;// la base
    int nombrejugador5=105;// la base
    int nombrejugador6=106;// la base

    printf("password1 del juegador1 es: %d\n", passwordjugador1);
    printf("nombredel juegador1 es: %d\n", nombrejugador1);
    printf("comando desencolado el password : %d\n", comando.password);
    printf("comando desencolado el nombre : %d\n",  comando.nombre);

    bool logeado=false;

    if(comando.password==passwordjugador1)
    {

      logeado=true;
      }else if(comando.password==passwordjugador2)
      {
          logeado=true;
      }else if(comando.password==passwordjugador3)
      {
         logeado=true;
      }else if(comando.password==passwordjugador4)
      {
           logeado=true;
      }else if(comando.password==passwordjugador5)
      {
         logeado=true;
      }else if(comando.password==passwordjugador6)
      {
          logeado=true;
      }
      Comando comandoLogin;
      if(logeado)
      {
        this->cantidadJugadoresActuales=this->cantidadJugadoresActuales+1;
        comandoLogin.action=this->cantidadJugadoresActuales;
        comandoLogin.tipo=11;
        printf("login correcto \n");
      } else
      {
        printf("login incorrecto \n");
        comandoLogin.action=0;
        comandoLogin.tipo=12;
      }
  return  comandoLogin;
}


void ModeloServidor::processData(Comando comando)
{
  switch (comando.action)
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

void* ModeloServidor::desencolar( ) //es un vector que tiene clientes
{

  pthread_mutex_t colaMutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_lock(&colaMutex);

  while(!this->colaComando.empty()&&!this->colaConexiones.empty())
  {
     int action = this->colaComando.back().action;

     printf("desencole el camondo de cargarcomando %d\n",  action);

     if(this->colaComando.back().tipo==1)
     {
      Comando unComando=this->login(this->colaComando.back());
       this->colaComando.pop_back();

      /*  int posicion=0;
       if(unComando.tipo==11)
            {//aca tenemos cocmo valor al principio un 1
            printf("procese ese action\n");
            this->sendDataGeneralComando(this->colaSocketCliente[unComando.action-1],&unComando);
            posicion=unComando.action-1;
            }else
            { //action siempre vale cero .
             this->sendDataGeneralComando(this->colaSocketCliente[this->cantidadJugadoresActuales],&unComando);
              posicion=this->cantidadJugadoresActuales;
            }*/

       for (int i = 0; i < this->colaConexiones.size(); i++) {
           // if(i!=posicion)
            //{
            this->sendDataGeneralComando(this->colaConexiones[i].getConexion(),&unComando);
            //}
         }

     }else if(this->colaComando.back().tipo==2)
     {
       this->processData(this->colaComando.back());

       printf("procese ese action\n");
       this->colaComando.pop_back();


      for (int i = 0; i < this->colaConexiones.size(); i++) {

            this->sendDataGeneral(this->colaConexiones[i].getConexion(),&this->modelo);
        }
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

int ModeloServidor::sendDataGeneral(int cliente, Modelito *modelito)
{
  int result = this->socketServidor->enviarDataGeneral(cliente, modelito);
  return result;
}

int ModeloServidor::sendDataGeneralComando(int cliente, Comando *comando)
{
  int result = this->socketServidor->enviarDataGeneralComando(cliente,comando) ;
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
  } else
  {
    Conexion* unaConexion= new Conexion();
    this->client_socket = this->socketServidor->getClientSocket();
    unaConexion->setearConexion(this->client_socket);
    unaConexion->setearId(this->id);
    unaConexion->setearEstado(false);

    //this->guardarCliente(this->socketServidor->getClientSocket());
    this->guardarConexion(unaConexion);
    //this->crearThread(this->receiveDataGeneral((void*)unaConexion));

    pthread_t hilos[4];
    //this->colaThread.push_back(&hilos[this->id]);
    // pthread_create(&hilos[this->id], NULL,   &ModeloServidor::hello_helperRecieve2,  this);
    this->id=this->id +1 ;
    return 0;
  }
  return result;
}

int ModeloServidor::closeSocket()
{
  return this->socketServidor->cerrar();
}
