#include "ModeloCliente.h"


ModeloCliente::ModeloCliente()
{
    Modelo m;
    m.positionX=0;
    m.positionY=0;

    Comando co;
    co.action=0;
    co.password=0;
    this->modelo = &(m);
    this->estaConectado=false;
    this->unComando=&(co);
    this->activo;
    this->indentificadorCliente;
    this->contador=0;

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


  pthread_mutex_t colaMutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_lock(&colaMutex);
  Comando comandato = comando;
  printf("recibi el camondo de cargarcomando %d\n", comando.action);
  printf("recibi el camondo de nombre %d\n", comando.nombre);
  this->colaComando.push_back(comandato);
  pthread_mutex_unlock(&colaMutex);
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


void ModeloCliente::initializeData(int action)
{

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



     void *ModeloCliente::threadLogin(void *context)
    {



     while(1)
    {
        ((ModeloCliente *)context)->hiloLogin( );
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


  void* ModeloCliente::hiloLogin()
  {

  //  pthread_mutex_t colaMutexx = PTHREAD_MUTEX_INITIALIZER;
  //pthread_mutex_lock(&colaMutexx);

     if(this->estaConectado==true)
    {

    if(this->activo==false)
    {

      int nombre;
    printf("Hola! ingrese el nombre x\n");
    scanf("%d", &nombre);

     int password;
    printf("Hola! ingrese el password \n");
    scanf("%d", &password);

    Comando command;
        command.nombre = nombre;
        command.password=password;
        command.tipo=1;
        this->cargarComandos(command);
     }

  if(!this->activo)
  {

 int result2 = this->socketCliente->recibirDataComando();
    if(result2)
    {
        this->unComando = this->socketCliente->getServerComando();
        if(this->unComando->tipo==11)
        {
            this->indentificadorCliente=this->unComando->action;
            this->activo=true;
            printf("logeado correcto");
             this->contador=this->contador+1;
        }else{
            printf("logeado incorrecto");
        }
    }

  }

  }
 // pthread_mutex_unlock(&colaMutexx);

}

  void* ModeloCliente::recibirDatosUsuario()
 {


     if(this->activo)
     {

     printf("Hola! ingrese un comando , si ingresa 1 aumenta eje y si ingresa 2 aumenta eje x\n");

        int comando;//En esta variable estará almacenado el nombre ingresado.
         scanf("%d", &comando);


        Comando command;
        command.action = comando;
         command.tipo=2;

        this->cargarComandos(command);

     }












 }




void ModeloCliente::ImprimirModeloActualizado()
 {

   printf("Receive data: pos(X,Y) = (%d,%d)\n\n", this->modelo->positionX, this->modelo->positionY );
 }

int ModeloCliente::receiveData()
{





if(this->activo)
{
int result = this->socketCliente->recibirData();

    if(result)
    {

     this->modelo = this->socketCliente->getServerModel();

    }
     this->ImprimirModeloActualizado();

}











    return 0;
}


int ModeloCliente::sendData(Comando* comando)
{



    int result = this->socketCliente->enviarData(comando);
    return result;
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
