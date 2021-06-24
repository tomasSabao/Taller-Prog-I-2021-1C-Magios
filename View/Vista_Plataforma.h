#ifndef VISTA_PLATAFORMA_H
#define VISTA_PLATAFORMA_H
#include "Vista_Jugador.h"

class Vista_Plataforma:  public Vista_Jugador
{
    public:
        Vista_Plataforma(Modelo_Jugador* jugadore);
        bool  loadMedia(SDL_Renderer*  grendered );
        virtual ~Vista_Plataforma();

    protected:

    private:
};

#endif // VISTA_PLATAFORMA_H
