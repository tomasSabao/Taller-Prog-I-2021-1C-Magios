#include "VistaMario.h"

VistaMario::VistaMario(Modelo_Jugador* jugadore): Vista_Jugador( jugadore)
{
   this->anchoProporcion=30;
   this->altoProporcion =30;
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
	else
	{
		//Mario salta izquierda 
		gSpriteClips[ 0 ].x = 38;
		gSpriteClips[ 0 ].y = 0;
		gSpriteClips[ 0 ].w =  16;
		gSpriteClips[ 0 ].h = 16;

		//mario camina izquieda
		gSpriteClips[ 1 ].x =  80;
		gSpriteClips[ 1 ].y =   0;
		gSpriteClips[ 1 ].w =  16;
		gSpriteClips[ 1].h = 16;


		//mario mira izquierda quieto
		gSpriteClips[ 2 ].x =   122;
		gSpriteClips[ 2 ].y =   0;
		gSpriteClips[ 2 ].w =  16;
		gSpriteClips[ 2].h = 16;

		//mario mira derecha quieto
		gSpriteClips[ 3 ].x =   162;
		gSpriteClips[ 3 ].y =   0;
		gSpriteClips[ 3 ].w =  16;
		gSpriteClips[ 3].h = 16;
		//mario camina derecha
		gSpriteClips[ 4 ].x =   200;
		gSpriteClips[ 4 ].y =   0;
		gSpriteClips[ 4 ].w =  16;
		gSpriteClips[ 4 ].h = 16;
		//mario salta derecha
		gSpriteClips[ 5 ].x =   240;
		gSpriteClips[ 5 ].y =   0;
		gSpriteClips[ 5 ].w =  16;
		gSpriteClips[ 5 ].h = 16;
         }
         return success;

}
