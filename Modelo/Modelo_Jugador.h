#ifndef MODELO_JUGADOR_H
#define MODELO_JUGADOR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Modelo/LTexture.h"


class Modelo_Jugador
{
    public:
        Modelo_Jugador(int posicion_x=0,int posicion_y=0);
        virtual ~Modelo_Jugador();


    	void traducirTecla(int tecla_apretada);
		int getPosicionX();
		int getPosicionY();
		virtual void mover();
		void imprimirPosicion();
		void imprimirVelocidad();
		void aplicarGravedad();
		void setPosicionX(int pos_x);
		void setPosicionY(int pos_y);
		void setGravedad(int num);
		void setVelocidadHorizontal(int numero);
		void setVelocidadVertical(int numero);
		void setDireccion(int numero);

		//solo tiene que usarse para el mario, porque necesita el valor de las teclas
		void fijarAnimacionMovimiento();

        virtual void caminar();
        //solo debug para ver todas las animaciones
        void caminar2();
        int getFrame();

        bool estaParadoEnPiso();
        std::string  getNombre();
        void aumentarVelocidadX();
		void reducirVelocidadX();
		void aumentarVelocidadY();
		void reducirVelocidadY();

		void setearEpilepsia(int cantFrameActualizar, int cantidadDeSprite);

		int  getCantFrameActualizar();
		int  getCantFrameDelPersonaje();
		int velocidad_horizontal=10;

	private:

		int velocidad_x=0;

		int cantidadDeSprite;


    protected:
    bool estaba_parado=true;
    int velocidad_vertical=20;
	int gravedad=1;
    int velocidad_y=0;
    int posicion_x=0;
		int posicion_y=0;
    std::string nombre;
    int frames;

    int ultima_animacion=2;
    //esto es para la ultima direccion. 1 es izquierda, 2 es derecha
    int ultima_direccion=2;
    int cuantosFrameActualizo;
    };

#endif // MODELO_JUGADOR_H
