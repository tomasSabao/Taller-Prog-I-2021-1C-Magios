#include "Vista_Plataforma.h"

Vista_Plataforma::Vista_Plataforma(Modelo_Jugador* jugadore):Vista_Jugador( jugadore)
{
   this->anchoProporcion=18;
   this->altoProporcion =10;
}

Vista_Plataforma::~Vista_Plataforma()
{
    //dtor
}

bool Vista_Plataforma::loadMedia(SDL_Renderer*  grendered){

	printf("scope: Vista_jugador::load_media\n");
	//Loading success flag
	bool success = true;


    //LTexture  newTexture ;
	//Load sprite sheet texture
	if( !gSpriteSheetTextureJugador->loadFromFile( "plataforma.png", grendered) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
		gSpriteClips[ 0 ].x = 0;
		gSpriteClips[ 0 ].y = 0;
		gSpriteClips[ 0 ].w =  24;
		gSpriteClips[ 0 ].h = 9;

		gSpriteClips[ 1 ].x = 0;
		gSpriteClips[ 1 ].y = 0;
		gSpriteClips[ 1 ].w =  24;
		gSpriteClips[ 1 ].h = 9;

		gSpriteClips[ 2 ].x = 0;
		gSpriteClips[ 2 ].y = 0;
		gSpriteClips[ 2 ].w =  24;
		gSpriteClips[ 2 ].h = 9;

		gSpriteClips[ 3 ].x = 0;
		gSpriteClips[ 3 ].y = 0;
		gSpriteClips[ 3 ].w =  24;
		gSpriteClips[ 3 ].h = 9;

		gSpriteClips[ 4 ].x = 0;
		gSpriteClips[ 4 ].y = 0;
		gSpriteClips[ 4 ].w =  24;
		gSpriteClips[ 4 ].h = 9;
	}
	return success;
}
