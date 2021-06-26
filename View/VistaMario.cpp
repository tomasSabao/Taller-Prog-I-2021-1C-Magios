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
char* VistaMario::setSpriteSheet(int i){

char*colores[5] ={"mario_sprite_rojo.png","mario_sprite_celeste.png","mario_sprite_amarillo.png","mario_sprite_verde.png","mario_sprite_gris.png"};
    return colores[i];
}

 bool VistaMario::loadMedia(SDL_Renderer*  grendered )
{


printf("scope: Vista_jugador::load_media\n");
	//Loading success flag
	bool success = true;


    //LTexture  newTexture ;
	//Load sprite sheet texture
	if( !gSpriteSheetTextureJugador->loadFromFile( this->setSpriteSheet(4), grendered) )
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

		gSpriteClips[ 8 ].x = 108;
		gSpriteClips[ 8 ].y = 51;
		gSpriteClips[ 8 ].w =  29;
		gSpriteClips[ 8 ].h = 23;

		gSpriteClips[ 9 ].x = 108;
		gSpriteClips[ 9 ].y = 51;
		gSpriteClips[ 9 ].w =  29;
		gSpriteClips[ 9 ].h = 23;

		gSpriteClips[ 10 ].x = 108;
		gSpriteClips[ 10 ].y = 51;
		gSpriteClips[ 10 ].w =  29;
		gSpriteClips[ 10 ].h = 23;

		gSpriteClips[ 11 ].x = 108;
		gSpriteClips[ 11 ].y = 51;
		gSpriteClips[ 11 ].w =  29;
		gSpriteClips[ 11 ].h = 23;

		gSpriteClips[ 12 ].x = 108;
		gSpriteClips[ 12 ].y = 51;
		gSpriteClips[ 12 ].w =  29;
		gSpriteClips[ 12 ].h = 23;

		gSpriteClips[ 13 ].x = 108;
		gSpriteClips[ 13 ].y = 51;
		gSpriteClips[ 13 ].w =  29;
		gSpriteClips[ 13 ].h = 23;

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

		//Mario sube borde escalera, pierna izquierda extendida [2]
		gSpriteClips[ 8 ].x = 0;
		gSpriteClips[ 8 ].y = 30;
		gSpriteClips[ 8 ].w = 15;
		gSpriteClips[ 8 ].h = 18;

		//mario sube borde escalera, pierna derecha extendida [1]
        gSpriteClips[ 9 ].x = 22;
		gSpriteClips[ 9 ].y = 31;
		gSpriteClips[ 9 ].w =  15;
		gSpriteClips[ 9 ].h = 18;


		//mario sube escalera, pierna derecha extendida
        gSpriteClips[ 10 ].x = 40;
		gSpriteClips[ 10].y = 31;
		gSpriteClips[ 10 ].w =  15;
		gSpriteClips[ 10 ].h = 18;

		//mario sube escalera, pierna izquierda extendida
        gSpriteClips[ 11 ].x = 56;
		gSpriteClips[ 11 ].y = 34;
		gSpriteClips[ 11 ].w =  15;
		gSpriteClips[ 11 ].h = 18;

		//mario sube borde escalera, pierna izquierda extendida [1]
        gSpriteClips[ 12 ].x = 77;
		gSpriteClips[ 12 ].y = 34;
		gSpriteClips[ 12 ].w =  15;
		gSpriteClips[ 12 ].h = 18;

		//mario sube borde escalera, pierna derecha extendida [2]
        gSpriteClips[ 13 ].x = 98;
		gSpriteClips[ 13 ].y = 34;
		gSpriteClips[ 13 ].w =  15;
		gSpriteClips[ 13 ].h = 18;

         }
         return success;

}
