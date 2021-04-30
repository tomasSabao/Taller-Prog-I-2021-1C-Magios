#ifndef VISTA_H
#define VISTA_H

#include <stdio.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../View/Vista_Jugador.h"

#include "../Modelo/Modelo.h"

class Vista
{
    public:
        Vista(Modelo* modelo);
        virtual ~Vista();
        bool init(  );
        void render();
         //Loads media
        bool loadMedia();
        void close();
    protected:

    private:
    SDL_Window* gWindow ;
    SDL_Renderer*  gRenderer  ;
     const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    Vista_Jugador* vista_jugador;
    Modelo* modelo;
};

#endif // VISTA_H
