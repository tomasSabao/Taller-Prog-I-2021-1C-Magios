#include "ModeloCliente.h"


ModeloCliente::ModeloCliente()
{
    Modelo m;
    m.positionX=0;
    m.positionY=0;
    this->modelo = &(m);
    this->estaConectado=false;
    //despues se redimensiona, pero es necesario para
    //que no haya segmentation fault
    this->envio_msj_login.asignarMemoria(1,1);
    this->recibir_msj_login.asignarMemoria(1,1);
   // Comando c;
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


int ModeloCliente::cargarComandos(Comando comando)
{

  Comando comandato = comando;
  pthread_mutex_t colaMutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_lock(&colaMutex);
  printf("recibi el camondo de cargarcomando %d\n", comando.action);
  this->colaComando.push_back(comandato);
  pthread_mutex_unlock(&colaMutex);
  return 0;
}


int ModeloCliente::cargarMensaje(Mensaje* msj){
  printf("funcion CargarMensaje, entro\n");
    pthread_mutex_t colaMutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&colaMutex);
    this->colaMensajes.push_back(msj);
    pthread_mutex_unlock(&colaMutex);
  printf("Funcion cargarMensaje, salgo\n");
    return 0;
}

void* ModeloCliente::desencolar( )
{

//  Comando *comandato = comando;
  pthread_mutex_t colaMutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_lock(&colaMutex);

  if(!this->colaComando.empty() && this->estaConectado )
  {
  //Comando comandito = this->colaComando.back();
  //printf("desencole el camondo de cargarcomando %d\n",  comandito.action);

  this->sendData(&this->colaComando.back());
  this->colaComando.pop_back();



  pthread_mutex_unlock(&colaMutex);
  }



   return NULL;
}


//desencolar mensaje saca el mensaje de la cola y lo manda
Mensaje* ModeloCliente::desencolarMensaje(){
  Mensaje* msj_desencolado=NULL;
  pthread_mutex_t colaMutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_lock(&colaMutex);

  //las condiciones son: la cola de mensajes no este vacia, y esta conectado el cliente
  if(this->colaMensajes.size()!=0   &&   this->estaConectado == true){
    msj_desencolado=this->colaMensajes.back();
    this->colaMensajes.pop_back();
  }
  pthread_mutex_unlock(&colaMutex);
  printf("Valor del mensaje desencolado: %d\n",msj_desencolado);
  return msj_desencolado;
}


void ModeloCliente::initializeData(int action)
{

}

//wrapper para la funcion recibirDatosUsuario
void* ModeloCliente::funcionParaThread(void* context){
  while(1){
      ((ModeloCliente *)context)->recibirUsuarioContrasenia();
  }

  return NULL;
}


void* ModeloCliente::threadFunctionRecibir(void* context){

  while(1){
    ((ModeloCliente*)context)->recibirDataGeneral2();
  }
  return NULL;
}

//se tiene que desencolar el mensaje de la cola, y se tiene que enviar
void* ModeloCliente::threadFunctionEnviar(void* context){
  printf("Funcion: threadEnviar\n");
  bool estaConectado= ((ModeloCliente*)context)->getEstaConectado();
  Mensaje* msj_a_mandar=NULL;
  void* contenido=NULL;
  int tamanio_msj;
  while(1){
    ((ModeloCliente*)context)->manejadora();
  }
  printf("Funcion threadEnviar. FIN\n");
  return NULL;
}

void ModeloCliente::manejadora(){
  int resultado;
  if(this->getEstaConectado()==true && this->colaMensajes.size()!=0){
    printf("Se va a mandar un mensaje\n");
    Mensaje* msj_a_mandar=this->desencolarMensaje();
    int tamanio_msj=msj_a_mandar->getTamanio();
    void* contenido=msj_a_mandar->getMensaje();
    resultado=this->enviarMensaje(contenido,tamanio_msj);
    if(resultado==0){
      printf("Se mando un mensaje correctamente\n");
    }
    else{
      printf("Error al mandar mensaje\n");
    }
  }
 // printf("Sali de funcion manejadora\n");
}

  void *ModeloCliente::hello_helperRecieve(void *context)
    {

    while(1)
    {
    ((ModeloCliente *)context)->receiveData( );

    }




        return NULL;
    }


      void *ModeloCliente::hello_helperSend(void *context)
    {



     while(1)
    {
        ((ModeloCliente *)context)->desencolar( );
    }


        return NULL;
    }

    void *ModeloCliente::hello_helperIngresarDatos(void *context)
    {



     while(1)
    {
        ((ModeloCliente *)context)->recibirDatosUsuario();
    }


        return NULL;
    }


  void ModeloCliente::recibirDatosUsuario()
 {
    if(this->estaConectado==true)
    {
  cout << "Hola! ingrese un comando , si ingresa 1 aumenta eje y si ingresa 2 aumenta eje x" << "\n"  ;
    //La instrucción \n es un salto de línea Mostrando los textos separados

        int comando;//En esta variable estará almacenado el nombre ingresado.
        cin >> comando; //Se lee el nombre

        cout << "Bienvenido al sistema " << comando << ". Gracias por usar nuestra aplicación" << "\n";
        Comando command;
        command.action = comando;

        this->cargarComandos(command);

        }

 }








void ModeloCliente::ImprimirModeloActualizado()
 {

   printf("Receive data: pos(X,Y) = (%d,%d)\n\n", this->modelo->positionX, this->modelo->positionY );
 }



int ModeloCliente::recibirMensaje(int tamanio_msj, void* buffer){

  int resultado=this->socketCliente->recibirData(tamanio_msj,buffer);
  if(resultado==0){//funciono el recibir data
    //hago algo con el modelo. Creo que conviene llamar al decodificador
    this->decodificador.decodificarMensajeDos(buffer);

  }

  return resultado;
}


int ModeloCliente::sendData(Comando* comando)
{



    int result = this->socketCliente->enviarData(comando);
    return result;
}


int ModeloCliente::enviarMensaje(void* msj, int tamanio_bytes){
  int resultado= this->socketCliente->enviarData(msj,tamanio_bytes);
  return resultado;
}


int ModeloCliente::conectar()

{

     int conectar=this->socketCliente->conectar();
       if(conectar==0)
          {
            this->estaConectado=true;
            return conectar;
          }

          return -1;


}

int ModeloCliente::closeSocket()
{
    return this->socketCliente->cerrar();
}


bool ModeloCliente::getEstaConectado(){
  return this->estaConectado;
}

int ModeloCliente::recibirUsuarioContrasenia(){
  int success=0;
  std::string usuario="";
  std::string contrasenia="";

  char buffer_usr_str[16];
  char buffer_psw_str[16];
  printf("Ingrese usuario: \n");
  scanf("%s" ,buffer_usr_str);
  for(int i=0; i<15; i++){
    if (buffer_usr_str[i]==0){
      break;
    }
    usuario+=buffer_usr_str[i];
  }
  printf("Ingrese contrasenia:  \n");
  scanf("%s" ,buffer_psw_str);
  for(int i=0;i<15;i++){
    if(buffer_psw_str[i]==0){
      break;
    }
    printf("%c\n",buffer_psw_str[i]);
    contrasenia+=buffer_psw_str[i];
  }
  printf("Voy a entrar al codificador\n");
  success=this->codificador.codificarMensajeConexionDos(&this->envio_msj_login, usuario, contrasenia);
  //saco el mutex

  //meter el mensaje en la cola
  this->cargarMensaje(&this->envio_msj_login);
  printf("Fin de funcion usuario contrasenia\n");

  //la mando

  return success;
}


bool ModeloCliente::getEstaConectadoServidor(){
  return this->estaConectadoAlServidor;
}



int ModeloCliente::receiveData()
{




    int result = this->socketCliente->recibirData();
    if(result)
    {

     this->modelo = this->socketCliente->getServerModel();

    }

    this->ImprimirModeloActualizado();


    return result;
}



void* ModeloCliente::recibirDataGeneral2(){
 // printf("Entra a la funcion: recibirDataGenral2\n");
  int estado_conexion=this->estaConectadoAlServidor;
  if(estado_conexion==true){
    //El cliente esta conectado al servidor, por lo que va a recibir mensajes de actualizacion de posiciones
    //TODO
  }
  else{
    //el cliente no esta conectado al servidor, por lo que va a recibir mensajes de aceptacion/rechazo de login
    int resultado= this->socketCliente->recibirData(1,&this->recibir_msj_login);
    //veo que pasa con el resultado del servidor
    if(resultado == 0){
      printf("Se recibio un mensaje del servidor, se procede a decodificarlo\n");
      this->decodificador.decodificarMensajeDos(this->recibir_msj_login.getMensaje());
    }
  }
  return NULL;
}