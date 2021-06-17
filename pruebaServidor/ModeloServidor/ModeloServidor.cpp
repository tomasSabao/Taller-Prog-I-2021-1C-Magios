#include "ModeloServidor.h"
#include "Thread.h"
ModeloServidor::ModeloServidor(int port = 5050)
{
  Modelo m;
  this->modelo = m;
  this->modelo.positionX=0;
  this->modelo.positionY=0;
  this->modelo.salaLlena='n';

   this->preparadoParaJugar=false;
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


 bool  ModeloServidor::cargarClientesAdmitidos(Conexion* unaConexion) //esto quisas se tenga que hacer en dos pasos, cargar y admitir
 {
     int password=15;// la base


    //todos tienen este pasword y contrasena para facilitar prueba

    bool result = this->socketServidor->recibirDataGeneral(unaConexion->getSocket());//tres estados, uno el 0 que se desconecto



        bool  admitido= false;
        while ( !admitido&&result ){


            if(this->socketServidor->getClientComand()->action==password)
            {
                admitido=true;
                cout << "Bienvenido su contrasena correcta "  ;
                this->modelo.password=35;//correcto
                this->socketServidor->enviarDataGeneral(unaConexion->getSocket(),&this->modelo);

            }else
            {
              cout << "contrasena incorrecta , ingrese de nuevo "  ;
              this->modelo.password=36;//incorrecto
              this->socketServidor->enviarDataGeneral(unaConexion->getSocket(),&this->modelo);
               result = this->socketServidor->recibirDataGeneral(unaConexion->getSocket());

            }

        }



    return admitido;
 }


void ModeloServidor::lanzarHilo()
{

  pthread_create(this->colaHilos[this->numeroThread-1], NULL,   &ModeloServidor::hello_helperRecieve,   this);


}


void ModeloServidor::bloquearHiloMain()
{

  for (int i = 0; i < this->colaHilos.size(); i++) {
		pthread_join(*this->colaHilos[i],NULL);
		}



}

/* Remove clients to queue */
void ModeloServidor::eliminarHiloClienteDemas(Conexion* unaConexion )
{
    pthread_mutex_t colaHiloMutex = PTHREAD_MUTEX_INITIALIZER;


    pthread_mutex_lock(&colaHiloMutex);


    this->modelo.salaLlena='s';

    this->socketServidor->enviarDataGeneral(unaConexion->getSocket() ,&this->modelo);
    // erase
  this->colaHilos.erase(this->colaHilos.begin()+MAX_CLIENTS);
  this->colaConexiones.erase(this->colaConexiones.begin()+MAX_CLIENTS);
  //(this->colaConexiones.begin()+MAX_CLIENTS)->getCliente()



     this->modelo.salaLlena='n';
    pthread_mutex_unlock(&colaHiloMutex);


}


 int ModeloServidor::guardarCliente( Conexion* unaConexion )
    {

        pthread_mutex_t colaMute = PTHREAD_MUTEX_INITIALIZER;
        pthread_mutex_lock(&colaMute);

         pthread_t unHilo;


         printf("numero thread : %d\n", this->numeroThread  );

          //int er2 = pthread_create(&hilos[cantThread], NULL,   &ModeloServidor::hello_helperRecieve,   modeloServidor);
          this->colaHilos.push_back(&unHilo);
        //this->colaConexiones[0]->getSocket()
        this->colaConexiones.push_back(unaConexion);
        printf("guardo el cliente en la cola cliente %d\n",unaConexion->getSocket());

        if(this->colaHilos.size()> MAX_CLIENTS)
        {
        this->eliminarHiloClienteDemas( unaConexion );
        }else
        {
         this->numeroThread=  this->numeroThread+1 ;
         this->lanzarHilo();
        }





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
    if (!this->colaConexiones.empty())
  {
     Conexion* unaConexion=this->colaConexiones[this->numeroThread -1];
     printf("NUMERO DE THREAD ES %d\n",this->numeroThread -1);
     printf("saque el socket de la cola de clientes numero : %d\n", unaConexion->getSocket());




     if(unaConexion->getEstado()==DESCONECTADO)
      {



         if(this->cargarClientesAdmitidos(unaConexion))//true osea paso el login
          {
          unaConexion->setearEstado(LOGIN);


          printf("login correcto, estas en el juego");
          }




      }else if (unaConexion->getEstado()==LOGIN)

      {

         printf("ESTAS ESPERANDO QUE SE LLENE LA SALA");

      }else//es activo entonces podra enviar sus comandos para jugar

      {

       bool result = this->socketServidor->recibirDataGeneral(unaConexion->getSocket());

       if (result == true)
       {
         this->cargarComandos(*this->socketServidor->getClientComand());
        printf("guarde el comando definitivamente a la coladecomando : %d\n",this->socketServidor->getClientComand()->action );
        }
      }








  }


 return NULL;


}

bool ModeloServidor::verificarSiHayAlgunDesconectado()
{
    bool result=false;
    //conexiones con estado true
            for (int i = 0; i < this->colaConexiones.size(); i++)
            {
                if( this->colaConexiones[i]->getEstado()==DESCONECTADO)
                {
                  result=true;//si hay algun desconectado y alcanzo el maxclientes, hay q esperar qe se logee bien
                 break;
                }
             }


             return result;
}

void ModeloServidor::activarTodasLasConexiones()
{

    for (int i = 0; i < this->colaConexiones.size(); i++)
    {
      this->colaConexiones[i]->setearEstado(ACTIVO) ;

     }

     this->preparadoParaJugar=true;//esto me dice que estos jugadores que estan jugando, estuvieron activos minimo en algun momento del juego

}


void ModeloServidor::procesoYEnvioATodosClientes()
{

  while(!this->colaComando.empty()&&!this->colaConexiones.empty())
  {

     int action = this->colaComando.back().action;

     printf("desencole el camondo de cargarcomando %d\n",  action);
     this->processData(action);
     printf("procese ese action\n");
     this->colaComando.pop_back();


     for (int i = 0; i < this->colaConexiones.size(); i++) {

            //conexiones con estado true

            this->sendDataGeneral( this->colaConexiones[i]->getSocket(),&this->modelo);

        }

  }


}





void* ModeloServidor::desencolar( ) //es un vector que tiene clientes
{


  pthread_mutex_t colaMutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_lock(&colaMutex);

  if( !this->colaConexiones.empty())

  {

      if( (this->colaConexiones.size()  )==MAX_CLIENTS )//condiciones si o si para jugar
      {


            if(!this->verificarSiHayAlgunDesconectado())//aca entra si todos son login los clientes
            {
             this->activarTodasLasConexiones();

            }



            if(this->preparadoParaJugar)
            {


            this->procesoYEnvioATodosClientes();


            }


       }

 }



pthread_mutex_unlock(&colaMutex);
   return NULL;
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

        Conexion* unaConexion=new Conexion();
        //veo si esta conexion esta en la cola de conexion, si esta entonces tendrias
        //que buscar el vector de thread de esa conexcion y despues poner estado de esa
        //conexion igual a true.
             unaConexion->setearSocket(this->socketServidor->getClientSocket());
             unaConexion->setearEstado(DESCONECTADO);//tiene que  pasar el login para ponerlo como true osea activo
           //unaConexion.setearSocket(this->socketServidor->getClientSocket());
           // unaConexion.setearEstado(false);//tiene que  pasar el login para ponerlo como true osea activo
      //this->client_socket = this->socketServidor->getClientSocket();
     // this->guardarCliente(this->socketServidor->getClientSocket());
     	    //this->modelo.salaLlena='n';

    this->socketServidor->enviarDataGeneral(unaConexion->getSocket() ,&this->modelo);
            this->guardarCliente(unaConexion);


  }


  return result;
}

int ModeloServidor::closeSocket()
{
  return this->socketServidor->cerrar();
}



