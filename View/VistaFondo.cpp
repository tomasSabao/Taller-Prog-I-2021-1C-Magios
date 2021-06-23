#include "VistaFondo.h"
#include "../lib/Parser.h"
#include <string>

extern Parser parser;

VistaFondo::VistaFondo(Modelo_Jugador* jugadore): Vista_Jugador( jugadore)
{
   std::vector<std::string> fondos = parser.obtenerFondos();

   this->anchoProporcion=600;
   this->altoProporcion =360;
   //this->path="fondo.png";
   this->path=fondos.at(0);
}

VistaFondo::~VistaFondo()
{
    //dtor
}

void VistaFondo::setearFondo(std::string path,int alto, int ancho)
{
 this->path=path;
 this->anchoProporcion=alto;
   this->altoProporcion =ancho;
}
bool VistaFondo::loadMedia(SDL_Renderer*  grendered )
{


printf("scope: Vista_jugador::load_media\n");
	//Loading success flag
	bool success = true;


    //LTexture  newTexture ;
	//Load sprite sheet texture
	if( !gSpriteSheetTextureJugador->loadFromFile( this->path, grendered) )
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
