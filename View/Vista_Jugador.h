#ifndef VISTA_JUGADOR_H
#define VISTA_JUGADOR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Modelo/Modelo_Jugador.h"
class Vista_Jugador
{
    public:
        Vista_Jugador(Modelo_Jugador* jugador);
        virtual ~Vista_Jugador();
        bool loadMedia(SDL_Renderer*  grendered);
        LTexture* getTextureJugador();
        void setGSpriteActual();
        SDL_Rect* getGSpriteActual();
        //Renders texture at given point
		void render( int posx, int posy, SDL_Renderer*  grendered );
        void close();


    private:
        Modelo_Jugador* jugador;
        int x;
        int y;
        LTexture*  gSpriteSheetTextureJugador;
        //Walking animation

        SDL_Rect gSpriteClips[ 4 ];
        SDL_Rect* gSpriteActual ;
};

#endif // VISTA_JUGADOR_H
