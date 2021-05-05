#ifndef MODELO_H
#define MODELO_H
#include "../Modelo/Modelo_Jugador.h"
#include "../Modelo/Mono.h"

class Modelo
{
    public:
        Modelo();
        ~Modelo();





        //Frees media and shuts down SDL

        Modelo_Jugador* getModeloJugador();
        Mono*  getMono();


    private:


    Modelo_Jugador * jugador;
    Mono* mono;
    //Screen dimension constants


};

#endif // MODELO_H
