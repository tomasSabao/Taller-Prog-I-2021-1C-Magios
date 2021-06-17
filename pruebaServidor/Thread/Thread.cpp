#include "Thread.h"

//

Thread::Thread()
{
    pthread_t nuevoHilo;
    this->hilo=&nuevoHilo;
    //this->algunaFuncion=algunaFuncion;
}

Thread::~Thread()
{
    //dtor
}


int Thread::crearThread(  )

{


   //pthread_create(this->hilo,NULL,  &ModeloServidor::hello_helper,modelo);
  return 0;
}
/*
void* Thread::crearThread(void *algunaFuncion(void*),ModeloServidor* modelo)

{


   pthread_create(this->hilo,NULL, algunaFuncion,NULL);
  return NULL;
}
*/
