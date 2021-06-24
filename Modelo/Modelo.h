#ifndef MODELO_H
#define MODELO_H
#include "../Modelo/Modelo_Jugador.h"
#include "../Modelo/Mono.h"
#include "../Modelo/Fondo.h"
#include "../Modelo/Fueguito.h"
#include "../Modelo/FueguitoDefault.h"
#include "../Modelo/FuegoPiso.h"
#include "../Modelo/Colisionador.h"
#include "../Modelo/Rectangulo.h"
#include <vector>
using namespace std;


class Modelo
{
    public:
        Modelo();
        ~Modelo();

        //Frees media and shuts down SDL
        Modelo_Jugador* getModeloJugador(int posicion);
        void escenario2(std::string tipo_enemigo, int cantFuieguitos=0);
        void escenario1(std::string tipo_enemigo, int cantFuieguitos=0);

        void acciones();
        int getCantJugadores();

        void agregarObjetosAlColisionador();
        //esta funcion es la que agrega los elementos del fondo a la pantalla
        //haciendo como que estan sin necesidad de graficarlos
        void agregarRectangulo(Rectangulo* rect);
        //esta funcion agrega las escaleras
        void agregarEscalera(Rectangulo* rect);
        //metodo que se usa solamente para mandarle la tecla apretada al colisionador
        void recibirTecla(int tecla_apretada,std::string nombre_jugador);
        void agregarJugador(std::string username, int id);

    private:
        Colisionador colisionador;
        Modelo_Jugador * jugador;
        std::vector<Modelo_Jugador*> modelosPersonajes;
        int contador = 0;
        std::vector<std::string> nombreJugadores;
};

#endif // MODELO_H
