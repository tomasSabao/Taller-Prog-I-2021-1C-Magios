#ifndef FUEGOPISO_H
#define FUEGOPISO_H

#include <Modelo_Jugador.h>


class FuegoPiso : public Modelo_Jugador
{
    public:
        FuegoPiso(int posicion_x,int posicion_y);
        virtual ~FuegoPiso();
        void caminar();
    protected:

    private:
};

#endif // FUEGOPISO_H
