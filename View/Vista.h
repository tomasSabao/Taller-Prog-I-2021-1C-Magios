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

        //
        SDL_Window* getWindow(){
            return this->gWindow;
        }
        SDL_Renderer* getRenderer(){
            return this->gRenderer;
        }

        Vista_Jugador* getVistaJugador(){
        return this->vista_jugador;}
    protected:


    private:
    bool iniciar_sdl_video();
    void cerrar_sdl_video();

    SDL_Window* gWindow=NULL ;
    SDL_Renderer*  gRenderer =NULL ;
     const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    Vista_Jugador* vista_jugador;
    Modelo* modelo;
};

#endif // VISTA_H
