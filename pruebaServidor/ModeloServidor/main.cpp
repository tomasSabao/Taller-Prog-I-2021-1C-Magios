#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>
#include "../ModeloServidor/ModeloServidor.h"
#include "../ModeloServidor/Conexion.h"
#include "../Thread/Thread.h"
//#include "ModeloServidor.h"
#include "../SocketServidor/SocketServidor.h"
 #include <vector>
 using namespace std;
 #define MAX_CLIENTS 4
// Structs for data transfer
 std::vector<Conexion> colaConexiones;
 int clients[MAX_CLIENTS];
 #include <pthread.h>
#include <stdio.h>
//------------------------
void *saludar(void* algo)
{
 int i;
 while(1)
 //printf("hilo funcion saludar soy un cliente");
  printf("hilo SOY CLIENTE NUMERO : %d\n", algo );

}

void *handle_client(void* clientSocket)
{
/* int i;
 while(1)
 printf("hilo  de conectado cliente saludar");*/
 printf("=== WELCOME TO THE CHATROOM ===\n");

/*	pthread_t send_msg_thread; desencolar motodo de la clase modeloservidor
  if(pthread_create(&send_msg_thread, NULL, (void *) send_msg_handler, NULL) != 0){
		printf("ERROR: pthread\n");
    return EXIT_FAILURE;
	}*/

	/*pthread_t recv_msg_thread;
  if(pthread_create(&recv_msg_thread, NULL,  modeloservidor->receiveDataGeneral(), clientSocket) != 0){
		printf("ERROR: pthread\n");
		return EXIT_FAILURE;
	}*/


}

pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

    /* Add clients to queue */
void queue_add(int cl){
	pthread_mutex_lock(&clients_mutex);

	for(int i=0; i < MAX_CLIENTS; ++i){
		if(!clients[i]){
			clients[i] = cl;
			break;
		}
	}

	pthread_mutex_unlock(&clients_mutex);
}

/* Remove clients to queue */
void queue_remove(int uid){
	pthread_mutex_lock(&clients_mutex);

	/*for(int i=0; i < MAX_CLIENTS; ++i){
		if(clients[i]){
			if(clients[i]->uid == uid){
				clients[i] = NULL;
				break;
			}
		}
	}*/

	pthread_mutex_unlock(&clients_mutex);
}

// First argument: port
int main(int argc , char *argv[])
{
    int server_socket;
    int client_socket;


    int port = atoi(argv[1]);


    //Thread* hilo= new Thread();
    //hilo->crearThread(saludar);


/*new Thread()



    while(true)
    {
     Conexion unaConexion;
     //SocketServidor* socket=new SocketServidor( port);
    SocketServidor* nuevoSocket= new SocketServidor(  port);

    unaConexion.setearConexion(nuevoSocket->getSocket());

   modeloServidor->CrearSocket(port);
   modeloServidor->bindSocket();
   modeloServidor->escuchar();
   modeloServidor->aceptandoConexiones();
   colaConexiones.push_back(  new Thread->crearThread());

    }*/

 ModeloServidor* modeloServidor= new ModeloServidor();
 modeloServidor->CrearSocket(port);
   modeloServidor->bindSocket();
   modeloServidor->escuchar();
    pthread_t tid;




int i=0;
    while(true)
    {
    i= i +1 ;
     //Conexion unaConexion;
     //SocketServidor* socket=new SocketServidor( port);
    //SocketServidor* nuevoSocket= new SocketServidor(  port);
    modeloServidor->aceptandoConexiones();


		/* Add client to the queue and fork thread */
    queue_add(modeloServidor->getCliente());
    //pthread_create(&tid, NULL, &handle_client, (void*)modeloServidor->getCliente());
    pthread_create(&tid, NULL, &saludar, (void*)modeloServidor->getCliente() );
    //unaConexion.setearConexion(nuevoSocket->getSocket());

   //modeloServidor->socketAceptando(nuevoSocket);
   //colaConexiones.push_back(  new Thread->crearThread());

    }

    int commands_count = 0;
    int status = 0;

    printf("inicializa data: %d\n",  2);
    modeloServidor->initializeData( );
    printf("termino %d\n",  2);

    //keep communicating with client


    while (commands_count < 20)
    {
        printf("Commands count: %d\n", commands_count + 1);

        // Receive data (command)
        if (modeloServidor->receiveData( ) < 0){
            perror("Receive Data Error");
            status = -1;
        }
         printf("Incomming command action: %d\n", modeloServidor->getAction() );
        //--------------------

        // Process model
        modeloServidor->processData(modeloServidor->getAction()  );
        //--------------------

        // Send data (view)
        if (modeloServidor->sendData( ) < 0){
            perror("Send Data Error");
            status = -1;
        }
        printf("Send data: pos(X,Y) = (%d,%d)\n\n", modeloServidor->getPosicionX(), modeloServidor->getPosicionY());
        //--------------------*/

        commands_count++;
    }


modeloServidor->imprimirComandos();
     close(modeloServidor->getCliente());
    printf("Client socket number %d closed\n",modeloServidor->getCliente());
    modeloServidor->closeSocket();
    //printf("Server socket number %d closed\n",server_socket);*/

    return 0;
}

