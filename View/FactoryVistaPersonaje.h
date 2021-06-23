#ifndef FACTORYVISTAPERSONAJE_H
#define FACTORYVISTAPERSONAJE_H
#include "../View/Vista.h"

class FactoryVistaPersonaje
{
    public:
        FactoryVistaPersonaje(Modelo_Jugador* jugadore);
        virtual ~FactoryVistaPersonaje();
        Vista_Jugador* getVistaPersonaje(string nombre);
    protected:

    Modelo_Jugador* personaje;
    private:

};

#endif // FACTORYVISTAPERSONAJE_H
