#include "../View/Vista_Jugador.h"
#include "../View/VistaMono.h"
Vista_Jugador::Vista_Jugador(Modelo_Jugador* jugadore)

{
   this->jugador=jugadore;
   this->x=0;
   this->y=0;
   this->gSpriteSheetTextureJugador= new LTexture();
   this->setGSpriteActual();
   this->anchoProporcion=0;
   this->altoProporcion =0;

 }

Vista_Jugador::~Vista_Jugador()
{
    //dtor
}


bool Vista_Jugador::loadMedia(SDL_Renderer*  grendered)
{
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
		gSpriteClips[ 0 ].x =   0;
		gSpriteClips[ 0 ].y =   0;
		gSpriteClips[ 0 ].w =  64;
		gSpriteClips[ 0 ].h = 205;

		gSpriteClips[ 1 ].x =  64;
		gSpriteClips[ 1 ].y =   0;
		gSpriteClips[ 1 ].w =  64;
		gSpriteClips[ 1 ].h = 205;

		gSpriteClips[ 2 ].x = 128;
		gSpriteClips[ 2 ].y =   0;
		gSpriteClips[ 2 ].w =  64;
		gSpriteClips[ 2 ].h = 205;

		gSpriteClips[ 3 ].x = 196;
		gSpriteClips[ 3 ].y =   0;
		gSpriteClips[ 3 ].w =  64;
		gSpriteClips[ 3 ].h = 205;
	}

    //this->gSpriteSheetTextureJugador= &newTexture;
	return success;
}

void Vista_Jugador::setGSpriteActual()
{


    this->gSpriteActual=&gSpriteClips[ this->jugador->getFrame()/4 ];

}

SDL_Rect* Vista_Jugador::getGSpriteActual()
{

    return this->gSpriteActual;
}

LTexture* Vista_Jugador::getTextureJugador()
{
 return  this->gSpriteSheetTextureJugador;
}

void Vista_Jugador::render( int posx, int posy ,SDL_Renderer* grendered)
{
    this->setGSpriteActual();
    this->gSpriteSheetTextureJugador->render( posx , posy,this->getGSpriteActual() ,grendered,this->anchoProporcion,this->altoProporcion );
}




void Vista_Jugador::close()
{
    this->gSpriteSheetTextureJugador->free();
}
