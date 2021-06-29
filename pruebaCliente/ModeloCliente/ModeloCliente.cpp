#include "ModeloCliente.h"


ModeloCliente::ModeloCliente()
{

    Modelo_Jugador * mj = new Modelo_Jugador("",0,0);
    Modelo m;

    Comando co;
    co.action=0;
    co.password=0;
    this->modelo = &(m);
    this->modelo_jugador = mj;
    this->estaConectado=false;
    this->unComando=&(co);
    this->activo;
    this->indentificadorCliente;
    this->contador=0;

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
  pthread_mutex_t colaMutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_lock(&colaMutex);
  Comando comandato = comando;
  printf("recibi el camondo de cargarcomando %d\n", comando.action);
  printf("recibi el camondo de nombre %d\n", comando.nombre);
  this->colaComando.push_back(comandato);
  pthread_mutex_unlock(&colaMutex);
  return 0;
}

int ModeloCliente::cargarMensaje(Mensaje* msj)
{
    printf("funcion CargarMensaje, entro\n");
    pthread_mutex_t colaMutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&colaMutex);
    this->colaMensajes.push_back(msj);
    pthread_mutex_unlock(&colaMutex);
    printf("Funcion cargarMensaje, salgo\n");
    return 0;
}

void* ModeloCliente::desencolar()
{
    //  Comando *comandato = comando;
    pthread_mutex_t colaMutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&colaMutex);

    if(!this->colaComando.empty() && this->estaConectado)
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
Mensaje* ModeloCliente::desencolarMensaje()
{
    Mensaje* msj_desencolado=NULL;
    pthread_mutex_t colaMutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&colaMutex);

    //las condiciones son: la cola de mensajes no este vacia, y esta conectado el cliente
    if(this->colaMensajes.size()!=0 && this->estaConectado == true)
    {
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
void* ModeloCliente::funcionParaThread(void* context)
{
  while(1)
  {
      //((ModeloCliente *)context)->recibirUsuarioContrasenia();
    ((ModeloCliente *)context)->funcionReceptoraInput();
  }
  return NULL;
}


void* ModeloCliente::threadFunctionRecibir(void* context)
{
  while(1)
  {
    ((ModeloCliente*)context)->recibirDataGeneral2();
  }
  return NULL;
}

//se tiene que desencolar el mensaje de la cola, y se tiene que enviar
void* ModeloCliente::threadFunctionEnviar(void* context)
{
    printf("Funcion: threadEnviar\n");
    bool estaConectado= ((ModeloCliente*)context)->getEstaConectado();
    Mensaje* msj_a_mandar=NULL;
    void* contenido=NULL;
    int tamanio_msj;
    while(1)
    {
        ((ModeloCliente*)context)->manejadora();
    }
    printf("Funcion threadEnviar. FIN\n");
    return NULL;
}

void ModeloCliente::manejadora()
{
    int resultado;
    if(this->getEstaConectado()==true && this->colaMensajes.size()!=0)
    {
        printf("Se va a mandar un mensaje\n");
        Mensaje* msj_a_mandar=this->desencolarMensaje();
        int tamanio_msj=msj_a_mandar->getTamanio();
        resultado=this->enviarMensaje(msj_a_mandar,tamanio_msj);
        if(resultado==0)
        {
            printf("Se mando un mensaje correctamente\n");
        } else {
            printf("Error al mandar mensaje\n");
        }
    }
    // printf("Sali de funcion manejadora\n");
}


void *ModeloCliente::hello_helperRecieve(void *context)
{
    while(1)
    {
        ((ModeloCliente *)context)->receiveData();
    }
    return NULL;
}

void *ModeloCliente::hello_helperSend(void *context)
{
    while(1)
    {
        ((ModeloCliente *)context)->desencolar();
    }
    return NULL;
}


void *ModeloCliente::threadLogin(void *context)
{
    while(1)
    {
        ((ModeloCliente *)context)->hiloLogin();
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
    if (this->estaConectado==true)
    {
        if (this->activo==false)
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

        if (!this->activo)
        {
            int result2 = this->socketCliente->recibirDataComando();
            if (result2)
            {
                this->unComando = this->socketCliente->getServerComando();
                if (this->unComando->tipo==11)
                {
                    this->indentificadorCliente=this->unComando->action;
                    this->activo=true;
                    printf("logeado correcto");
                    this->contador=this->contador+1;
                } else {
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
        cout << "Bienvenido al sistema " << comando << ". Gracias por usar nuestra aplicación" << "\n";
        Comando command;
        command.action = comando;
        command.tipo=2;

        this->cargarComandos(command);
    }
}



void ModeloCliente::ImprimirModeloActualizado()
{
    printf("Receive data: pos(X,Y) = (%d,%d)\n\n", this->modelo_jugador->getPosicionX(), this->modelo_jugador->getPosicionY());
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

int ModeloCliente::enviarMensaje(void* msj, int tamanio_bytes)
{
    int resultado = this->socketCliente->enviarData(msj,tamanio_bytes);
    return resultado;
}

//version nueva
int ModeloCliente::enviarMensaje(Mensaje* msj,int tamanio_bytes)
{
    void* mensaje_a_mandar=msj->getMensaje();
    int resultado=this->socketCliente->enviarData(mensaje_a_mandar,tamanio_bytes);
    return resultado;
}

int ModeloCliente::sendData(Comando* comando)
{
    int result = this->socketCliente->enviarData(comando);
    return result;
}


int ModeloCliente::conectar()
{
    int conectar=this->socketCliente->conectar();
    if (conectar==0)
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

bool ModeloCliente::getEstaConectado()
{
    return this->estaConectado;
}

int ModeloCliente::recibirUsuarioContrasenia()
{
    if(this->esperandoRespuestaLogin==true){
        printf("Esperando respuesta...\n");
        return 0;
    }
    int success=0;
    std::string usuario="";
    std::string contrasenia="";

    char buffer_usr_str[16];
    char buffer_psw_str[16];
    printf("Ingrese usuario: \n");
    scanf("%s" ,buffer_usr_str);
    for (int i=0; i<15; i++) {
        if (buffer_usr_str[i]==0){
            break;
        }
        usuario+=buffer_usr_str[i];
    }
    printf("Ingrese contrasenia:  \n");
    scanf("%s" ,buffer_psw_str);
    for (int i=0;i<15;i++){
        if(buffer_psw_str[i]==0){
            break;
        }
        printf("%c\n",buffer_psw_str[i]);
        contrasenia+=buffer_psw_str[i];
    }
    printf("Voy a entrar al codificador\n");
    success=this->codificador.codificarMensajeConexionDos(&this->envio_msj_login, usuario, contrasenia);
    //saco el mutex

    //meter el mensaje en la cola de mensajes a enviar
    this->encolarMensajeAEnviar(&this->envio_msj_login);
    printf("Fin de funcion usuario contrasenia\n");
    this->esperandoRespuestaLogin=true;
    return success;
}


bool ModeloCliente::getEstaConectadoServidor(){
    return this->estaConectadoAlServidor;
}


void* ModeloCliente::recibirDataGeneral2()
{
    printf("-----Thread: recibir mensaje -------\n");
    if (this->estaConectadoAlServidor==true){
        //El cliente esta conectado al servidor, por lo que va a recibir mensajes de actualizacion de posiciones
        //TODO
    } else {
        //el cliente no esta conectado al servidor, por lo que va a recibir mensajes de aceptacion/rechazo de login
        printf("XXXXXXXX Valor del buffer antes de recibir: %d\n",*(unsigned char*) (this->recibir_msj_login.getMensaje()));
        int resultado= this->socketCliente->recibirData(1,&this->recibir_msj_login);
        //veo que pasa con el resultado del servidor
        if (resultado == 0) {
            printf("XXXXXXXXSe recibio un mensaje del servidor\n");
            printf("XXXXXXXXXValor del mensaje recibido: %d\n",*(unsigned char*)(this->recibir_msj_login.getMensaje()));
            //quiero encolarlo en la cola de mensajes recibidos
            Mensaje* un_msj=new Mensaje();
            un_msj->asignarMemoria(this->recibir_msj_login.getTamanio(),1);
            //en teoria el nuevo mensaje tiene el espacio para almacenar el contenido del mensaje
            memcpy(un_msj->getMensaje(),this->recibir_msj_login.getMensaje(),1);
            this->encolarMensaje(un_msj);
        }
    }
    return NULL;
}

//encola mensaje para ser procesado
void ModeloCliente::encolarMensaje(Mensaje* msj)
{
    printf("Funcion ENCOLARMENSAJE\n");
    pthread_mutex_t colaMutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&colaMutex);

    this->colaMensajesAProcesar.push_back(msj);
    printf("Se encolo un mensaje en la cola para procesar\n");
    pthread_mutex_unlock(&colaMutex);
}


void ModeloCliente::encolarMensajeAEnviar(Mensaje* msj)
{
    pthread_mutex_t colaMutex=PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&colaMutex);

    this->colaMensajes.push_back(msj);
    printf("Se encolo un mensaje en la cola para enviar \n");
    pthread_mutex_unlock(&colaMutex);
}


int ModeloCliente::procesarMensaje(Mensaje* msj)
{
    //TODO: logica de respuesta
    int tipo_msj=this->decodificador.obtenerTipo(msj->getMensaje());
    printf("Tipo de mensaje: %d \n");
    //este es el caso de la aceptacion del servidor
    if(tipo_msj == 2){
        char id=this->decodificador.obtenerIdAsignadoLogin(msj->getMensaje());
        int num_jugadores=this->decodificador.obtenerMaximoNumeroJugadores(msj->getMensaje());
        
        printf("Numero maximo de jugadores: %d\n",num_jugadores);
        printf("Id asignada: %c\n",id);
        this->estaConectadoAlServidor=true;
        //this->indentificadorCliente=id;
        this->esperandoRespuestaLogin=false;
        printf("Se conecto el jugador\n");
        return 0;
    }
    //caso sala llena
    if(tipo_msj==3){
        printf("Sala llena, no se puede conectar al juego\n");
        this->esperandoRespuestaLogin=false;
        return 1;
    }
    //caso usuario contrasenia invalidos
    if(tipo_msj == 4){
        printf("Usuario/Contrasenia invalidos\n");
        this->esperandoRespuestaLogin=false;
        return 1;
    }
    if(tipo_msj == 6 ){
        printf("Se recibio un mensaje de avance de nivel\n");
        //TODO: logica del nivel
    }
    if(tipo_msj == 7){
        printf("Se recibio un mensaje de actualizacion de plataformas\n");
        return 0;
    }
    if(tipo_msj == 8){
        printf("Se recibio un mensaje de actualizacion de barriles\n");
        return 0;
        //TODO: logica
    }
    if(tipo_msj == 10){
        printf("Se va a iniciar el juego\n");
        return 0;
        //TODO: logica de inicio de juego
    }
    if(tipo_msj == 11){
        printf("Se recibio un mensaje de actualizacion de los fueguitos\n");
        return 0;
        //TODO: logica de actualizacion
    }
    //caso desconexion de un jugador
    if(tipo_msj == 12){
        char id=*(char*)(msj->getMensaje());
        id=id<<4;
        id=id>>4;
        this->desconectarJugador(id);
        //funcion de cambio de sprite
        return 0;
    }
    //caso de reconexion de un jugador
    if(tipo_msj == 13){
        char id=*(char*)(msj->getMensaje());
        id=id<<4;
        id=id>>4;
        this->conectarJugador(id);
    }
    //caso que se recibio el path de un fondo
    if(tipo_msj == 14){
        printf("Se recibio un path a un fondo\n");
        std::string path=this->decodificador.obtenerPathDeFondo(msj->getMensaje());
        //TODO: hacer algo con el path de fondo
        return 0;
    }
    if(tipo_msj == 15){
        printf("Credenciales repetidas. No se puede conectar\n");
        this->esperandoRespuestaLogin=false;
        return 0;
    }
    return 0;
}


int ModeloCliente::desencolarYProcesarMensaje()
{
    pthread_mutex_t colaMutex= PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock (&colaMutex);

    if (this->colaMensajesAProcesar.size() ==0)
    {
        //no hay mensajes para procesar
        pthread_mutex_unlock(&colaMutex);
        return 1;
    }
    //tenemos mensajes para desencolar
    printf("777777777777 ModeloCliente::desencolarYProcesarMensaje. Hay mensaje para procesar\n");
    Mensaje* msj_desencolado=this->colaMensajesAProcesar.front();
    this->colaMensajesAProcesar.erase(this->colaMensajesAProcesar.begin());
    pthread_mutex_unlock(&colaMutex);
    //proceso el mensaje ahora
    this->procesarMensaje(msj_desencolado);
    return 0;
}


int ModeloCliente::desencolarYEnviarMensaje()
{
    //solo si hay mensajes para enviar
    pthread_mutex_t colaMutex=PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock (&colaMutex);

    if (this->colaMensajes.size()==0)
    {
        //no hay mensajes para enviar
        pthread_mutex_unlock(&colaMutex);
        return 1;
    }
    //tenemos mensajes para enviar
    Mensaje* msj_desencolado=this->colaMensajes.front();
    this->colaMensajesAProcesar.erase(this->colaMensajesAProcesar.begin());
    pthread_mutex_unlock(&colaMutex);

    this->enviarMensaje(msj_desencolado,msj_desencolado->getTamanio());
    return 0;
}


void* ModeloCliente::funcionThreadDesencolarYEnviar(void* contexto)
{
    while(1){
        ((ModeloCliente*)contexto)->desencolarYEnviarMensaje();
    }
    return NULL;
}

void* ModeloCliente::funcionThreadDesencolarYProcesar(void* contexto)
{
    while(1)
    {
        ((ModeloCliente*)contexto)->desencolarYProcesarMensaje();
    }
    return NULL;
}

void* ModeloCliente::funcionThreadRecibir(void* contexto)
{
    while(1)
    {
        ((ModeloCliente*)contexto)->recibirDataGeneral2();
    }
    return NULL;
}



void ModeloCliente::desconectarJugador(char id_jugador){
    this->idConectados[id_jugador]=false;
}

void ModeloCliente::conectarJugador(char id_jugador){
    this->idConectados[id_jugador]=true;
}

void ModeloCliente::cambiarPosX(char id_jugador,int pos){
    this->posXJugadores[id_jugador]=pos;
}

void ModeloCliente::cambiarPosY(char id_jugador,int pos){
    this->posYJugadores[id_jugador]=pos;
}

void ModeloCliente::cambiarFrameJugador(char id_jugador,int frame){
    this->frameJugadores[id_jugador]=frame;
}

void ModeloCliente::setNumeroFueguitos(int numero){
    this->num_fueguitos=numero;
}

void ModeloCliente::setNumeroBarriles(int numero){
    this->num_barriles=numero;
}

void ModeloCliente::setNumeroPlataformas(int numero){
    this->num_plataformas=numero;
}

void ModeloCliente::eliminarFueguitos(){
    while(this->posXFueguitos.size()!=0){
        this->posXFueguitos.pop_back();
    }
    while(this->posYFueguitos.size()!=0){
        this->posYFueguitos.pop_back();
    }
    while(this->frameFueguitos.size()!=0){
        this->frameFueguitos.pop_back();
    }
}

void ModeloCliente::eliminarPlataformas(){
    while(this->posXPlataformas.size()!=0){
        this->posXPlataformas.pop_back();
    }
    while(this->posYPlataformas.size()!=0){
        this->posYPlataformas.pop_back();
    }
}

void ModeloCliente::eliminarBarriles(){
    while(this->posXBarriles.size() !=0){
        this->posXBarriles.pop_back();
    }
    while(this->posYBarriles.size() !=0){
        this->posYBarriles.pop_back();
    }
    while(this->frameBarriles.size() != 0){
        this->frameBarriles.pop_back();
    }
}


void ModeloCliente::cambiarPosXFueguitos(std::vector<int>posiciones){
    for(int i=0; i<this->num_fueguitos;i++){
        this->posXFueguitos[i]=posiciones[i];
    }
}

void ModeloCliente::cambiarPosYFueguitos(std::vector<int>posiciones){
    for(int i=0; i<this->num_fueguitos;i++){
        this->posYFueguitos[i]=posiciones[i];
    }
}

void ModeloCliente::cambiarFramesFueguitos(std::vector<int>posiciones){
    for(int i=0; i<this->num_fueguitos;i++){
        this->frameFueguitos[i]=posiciones[i];
    }
}

void ModeloCliente::cambiarPosXBarriles(std::vector<int>posiciones){
    for(int i=0; i<this->num_fueguitos;i++){
        this->posXBarriles[i]=posiciones[i];
    }
}

void ModeloCliente::cambiarPosYBarriles(std::vector<int>posiciones){
    for(int i=0; i<this->num_fueguitos;i++){
        this->posYBarriles[i]=posiciones[i];
    }
}

void ModeloCliente::cambiarFrameBarriles(std::vector<int>posiciones){
    for(int i=0; i<this->num_fueguitos;i++){
        this->frameBarriles[i]=posiciones[i];
    }
}

void ModeloCliente::cambiarPosicionXPlataforma(int plataforma_a_cambiar,int posicion){
    this->posXPlataformas[plataforma_a_cambiar]=posicion;
}

void ModeloCliente::cambiarPosicionYPlataforma(int plataforma_a_cambiar,int posicion){
    this->posYPlataformas[plataforma_a_cambiar]=posicion;
}


void ModeloCliente::funcionReceptoraInput(){
    if(this->estaConectadoAlServidor == false && this->esperandoRespuestaLogin==false){
        this->recibirUsuarioContrasenia();
        return;
    }
    if(this->estaConectadoAlServidor == false  && this->esperandoRespuestaLogin==true){
        return;
    }
    this->recibirInputJuego();
}

void ModeloCliente::recibirInputJuego(){
    printf("funcion recibir input juego\n");

    int quit=7; //creo que este valor no causa problemas en el juego
    while(quit != 1){
        while(this->controlador.desencolarEvento() != 0){
            quit=this->controlador.descifrarEvento();
            //y ahora hay que armar el mensaje y enviarlo
            Mensaje* msj=new Mensaje();
            msj->asignarMemoria(1,1);
            this->codificador.codificarMensajeTeclaDos(msj,quit,this->indentificadorCliente);
            this->encolarMensajeAEnviar(msj);
        }
    }
    return;
}
