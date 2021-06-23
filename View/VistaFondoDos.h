#ifndef VISTAFONDODOS_H
#define VISTAFONDODOS_H

#include <Vista_Jugador.h>


class VistaFondoDos : public Vista_Jugador
{
    public:
        VistaFondoDos(Modelo_Jugador* jugadore);
        virtual ~VistaFondoDos();
        bool  loadMedia(SDL_Renderer*  grendered );

    protected:

    private:
};

#endif // VISTAFONDODOS_H
