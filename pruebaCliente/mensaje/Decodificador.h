#ifndef DECODIFICADOR_H
#define DECODIFICADOR_H

#include <stdio.h>
#include "Mensaje.h"
#include <string>
#include <iostream>
class Decodificador
{
    public:
        Decodificador();
        virtual ~Decodificador();

        //esta no sirve
        void decodificarMensaje(Mensaje* msj);
        //esta si
        void decodificarMensajeDos(void* msj);

    protected:

    private:
    	char mapearIdJugador(int numero);
};

#endif // DECODIFICADOR_H
