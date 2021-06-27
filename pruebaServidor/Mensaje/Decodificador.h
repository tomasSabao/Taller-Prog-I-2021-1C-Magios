#ifndef DECODIFICADOR_H
#define DECODIFICADOR_H

#include <stdio.h>
#include "Mensaje.h"
#include <string>
#include <iostream>
#include <vector>
class Decodificador
{
    public:
        Decodificador();
        virtual ~Decodificador();

        //no se usa
        void decodificarMensaje(Mensaje* msj);

        void decodificarMensajeDos(void* msj);



        int obtenerTipo(void* msj);

        std::string obtenerUsuario(void* msj);

        std::string obtenerContrasenia(void* msj);

        int obtenerLongitudUsuario(void* msj);

        int obtenerLongitudContrasenia(void* msj);

        //de aca en adelante, funciones a ser usadas para los mensajes de tipo tecla
        int obtenerTecla(void* msj);//funciona
        char obtenerIdJugador(void* msj);
        //fin de las funciones de tecla

        std::string obtenerPathDeFondo(void* msj);//funciona

        std::vector<int> obtenerPosicionesXPlataformas(void* msj);
        int obtenerPosicionXPlataforma(void*msj, int i);
        int obtenerPosicionYPlataforma(void*msj, int i);
        std::vector<int> obtenerPosicionesYPlataformas(void* msj);

        std::vector<int> obtenerPosicionesXBarriles(void* msj);
        std::vector<int> obtenerPosicionesYBarriles(void* msj);
        std::vector<int> obtenerFramesBarriles(void* msj);

        std::vector<int> obtenerPosicionesXFueguitos(void* msj);
        std::vector<int> obtenerPosicionesYFueguitos(void* msj);
        std::vector<int> obtenerFramesFueguitos(void* msj);
    protected:

    private:
    	char mapearIdJugador(int numero);
};

#endif // DECODIFICADOR_H
