#include "VistaMario.h"
#include "../lib/Logger.h"

extern Logger logger;

VistaMario::VistaMario(Modelo_Jugador* jugadore): Vista_Jugador( jugadore)
{
   this->anchoProporcion=30;
   this->altoProporcion =30;
   this->numero_maximo_frames=1;
}

VistaMario::~VistaMario()
{
    //dtor
}

 bool VistaMario::loadMedia(SDL_Renderer*  grendered )
{


printf("scope: Vista_jugador::load_media\n");
	//Loading success flag
	bool success = true;


    //LTexture  newTexture ;
	//Load sprite sheet texture
	if( !gSpriteSheetTextureJugador->loadFromFile( "mario_sprites.png", grendered) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}

	if(!success){

		logger.log("error", "Error al cargar imagen del personaje principal. Se carga imagen por defecto");
        gSpriteSheetTextureJugador->loadFromFile( "default_mario.png", grendered);

        printf( "Default image loaded!\n" );

        gSpriteClips[ 0 ].x = 108;
		gSpriteClips[ 0 ].y = 51;
		gSpriteClips[ 0 ].w =  29;
		gSpriteClips[ 0 ].h = 23;

		//mario camina izquierda[1]
        gSpriteClips[ 1 ].x = 108;
		gSpriteClips[ 1 ].y = 51;
		gSpriteClips[ 1 ].w =  29;
		gSpriteClips[ 1 ].h = 23;

		//mario camina derecha[1]
        gSpriteClips[ 2 ].x = 108;
		gSpriteClips[ 2 ].y = 51;
		gSpriteClips[ 2 ].w =  29;
		gSpriteClips[ 2 ].h = 23;
		//mario camina izquierda[2]
        gSpriteClips[ 4 ].x = 108;
		gSpriteClips[ 4 ].y = 51;
		gSpriteClips[ 4 ].w =  29;
		gSpriteClips[ 4 ].h = 23;
		//mario camina derecha [2]
        gSpriteClips[ 3 ].x = 108;
		gSpriteClips[ 3 ].y = 51;
		gSpriteClips[ 3 ].w =  29;
		gSpriteClips[ 3 ].h = 23;

		//Mario salta izquierda
        gSpriteClips[ 5 ].x = 108;
		gSpriteClips[ 5 ].y = 51;
		gSpriteClips[ 5 ].w =  29;
		gSpriteClips[ 5 ].h = 23;
		//Mario salta derecha
        gSpriteClips[ 6 ].x = 108;
		gSpriteClips[ 6 ].y = 51;
		gSpriteClips[ 6 ].w =  29;
		gSpriteClips[ 6 ].h = 23;

        gSpriteClips[ 7 ].x = 108;
		gSpriteClips[ 7 ].y = 51;
		gSpriteClips[ 7 ].w =  29;
		gSpriteClips[ 7 ].h = 23;

		success=true;
	}

	else
	{
		//Mario mira izquierda
		gSpriteClips[ 0 ].x = 0;
		gSpriteClips[ 0 ].y = 0;
		gSpriteClips[ 0 ].w =  14;
		gSpriteClips[ 0 ].h = 18;

		//mario mira derecha
		gSpriteClips[ 1 ].x =  14;
		gSpriteClips[ 1 ].y =   0;
		gSpriteClips[ 1 ].w =  12;
		gSpriteClips[ 1].h = 18;


		//mario camina izquierda[1]
		gSpriteClips[ 2 ].x =   29;
		gSpriteClips[ 2 ].y =   0;
		gSpriteClips[ 2 ].w =  15;
		gSpriteClips[ 2].h = 18;

		//mario camina derecha[1]
		gSpriteClips[ 4 ].x =   48;
		gSpriteClips[ 4 ].y =   0;
		gSpriteClips[ 4 ].w =  15;
		gSpriteClips[ 4 ].h = 18;
		//mario camina izquierda[2]
		gSpriteClips[ 3 ].x =   67;
		gSpriteClips[ 3 ].y =   0;
		gSpriteClips[ 3 ].w =  15;
		gSpriteClips[ 3 ].h = 18;
		//mario camina derecha [2]
		gSpriteClips[ 5 ].x =   86;
		gSpriteClips[ 5 ].y =   0;
		gSpriteClips[ 5 ].w =  15;
		gSpriteClips[ 5 ].h = 18;

		//Mario salta izquierda
		gSpriteClips[ 6 ].x = 106;
		gSpriteClips[ 6 ].y = 0;
		gSpriteClips[ 6 ].w =  15;
		gSpriteClips[ 6 ].h = 18;

		//Mario salta derecha
		gSpriteClips[ 7 ].x = 124;
		gSpriteClips[ 7 ].y = 0;
		gSpriteClips[ 7 ].w =  15;
		gSpriteClips[ 7 ].h = 18;

         }
         return success;

}
