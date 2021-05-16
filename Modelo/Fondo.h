#ifndef FONDO_H
#define FONDO_H

#include <Modelo_Jugador.h>


class Fondo : public Modelo_Jugador
{
    public:
        Fondo(int posicion_x=0,int posicion_y=0);
        virtual ~Fondo();
        void  caminar();


    protected:

    private:
};

#endif // FONDO_H
