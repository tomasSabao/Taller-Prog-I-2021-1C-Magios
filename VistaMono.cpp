#include "VistaMono.h"

VistaMono::VistaMono( Modelo_Jugador* jugador  )

{

}

VistaMono::~VistaMono()
{
    //dtor
}


bool VistaMono::loadMediaMono(SDL_Renderer*  grendered )
{
	//Loading success flag
	bool success = true;

printf("scope: Vista_jugador::load_media\n");
	//Loading success flag
	bool success = true;


    //LTexture  newTexture ;
	//Load sprite sheet texture
	if( !gSpriteSheetTextureJugador->loadFromFile( "foo.png", grendered) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
		//Set sprite clips
		gSpriteClipsMono[ 0 ].x =   0;
		gSpriteClipsMono[ 0 ].y =   110;
		gSpriteClipsMono[ 0 ].w =  100;
		gSpriteClipsMono[ 0 ].h = 150;

		//Set sprite clips
		gSpriteClipsMono[ 1 ].x =   105;
		gSpriteClipsMono[ 1 ].y =   110;
		gSpriteClipsMono[ 1 ].w =  105;
		gSpriteClipsMono[ 1].h = 150;


		//Set sprite clips
		gSpriteClipsMono[ 2 ].x =   220;
		gSpriteClipsMono[ 2 ].y =   110;
		gSpriteClipsMono[ 2 ].w =  110;
		gSpriteClipsMono[ 2].h = 150;

		//Set sprite clips
		gSpriteClipsMono[ 3 ].x =   320;
		gSpriteClipsMono[ 3 ].y =   110;
		gSpriteClipsMono[ 3 ].w =  112;
		gSpriteClipsMono[ 3].h = 150;


}

	return success;
}
