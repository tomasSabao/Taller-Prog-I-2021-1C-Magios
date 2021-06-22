#include "ModeloServidor.h"
#include "Thread.h"
ModeloServidor::ModeloServidor(int port = 5050)
{
  Modelo m;
  this->modelo = m;
  this->modelo.positionX=0;
  this->modelo.positionY=0;

  //tengo que asignar a los mensaje un tamanio
  this->buffer_rta_login.asignarMemoria(1,1);
  this->buffer_login.asignarMemoria(34,1);
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

void* ModeloServidor::funcionThreadRecibir(void* contexto){
  while(1){
    ( ((ModeloServidor*)contexto)->recibirDataGeneral2());
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

void* ModeloServidor::recibirDataGeneral2(){
 // printf("Entra a la funcion: recibirDataGenral2\n");
  if(!this->colaSocketCliente.empty()){
    int socketClienteActual=this->colaSocketCliente[this->numeroThread-1];
    //printf("Saque el socket de la cola de clientes. Valor del socket: %d\n",socketClienteActual);
    //por ahora siempre lleva -1 porque quiero recibir el tipo de mensaje login
    int  result=this->socketServidor->recibirData(&this->buffer_login,-1,socketClienteActual);
    if(result == 0){
      printf("Se recibio un mensaje, se procede a encolarlo en la cola de mensajes\n");
      //quiero que el decodificador me decodifique el mensaje
      //quiero que se me guarde en algun lado el mensaje
      Mensaje* un_mensaje=new Mensaje();
      un_mensaje->asignarMemoria(this->buffer_login.getTamanio(),1);
      //se copia el contenido al mensaje
      memcpy(un_mensaje->getMensaje(),this->buffer_login.getMensaje(),this->buffer_login.getTamanio());
      this->encolarMensaje(un_mensaje);
      //this->decodificador.decodificarMensajeDos(this->buffer_login.getMensaje());
      printf("Sale de la funcion: recibirDataGeneral2\n");
      //printf("no guarde ningun comando, lo recibi y lo decodifique\n");
    }

  }
  return NULL;
}



void* ModeloServidor::funcionThreadDesencolarYProcesar(void* context){
  while(1){

    ((ModeloServidor*)context)->desencolarYProcesarMensaje();

  }
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



int  ModeloServidor::recibirMensaje(){
  //return this->socketServidor->
  return 0;
}



void ModeloServidor::encolarMensaje(Mensaje* msj){
  pthread_mutex_t colaMutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_lock(&colaMutex);
  printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX Se agrega el mensaje a la cola de mensajes a procesar\n");
  this->cola_mensajes.push_back(msj);

  pthread_mutex_unlock(&colaMutex);
}



int ModeloServidor::desencolarYProcesarMensaje(){
  pthread_mutex_t colaMutex= PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_lock (&colaMutex);
  int tamanio_cola=this->cola_mensajes.size();
  if(tamanio_cola==0){
    //no hay mensajes para desencolar, no se hace nada
    pthread_mutex_unlock(&colaMutex);
    return 1;
  }
  //en este caso tengo mensajes para desencolar y procesar
  //desencolo el primer mensaje de la cola
  Mensaje* msj_desencolado= this->cola_mensajes.front();
  //se borra el primer mensaje de la cola
  this->cola_mensajes.erase(this->cola_mensajes.begin());
  pthread_mutex_unlock(&colaMutex);
  //se procesa el mensaje
  this->procesarMensaje(msj_desencolado);
  msj_desencolado->liberarMemoria();


}


int ModeloServidor::procesarMensaje(Mensaje* msj){

  //lo que voy a hacer aca por ahora es codificar una respuesta de login postivia, mandandole un id

  int success= this->codificador.codificarMensajeSalaVaciaAceptacion(&this->buffer_rta_login, '1', MAX_CLIENTS);
  if(success==0){
    //se codifico correctamente el menstaje, vamos a encolarlo
    this->encolarMensajeAEnviar(&this->buffer_rta_login);
    printf("El mensaje que se va a enviar es: \n");
    this->decodificador.decodificarMensajeDos(this->buffer_rta_login.getMensaje());
    return 0;
  }
  printf("El mensaje no fue procesado correctamente\n");
  return 1;
}



int ModeloServidor::desencolarYEnviarMensaje(){
  //printf("------------Thread: desencolar y enviar mensaje. Accedo a la cola de mensajes a enviar\n");
  pthread_mutex_t colaMutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_lock(&colaMutex);
  int numero_msjs=this->cola_mensajes_a_enviar.size();
  if(numero_msjs== 0){
    //no tengo mensajes para enviar
    //printf("No tengo mensajes para enviar\n");
    //printf("-------------Thread: desencolar y enviar mensaje. Salgo del thread \n");
    pthread_mutex_unlock(&colaMutex);
    return 1;
  }
  //tengo mensajes para enviar
  printf("----------- Thread: envio de mensaje. Tengo mensajes para enviar---------------\n");
  Mensaje* msj_desencolado=this->cola_mensajes_a_enviar.front();
  this->cola_mensajes_a_enviar.erase(this->cola_mensajes_a_enviar.begin());
  pthread_mutex_unlock(&colaMutex);

  this->enviarMensaje(msj_desencolado,msj_desencolado->getTamanio());
  return 0;
}


int ModeloServidor::encolarMensajeAEnviar(Mensaje* msj){
  pthread_mutex_t colaMutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_lock(&colaMutex);


  this->cola_mensajes_a_enviar.push_back(msj);

  pthread_mutex_unlock(&colaMutex);
  return 0;
}

int ModeloServidor::enviarMensaje(Mensaje* msj,int tamanio_bytes){
  printf("--------------- Thread: Se va a enviar un mensaje ---------\n");
  int resultado=this->socketServidor->enviarData(msj,tamanio_bytes);
  return resultado;
}


void* ModeloServidor::funcionThreadDesencolarYEnviar(void* context){
  while(1){
    ((ModeloServidor*)context)->desencolarYEnviarMensaje();
  }
  return NULL;
}