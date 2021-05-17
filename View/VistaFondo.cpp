#include "VistaFondo.h"

VistaFondo::VistaFondo(Modelo_Jugador* jugadore): Vista_Jugador( jugadore)
{
    this->anchoProporcion=600;
   this->altoProporcion =360;
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
	if( !gSpriteSheetTextureJugador->loadFromFile( "fondo.png", grendered) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
		//Set sprite clips
		gSpriteClips[ 0 ].x = 0
		  ;
		gSpriteClips[ 0 ].y =   0;
		gSpriteClips[ 0 ].w =  225;
		gSpriteClips[ 0 ].h = 244;


         }
         return success;

}
