#ifndef VISTAMONO_H
#define VISTAMONO_H

#include <Vista_Jugador.h>
#include "../Modelo/Modelo_Jugador.h"


class VistaMono : public Vista_Jugador
{
    public:
        VistaMono(Modelo_Jugador* jugadore);
        virtual ~VistaMono();
         bool  loadMedia(SDL_Renderer*  grendered );
         void  setGSpriteActual();
    protected:

    private:
};

#endif // VISTAMONO_H
