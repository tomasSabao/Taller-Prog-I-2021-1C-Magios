#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>
#include <stdio.h>
//#include <conio.h>

class Thread
{
    public:
        Thread();
        virtual ~Thread();
        void* crearThread(void *algunaFuncion(void*));


    protected:
    pthread_t* hilo;
//void* algunaFuncion;//en general sera del servidor

    private:
};

#endif // THREAD_H
