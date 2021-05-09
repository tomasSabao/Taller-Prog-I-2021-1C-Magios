#ifndef VISTAFONDO_H
#define VISTAFONDO_H

#include <Vista_Jugador.h>
#include "../Modelo/Modelo_Jugador.h"


class VistaFondo : public Vista_Jugador
{
    public:
        VistaFondo(Modelo_Jugador* jugadore);
        virtual ~VistaFondo();
         bool  loadMedia(SDL_Renderer*  grendered );

    protected:

    private:
};

#endif // VISTAFONDO_H
