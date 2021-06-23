#ifndef VISTAFUEGOPISO_H
#define VISTAFUEGOPISO_H

#include <Vista_Jugador.h>


class VistaFuegoPiso : public Vista_Jugador
{
    public:
        VistaFuegoPiso(Modelo_Jugador* jugadore);
        bool  loadMedia(SDL_Renderer*  grendered );
        virtual ~VistaFuegoPiso();
        void  setGSpriteActual();

    protected:

    private:
};

#endif // VISTAFUEGOPISO_H
