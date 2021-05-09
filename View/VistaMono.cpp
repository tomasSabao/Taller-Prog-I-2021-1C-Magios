#include "VistaMono.h"

VistaMono::VistaMono(Modelo_Jugador* jugadore): Vista_Jugador( jugadore)
{

}

VistaMono::~VistaMono()
{
    //dtor
}

 bool VistaMono::loadMedia(SDL_Renderer*  grendered )
{


printf("scope: Vista_jugador::load_media\n");
	//Loading success flag
	bool success = true;


    //LTexture  newTexture ;
	//Load sprite sheet texture
	if( !gSpriteSheetTextureJugador->loadFromFile( "mono.png", grendered) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
		//Set sprite clips
		gSpriteClips[ 0 ].x =   0;
		gSpriteClips[ 0 ].y =   110;
		gSpriteClips[ 0 ].w =  100;
		gSpriteClips[ 0 ].h = 150;

		//Set sprite clips
		gSpriteClips[ 1 ].x =   105;
		gSpriteClips[ 1 ].y =   110;
		gSpriteClips[ 1 ].w =  105;
		gSpriteClips[ 1].h = 150;


		//Set sprite clips
		gSpriteClips[ 2 ].x =   220;
		gSpriteClips[ 2 ].y =   110;
		gSpriteClips[ 2 ].w =  110;
		gSpriteClips[ 2].h = 150;

		//Set sprite clips
		gSpriteClips[ 3 ].x =   320;
		gSpriteClips[ 3 ].y =   110;
		gSpriteClips[ 3 ].w =  112;
		gSpriteClips[ 3].h = 150;
         }
         return success;

}
