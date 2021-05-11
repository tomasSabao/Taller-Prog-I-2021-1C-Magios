#ifndef MODELO_JUGADOR_H
#define MODELO_JUGADOR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Modelo/LTexture.h"


class Modelo_Jugador
{
    public:
        Modelo_Jugador();
        virtual ~Modelo_Jugador();


    	void traducirTecla(int tecla_apretada);
		int getPosicionX();
		int getPosicionY();
		void mover();
		void imprimirPosicion();
		void imprimirVelocidad();
		void aplicarGravedad();
		void setPosicionX(int pos_x);
		void setPosicionY(int pos_y);
		void setGravedad(int num);

		//solo tiene que usarse para el mario, porque necesita el valor de las teclas
		void fijarAnimacionMovimiento();
		
        virtual void caminar();
        //solo debug para ver todas las animaciones
        void caminar2();
        int getFrame();

	private:
		void aumentarVelocidadX();
		void reducirVelocidadX();
		void aumentarVelocidadY();
		void reducirVelocidadY();



		int velocidad_horizontal=10;

	//solo para el mario:con velocidad_vertical=20 el pico del salto es de 50
		int velocidad_vertical=20;
		int gravedad=5;

		int velocidad_x=0;
		int velocidad_y=0;
		int posicion_x=0;
		int posicion_y=0;

		bool ultima_animacion_quieta=false;

    protected:


    int frames;

    };

#endif // MODELO_JUGADOR_H
