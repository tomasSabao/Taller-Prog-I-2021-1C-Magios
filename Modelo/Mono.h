#ifndef MONO_H
#define MONO_H

#include "Modelo_Jugador.h"


class Mono : public Modelo_Jugador
{
    public:
        Mono(int posicion_x=0,int posicion_y=0);
        virtual ~Mono();
        void  caminar();

    protected:

    private:
};

#endif // MONO_H
