#ifndef MODELO_JUGADOR_H
#define MODELO_JUGADOR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Modelo/LTexture.h"


class Modelo_Jugador
{
    public:
        Modelo_Jugador();
        virtual ~Modelo_Jugador();


        virtual void caminar();

        int getFrame();



    protected:


    int frames;

    };

#endif // MODELO_JUGADOR_H
