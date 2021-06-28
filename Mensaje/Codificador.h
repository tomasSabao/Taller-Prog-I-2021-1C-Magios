#ifndef CODIFICADOR_H
#define CODIFICADOR_H

#include "Mensaje.h"
#include <stdio.h>
#include <string>
#include <cmath>
#include <map>
#include <iostream>
#include <vector>


class Codificador
{
    public:
        Codificador();
        virtual ~Codificador();

        int codificarMensajeRespuestaLoginPositiva(Mensaje* msj,char user_id,int numero_jugadores);

        int codificarMensajeRespuestaLoginNegativa();

        int codificarMensajeActualizacionPosiciones(Mensaje* msj,int numero_jugadores);

    	char conseguirTipoTecla(int tecla_apretada);

    	int codificarMensajeTeclaDos(Mensaje* msj,int tecla_apretada,char id_jugador);

    	int codificarMensajeConexionDos(Mensaje* msj, std::string usuario, std::string contrasenia);

    	int codificarMensajeSalaVaciaAceptacion(Mensaje* msj, char id_jugador, int numero_max_jugadores);

    	int codificarMensajeSalaLlenaRechazo(Mensaje* msj);

        int codificarMensajeErrorUsuarioContraseniaRechazo(Mensaje* msj);

        int codificarMensajeActualizacion(Mensaje* msj,std::map<char,int>mapa_posiciones_x,std::map<char,int>mapa_posiciones_y,std::map<char,int>mapa_frames);

        //nuevos mensajes agregados
        int codificarMensajeInicioJuego(Mensaje* msj);//funciona
        int codificarMensajeDesconexionDeUnJugador(Mensaje* msj,char id_jugador);//usada solo por el servidor
        int codificarMensajeReconexionDeUnJugador(Mensaje* msj,char id_jugador);
        int codificarMensajeAvanceDeNivel(Mensaje* msj,int numero_fueguitos);//
        int codificarMensajeActualizacionPosicionesFueguitos(Mensaje* msj, std::vector<int>posiciones_x, std::vector<int>posiciones_y,std::vector<int>frames);
        int codificarMensajeActualizacionPosicionesPlataformas(Mensaje* msj, std::vector<int>posiciones_x, std::vector<int>posiciones_y);
        int codificarMensajeActualizacionPosicionesBarriles(Mensaje* msj, std::vector<int>posiciones_x, std::vector<int>posiciones_y,std::vector<int>frames);
        int codificarMensajePathFondo(Mensaje* msj,std::string path);//funciona
        int codificarMensajeLoginRepetido(Mensaje* msj);//15

    protected:

    private:

    	char mapearIdJugador(char id_jugador);

    	char mapearNumeroMaxJugadores(int numero_max);

        char mapearNumeroDeFrame(int numero_frame);

};

#endif // CODIFICADOR_H
