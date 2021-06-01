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


void* Thread::crearThread(void *algunaFuncion(void*))

{


   pthread_create(this->hilo,NULL, algunaFuncion,NULL);
  return NULL;
}
