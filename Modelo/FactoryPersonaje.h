#ifndef FACTORYPERSONAJE_H
#define FACTORYPERSONAJE_H
#include "../Modelo/Modelo.h"


class FactoryPersonaje
{
    public:
        FactoryPersonaje();
        virtual ~FactoryPersonaje();
        Modelo_Jugador* getPersonaje(string nombre, int posX=0, int posY=0);

    protected:

    private:
};

#endif // FACTORYPERSONAJE_H
