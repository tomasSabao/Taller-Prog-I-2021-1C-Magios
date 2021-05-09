#ifndef FONDO_H
#define FONDO_H

#include <Modelo_Jugador.h>


class Fondo : public Modelo_Jugador
{
    public:
        Fondo();
        virtual ~Fondo();
        void  caminar();


    protected:

    private:
};

#endif // FONDO_H
