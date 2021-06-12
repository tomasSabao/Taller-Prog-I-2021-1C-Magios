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
        virtual void setGSpriteActual();
        SDL_Rect* getGSpriteActual();
        //Renders texture at given point
		virtual void render( int posx, int posy, SDL_Renderer*  grendered );
        void close();
        //Tomas: Esta va a ser la conexion entre la vista y el modelo
        Modelo_Jugador* getModeloJugador();
        virtual void setearFondo(std::string path,int ancho, int alto);

    protected:
        Modelo_Jugador* jugador;
        int x;
        int y;
        LTexture*  gSpriteSheetTextureJugador;
        //Walking animation

        //Nota tomas: cambie el numero de elementos de gSpriteClips de 8 a 14
        SDL_Rect gSpriteClips[ 14 ];
        SDL_Rect* gSpriteActual ;


        int   anchoProporcion;
        int altoProporcion;


        int numero_maximo_frames=4;

        //esto es solo para el numero de la ultima animacion corriendo
        //en el mario
        int ultima_animacion=2;
        std::string path;
};

#endif // VISTA_JUGADOR_H
