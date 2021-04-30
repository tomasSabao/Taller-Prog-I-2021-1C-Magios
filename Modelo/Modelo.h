#ifndef MODELO_H
#define MODELO_H
#include "../Modelo/Modelo_Jugador.h"

class Modelo
{
    public:
        Modelo();
        ~Modelo();





        //Frees media and shuts down SDL

        Modelo_Jugador* getModeloJugador();


    private:


    Modelo_Jugador * jugador;
    //Screen dimension constants


};

#endif // MODELO_H
