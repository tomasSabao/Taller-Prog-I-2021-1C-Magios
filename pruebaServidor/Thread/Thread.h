#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>
#include <stdio.h>
#include "../ModeloServidor/ModeloServidor.h"
//#include <conio.h>

class Thread
{
    public:
        Thread();
        virtual ~Thread();
        //void* crearThread(void *algunaFuncion(void*));
       int crearThread(  );


    protected:
    pthread_t* hilo;
//void* algunaFuncion;//en general sera del servidor

    private:
};

#endif // THREAD_H
