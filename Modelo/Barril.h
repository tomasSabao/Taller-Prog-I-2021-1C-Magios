#ifndef BARRIL_H
#define BARRIL_H

#include "Modelo_Jugador.h"


class Barril : public Modelo_Jugador
{
    public:
        Barril(int posicion_x=0,int posicion_y=0);
        virtual ~Barril();
        void  caminar();
        void  mover();

    protected:

    private:
};

#endif // BARRIL_H
