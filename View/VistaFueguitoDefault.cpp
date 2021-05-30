#include "VistaFueguitoDefault.h"


VistaFueguitoDefault::VistaFueguitoDefault(Modelo_Jugador* jugadore): Vista_Jugador( jugadore)
{
   this->anchoProporcion=30;
   this->altoProporcion =30;
}

VistaFueguitoDefault::~VistaFueguitoDefault()
{
    //dtor
}

 bool VistaFueguitoDefault::loadMedia(SDL_Renderer*  grendered )
{


printf("scope: Vista_jugador::load_media\n");
	//Loading success flag
	bool success = true;


    //LTexture  newTexture ;
	//Load sprite sheet texture
	if( !gSpriteSheetTextureJugador->loadFromFile( "dksprites-default.png", grendered) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
		//Set sprite clips
		gSpriteClips[ 0 ].x =   111;
		gSpriteClips[ 0 ].y =   223;
		gSpriteClips[ 0 ].w =  16;
		gSpriteClips[ 0 ].h = 16;

		//Set sprite clips
		gSpriteClips[ 1 ].x =   132;
		gSpriteClips[ 1 ].y =   223;
		gSpriteClips[ 1 ].w =  16;
		gSpriteClips[ 1].h = 16;


		//Set sprite clips
		gSpriteClips[ 2 ].x =   158;
		gSpriteClips[ 2 ].y =   220;
		gSpriteClips[ 2 ].w =  16;
		gSpriteClips[ 2].h = 16;

		//Set sprite clips
		gSpriteClips[ 3 ].x =   179;
		gSpriteClips[ 3 ].y =   220;
		gSpriteClips[ 3 ].w =  16;
		gSpriteClips[ 3].h = 16;
  }
         return success;

}
