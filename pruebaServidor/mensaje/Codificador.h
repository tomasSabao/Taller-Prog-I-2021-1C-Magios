#ifndef CODIFICADOR_H
#define CODIFICADOR_H


#include "Mensaje.h"
#include <stdio.h>
#include <string>
#include <cmath>
#include <map>
#include <iostream>

class Codificador
{
    public:
        Codificador();
        virtual ~Codificador();


        //NO USAR
        int codificarMensajeRespuestaLoginPositiva(Mensaje* msj,char user_id,int numero_jugadores);
        //VACIO
        int codificarMensajeRespuestaLoginNegativa();

        int codificarMensajeActualizacionPosiciones(Mensaje* msj,int numero_jugadores);

    	char conseguirTipoTecla(int tecla_apretada);


    	int codificarMensajeTeclaDos(Mensaje* msj,int tecla_apretada,char id_jugador);

    	int codificarMensajeConexionDos(Mensaje* msj, std::string usuario, std::string contrasenia);


    	int codificarMensajeSalaVaciaAceptacion(Mensaje* msj, char id_jugador, int numero_max_jugadores);

    	int codificarMensajeSalaLlenaRechazo(Mensaje* msj);

        int codificarMensajeErrorUsuarioContraseniaRechazo(Mensaje* msj);

        int codificarMensajeActualizacion(Mensaje* msj,std::map<char,int>mapa_posiciones_x,std::map<char,int>mapa_posiciones_y,std::map<char,int>mapa_frames);

    protected:

    private:

    	char mapearIdJugador(char id_jugador);

    	char mapearNumeroMaxJugadores(int numero_max);

        char mapearNumeroDeFrame(int numero_frame);


};

#endif // CODIFICADOR_H
