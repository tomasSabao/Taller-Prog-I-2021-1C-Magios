#include "VistaFuegoPiso.h"


VistaFuegoPiso::VistaFuegoPiso(Modelo_Jugador* jugadore): Vista_Jugador( jugadore)
{
   this->anchoProporcion=-30;
   this->altoProporcion =0;
}

VistaFuegoPiso::~VistaFuegoPiso()
{
    //dtor
}

 bool VistaFuegoPiso::loadMedia(SDL_Renderer*  grendered )
{


printf("scope: Vista_jugador::load_media\n");
	//Loading success flag
	bool success = true;


    //LTexture  newTexture ;
	//Load sprite sheet texture
	if( !gSpriteSheetTextureJugador->loadFromFile( "fuegoPiso.png", grendered) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
		//Set sprite clips
		gSpriteClips[ 0 ].x =   13;
		gSpriteClips[ 0 ].y =   38;
		gSpriteClips[ 0 ].w =  111;
		gSpriteClips[ 0 ].h = 92;

		//Set sprite clips
		gSpriteClips[ 1 ].x =   9;
		gSpriteClips[ 1 ].y =   165;
		gSpriteClips[ 1 ].w =  111;
		gSpriteClips[ 1].h = 92;


		//Set sprite clips
		gSpriteClips[ 2 ].x =   12;
		gSpriteClips[ 2 ].y =   292;
		gSpriteClips[ 2 ].w =  111;
		gSpriteClips[ 2].h = 92;

		//Set sprite clips
		gSpriteClips[ 3 ].x =   10;
		gSpriteClips[ 3 ].y =   424;
		gSpriteClips[ 3 ].w =  111;
		gSpriteClips[ 3].h = 92;
         }
         return success;

}

void VistaFuegoPiso::setGSpriteActual()
{

    this->gSpriteActual=&gSpriteClips[ this->jugador->getFrame()/this->jugador->getCantFrameActualizar()];

}
