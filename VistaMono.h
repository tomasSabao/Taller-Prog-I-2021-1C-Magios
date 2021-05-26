#ifndef VISTAMONO_H
#define VISTAMONO_H

#include <Vista_Jugador.h>

#include "../View/VistaMono.h"
#include "../Modelo/Mono.h"
#include "../Modelo/Modelo_Jugador.h"

class VistaMono : public Vista_Jugador
{
    public:
        VistaMono( Modelo_Jugador* jugador);

        virtual ~VistaMono();
        virtual bool loadMediaMono(SDL_Renderer*  grendered );

    protected:
    //Modelo_Jugador* jugador;
    private:
};

#endif // VISTAMONO_H
