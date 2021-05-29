#ifndef MODELO_H
#define MODELO_H
#include "../Modelo/Modelo_Jugador.h"
#include "../Modelo/Mono.h"
#include "../Modelo/Fondo.h"
#include "../Modelo/Fueguito.h"
#include "../Modelo/FueguitoDefault.h"
#include "../Modelo/FuegoPiso.h"
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
        void  escenario1(std::string tipo_enemigo, int cantFuieguitos=0);

        void acciones();
        int  getCantJugadores( );



    private:


    Modelo_Jugador * jugador;
    std::vector<Modelo_Jugador*> modelosPersonajes;
    int contador = 0;
    //Screen dimension constants


};

#endif // MODELO_H
