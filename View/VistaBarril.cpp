#include "VistaBarril.h"

VistaBarril::VistaBarril(Modelo_Jugador* jugadore): Vista_Jugador( jugadore)
{
    this->anchoProporcion=0;
   this->altoProporcion =0;
}

VistaBarril::~VistaBarril()
{
    //dtor
}


 bool VistaBarril::loadMedia(SDL_Renderer*  grendered )
{


printf("scope: Vista_jugador::load_media\n");
	//Loading success flag
	bool success = true;


    //LTexture  newTexture ;
	//Load sprite sheet texture
	if( !gSpriteSheetTextureJugador->loadFromFile( "barriles.png", grendered) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
		//Set sprite clips
		gSpriteClips[ 0 ].x =   0;
		gSpriteClips[ 0 ].y =   0;
		gSpriteClips[ 0 ].w =  80;
		gSpriteClips[ 0 ].h = 100;

		//Set sprite clips
		gSpriteClips[ 1 ].x =   82;
		gSpriteClips[ 1  ].y =   0;
		gSpriteClips[ 1  ].w =  80;
		gSpriteClips[ 1  ].h = 100;


		//Set sprite clips
		gSpriteClips[ 2  ].x =   156;
		gSpriteClips[ 2  ].y =   0;
		gSpriteClips[ 2 ].w =  80;
		gSpriteClips[ 2  ].h = 100;

		//Set sprite clips
		gSpriteClips[ 3 ].x =   238;
		gSpriteClips[ 3 ].y =   0;
		gSpriteClips[ 3 ].w =  80;
		gSpriteClips[ 3].h = 100;
		}
         return success;

}


void VistaBarril::setGSpriteActual()
{

    this->gSpriteActual=&gSpriteClips[ this->jugador->getFrame()/this->jugador->getCantFrameActualizar()];

}
/*
void VistaBarril::render( int posx, int posy ,SDL_Renderer* grendered)
{
	this->setGSpriteActual();
    this->gSpriteSheetTextureJugador->render( posx , posy,this->getGSpriteActual()/this->jugador->getCantFrameActualizar() ,grendered,this->anchoProporcion,this->altoProporcion );
}
*/
