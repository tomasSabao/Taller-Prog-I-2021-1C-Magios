#ifndef VISTAMARIO_H
#define VISTAMARIO_H

#include "Vista_Jugador.h"


class VistaMario : public Vista_Jugador
{
    public:
        VistaMario(Modelo_Jugador* jugadore);
        bool  loadMedia(SDL_Renderer*  grendered );
        virtual ~VistaMario();

    protected:

    private:
};

#endif // VISTAMARIO_H
