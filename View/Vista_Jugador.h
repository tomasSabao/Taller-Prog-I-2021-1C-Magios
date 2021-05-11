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
        virtual bool loadMedia(SDL_Renderer*  grendered);
        LTexture* getTextureJugador();
        void setGSpriteActual();
        SDL_Rect* getGSpriteActual();
        //Renders texture at given point
		void render( int posx, int posy, SDL_Renderer*  grendered );
        void close();

        //Tomas: Esta va a ser la conexion entre la vista y el modelo
        Modelo_Jugador* getModeloJugador();

    protected:
        Modelo_Jugador* jugador;
        int x;
        int y;
        LTexture*  gSpriteSheetTextureJugador;
        //Walking animation

        //Nota tomas: cambie el numero de elementos de gSpriteClips de 4 a 6
        SDL_Rect gSpriteClips[ 6 ];
        SDL_Rect* gSpriteActual ;


        int   anchoProporcion;
        int altoProporcion;


};

#endif // VISTA_JUGADOR_H
