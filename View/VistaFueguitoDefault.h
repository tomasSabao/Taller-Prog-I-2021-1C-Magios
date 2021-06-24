#ifndef VISTAFUEGUITODEFAULT_H
#define VISTAFUEGUITODEFAULT_H

#include "Vista_Jugador.h"


class VistaFueguitoDefault : public Vista_Jugador
{
    public:
        VistaFueguitoDefault(Modelo_Jugador* jugadore);
        bool  loadMedia(SDL_Renderer*  grendered );
        virtual ~VistaFueguitoDefault();
        void  setGSpriteActual();

    protected:

    private:
};


#endif // VISTAFUEGUITODEFAULT_H
