#include "ModeloServidor.h"
#include "Thread.h"
#include "../../lib/Parser.h"
#include "../../Modelo/Modelo.h"


#define TIPO_TECLA 0
#define TIPO_LOGIN 1
#define TIPO_ACEPTACION 2
#define TIPO_SALA_LLENA 3
#define TIPO_ERROR_LOGIN 4
#define TIPO_ACTUALIZAR 5

extern Parser parser;


ModeloServidor::ModeloServidor(Modelo* modeloJuego, int port)
{
    int cantidad_jugadores = modeloJuego->getCantJugadores();

    if (cantidad_jugadores > 0)
    {
      // necesito modelo_jugador para hacer cambios
      //el ultimo o el primero?
      this->modelo_jugador = modeloJuego->getModeloJugador(cantidad_jugadores-1);
    } else {
      this->modelo_jugador = new Modelo_Jugador("",0,0);
    }
    
    //Modelo m;
    //this->modelo = m;
    //this->modelo.positionX=0;
    //this->modelo.positionY=0;
    this->cantidadJugadoresActuales=0;
    this->id=0;
    /*this->CrearSocket(port);
    this->bindSocket();
    this->escuchar();
    this->numeroThread=0;*/
    //this->colaComando=NULL;
    this->buffer_rta_login.asignarMemoria(1,1);
    this->buffer_login.asignarMemoria(34,1);
    this->modelo_juego = modeloJuego;

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

void* ModeloServidor::funcionThreadRecibir(void* context){
  while(1){
    ((Tupla*)context)->unModelo->recibirDataGeneral2(((Tupla*)context)->idSocket);
  }
  return NULL;
}

void* ModeloServidor::recibirDataGeneral2(int socket_del_thread){
  if(!this->colaConexiones.empty()){
    int socketDeEsteThread=this->colaConexiones[socket_del_thread-1].getConexion() ;
    //printf("Saque RECIBE el socket de la cola de clientes numero: %d\n",socketDeEsteThread);
    //TODO:logica que especifique el tamaño del mensaje a recibir segun el estado del servidor
    //por ahora se hardcodea a un mensaje de recepcion de login positivo
    bool resultado= this->socketServidor->recibirData(&this->buffer_login,-1,socketDeEsteThread);
    if(resultado == 0){
      printf("Se recibio un mensaje, se procede a encolarlo en la cola de mensajes\n");
      Mensaje* unMensaje=new Mensaje();
      unMensaje->asignarMemoria(this->buffer_login.getTamanio(),1);
      memcpy(unMensaje->getMensaje(),this->buffer_login.getMensaje(),this->buffer_login.getTamanio());
      //se encola el mensaje
      this->encolarMensaje(unMensaje);
    }
    else{
      //printf("No se recibio mensaje, no se encola nada\n");
    }
  }
  else{
    printf("La cola de conexiones esta vacia\n");
  }
  return NULL;
}

void* ModeloServidor::funcionThreadDesencolarYProcesar(void* context){
  while(1){
    // printf("Thread desencolar y procesar\n");
    ((ModeloServidor*)context)->desencolarYProcesarMensaje();
  }
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

void ModeloServidor::encolarMensaje(Mensaje* msj)
{
  pthread_mutex_t colaMutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_lock(&colaMutex);
  printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX Se agrega el mensaje a la cola de mensajes a procesar\n");
  this->cola_mensajes.push_back(msj);

  pthread_mutex_unlock(&colaMutex);
}

int ModeloServidor::desencolarYProcesarMensaje()
{
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

int ModeloServidor::procesarMensaje(Mensaje* msj)
{
  //lo que voy a hacer aca por ahora es codificar una respuesta de login postivia, mandandole un id

  int success= this->codificador.codificarMensajeSalaVaciaAceptacion(&this->buffer_rta_login, '1', MAX_CLIENTS);
  //int success= this->codificador.codificarMensajeSalaLlenaRechazo(msj);
  printf("Valor del mensaje una vez codificado: %d\n",*(unsigned char*)msj->getMensaje());
  if(success==0){
    //se codifico correctamente el menstaje, vamos a encolarlo
    //necesito una copia
    Mensaje* msj_aux=new Mensaje();
    msj_aux->asignarMemoria(1,1);
    memcpy(msj_aux->getMensaje(),this->buffer_rta_login.getMensaje(),1);
    if (this->decodificador.obtenerTipo(msj) == TIPO_LOGIN) {
      std::string username = this->decodificador.obtenerUsuario(msj);
      std::string password = this->decodificador.obtenerContrasenia(msj);
      //TODO: ver si ya esta conectado ese jugador.
      if (parser.validarJugador(username,password)) {
        //ver si ese jugador ya esta conectado.
        int id = 5;
        this->modelo_juego->agregarJugador(username, id);
      }
    } else if (this->decodificador.obtenerTipo(msj) == TIPO_TECLA) {
      int id = this->decodificador.obtenerIdJugador(msj);
      int tecla = this->decodificador.obtenerTecla(msj);
    }

    //this->decodificador.decodificarMensajeDos(this->buffer_rta_login.getMensaje());

    printf("Valor de copia: %d\n",*(unsigned char*)msj->getMensaje());
    this->encolarMensajeAEnviar(msj_aux);
    //this->decodificador.decodificarMensajeDos(this->buffer_rta_login.getMensaje());
    return 0;
  }
  printf("El mensaje no fue procesado correctamente\n");
  return 1;
}

int ModeloServidor::desencolarYEnviarMensaje()
{
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
  printf("Antes de entrar a la funcion de envio, valor del mensaje: %d\n",*(unsigned char*)msj_desencolado->getMensaje());
  this->enviarMensaje(msj_desencolado,msj_desencolado->getTamanio());
  return 0;
}

int ModeloServidor::encolarMensajeAEnviar(Mensaje* msj)
{
  pthread_mutex_t colaMutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_lock(&colaMutex);


  this->cola_mensajes_a_enviar.push_back(msj);

  pthread_mutex_unlock(&colaMutex);
  return 0;
}

int ModeloServidor::enviarMensaje(Mensaje* msj,int tamanio_bytes)
{
  printf("--------------- Thread: Se va a enviar un mensaje ---------\n");
  //printf("Se decodifica el mensaje a mandar: \n");
  //this->decodificador.decodificarMensajeDos(msj->getMensaje());
  int resultado=this->socketServidor->enviarData(msj,tamanio_bytes);
  return resultado;
}

void* ModeloServidor::funcionThreadDesencolarYEnviar(void* context)
{
  while(1){
    ((ModeloServidor*)context)->desencolarYEnviarMensaje();
  }
  return NULL;
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
      int socketDeEsteThread=this->colaConexiones[socketdeesethread-1].getConexion();
      printf("saque  RECIBE el socket de la cola de clientes numero : %d\n", socketDeEsteThread);
      bool result = this->socketServidor->recibirDataGeneral(socketDeEsteThread);
      if (result == true){
          this->cargarComandos(*this->socketServidor->getClientComand());
          //TODO: aca iria lo del username?
          printf("guarde el comando definitivamente a la coladecomando : %d\n",this->socketServidor->getClientComand()->action);
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


Comando ModeloServidor::login(Comando comando)
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
//decodificador ->gettecla()
  switch (comando.action)
  {
  case 1: //arriba
    printf("muevo a eje y inicial: %d\n", this->modelo_jugador->getPosicionY());
    this->modelo_jugador->setPosicionX(this->modelo_jugador->getPosicionY() + this->modelo_jugador->getVelocidadX());
    printf("muevo a eje y siguiente: %d\n", this->modelo_jugador->getPosicionY());
    break;
  case 3: //izquierda
    this->modelo_jugador->setPosicionX(this->modelo_jugador->getPosicionX() - this->modelo_jugador->getVelocidadX());
    break;
  case 2:
  //arriba
   this->modelo_jugador->setPosicionY(this->modelo_jugador->getPosicionY() + this->modelo_jugador->getVelocidadY());
    break;
  case 4:
  //abajo
   this->modelo_jugador->setPosicionY(this->modelo_jugador->getPosicionY() + this->modelo_jugador->getVelocidadY());
    break;
  }

}

void* ModeloServidor::desencolar() //es un vector que tiene clientes
{
  pthread_mutex_t colaMutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_lock(&colaMutex);

  while(!this->colaComando.empty()&&!this->colaConexiones.empty())
  {
     int action = this->colaComando.back().action;

     printf("desencole el camondo de cargarcomando %d\n", action);

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

void *ModeloServidor::manejoCliente()
{
    return NULL;
}

void ModeloServidor::initializeData()
{
  this->modelo_jugador->setPosicionX(0);
  this->modelo_jugador->setPosicionY(0);
  //this->View.positionX=0;
}

int ModeloServidor::getPosicionX()
{
  return this->modelo_jugador->getPosicionX();
}

int ModeloServidor::getPosicionY()
{
  return this->modelo_jugador->getPosicionY();
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
  printf("muevo derecha: %d\n", this->modelo_jugador->getPosicionX());

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
    Conexion* unaConexion = new Conexion();
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
