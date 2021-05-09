#include "VistaFondo.h"

VistaFondo::VistaFondo(Modelo_Jugador* jugadore): Vista_Jugador( jugadore)
{
    this->anchoProporcion=600;
   this->altoProporcion =400;
}

VistaFondo::~VistaFondo()
{
    //dtor
}


bool VistaFondo::loadMedia(SDL_Renderer*  grendered )
{


printf("scope: Vista_jugador::load_media\n");
	//Loading success flag
	bool success = true;


    //LTexture  newTexture ;
	//Load sprite sheet texture
	if( !gSpriteSheetTextureJugador->loadFromFile( "total.png", grendered) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
		//Set sprite clips
		gSpriteClips[ 0 ].x =   0;
		gSpriteClips[ 0 ].y =   200;
		gSpriteClips[ 0 ].w =  230;
		gSpriteClips[ 0 ].h = 220;


         }
         return success;

}
