#ifndef MENSAJE_H
#define MENSAJE_H


#include <string.h>
#include <stdlib.h>
#include <stdio.h>

class Mensaje
{
    public:
        Mensaje();
        virtual ~Mensaje();

        void* getMensaje();

        int asignarMemoria(int numero_elementos,int tamanio);

        int redimensionarMemoria(int numero_elementos);

        int getTamanio();

        void liberarMemoria();

    protected:

    private:

    void* msj=NULL;
    int tamanio=0;
};

#endif // MENSAJE_H
