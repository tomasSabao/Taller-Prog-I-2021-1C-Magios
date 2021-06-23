#ifndef VISTAPLATAFORMADERECHA_H
#define VISTAPLATAFORMADERECHA_H
#include <Vista_Jugador.h>

class VistaPlataformaDerecha:  public Vista_Jugador
{
    public:
        VistaPlataformaDerecha(Modelo_Jugador* jugadore);
        bool  loadMedia(SDL_Renderer*  grendered );
        virtual ~VistaPlataformaDerecha();

    protected:

    private:
};

#endif // VISTAPLATAFORMADERECHA_H
