#include "ModeloCliente.h"


ModeloCliente::ModeloCliente()
{
    Modelo m;
    m.positionX=0;
    m.positionY=0;
    this->modelo = &(m);
    this->estaConectado=false;

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
