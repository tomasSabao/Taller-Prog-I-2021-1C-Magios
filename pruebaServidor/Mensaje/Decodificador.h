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


        void decodificarMensaje(Mensaje* msj);

        void decodificarMensajeDos(void* msj);



        int obtenerTipo(void* msj);

        std::string obtenerUsuario(void* msj);

        std::string obtenerContrasenia(void* msj);

        int obtenerLongitudUsuario(void* msj);

        int obtenerLongitudContrasenia(void* msj);

        int obtenerTecla(void* tecla);



    protected:

    private:
    	char mapearIdJugador(int numero);
};

#endif // DECODIFICADOR_H
