#ifndef VISTAFUEGUITO_H
#define VISTAFUEGUITO_H

#include <Vista_Jugador.h>


class VistaFueguito : public Vista_Jugador
{
    public:
        VistaFueguito(Modelo_Jugador* jugadore);
        bool  loadMedia(SDL_Renderer*  grendered );
        virtual ~VistaFueguito();

    protected:

    private:
};

#endif // VISTAFUEGUITO_H
