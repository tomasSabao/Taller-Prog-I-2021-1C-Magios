#ifndef MODELO_JUGADOR_H
#define MODELO_JUGADOR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Modelo/LTexture.h"
#include "../Modelo/Rectangulo.h"


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

		//getters agregados para hacer andar el colisionador
		int getVelocidadX();
		int getVelocidadY();

		void resetVelocidadY();
		void setEstaEnPiso();
		void setEstaEnAire();
		void setEstaEnEscalera();
		bool getEstaEnEscalera();
//fin de los getters


		//solo tiene que usarse para el mario, porque necesita el valor de las teclas
		void fijarAnimacionMovimiento();

		//funciones que se usan para setear la animacion del mario en las escaleras
		//porque la animacion va a depender de la posicion del mario en la misma
		void fijarAnimacionesEnEscalera();
		void fijarAnimacionBordeSuperior(Rectangulo* escalera);
		//estas funciones van a ser solo para la escalera,para setear bien las animaciones
		void setEstaQuieto();
		void setEstaMoviendo();

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

    bool esta_en_piso=false;
    bool esta_en_aire=true;
    //agregado para hacer funcionar la escalera
    bool esta_en_escalera=false;
	bool esta_quieto=true;
	//solo para probar
	bool unSwitch=false;
	int ultima_animacion_escalera=10;
	int cuantos_frame_actualizo_escalera=0;
    };

#endif // MODELO_JUGADOR_H
