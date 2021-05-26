#ifndef VISTABARRIL_H
#define VISTABARRIL_H

#include <Vista_Jugador.h>


class VistaBarril : public Vista_Jugador
{
    public:
        VistaBarril(Modelo_Jugador* jugadore);
        bool  loadMedia(SDL_Renderer*  grendered );
        virtual ~VistaBarril();


    protected:

    private:
};

#endif // VISTABARRIL_H
