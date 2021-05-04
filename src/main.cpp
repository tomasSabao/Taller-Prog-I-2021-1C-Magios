//Using SDL, SDL_image, standard IO, and strings

#include <stdio.h>
#include <string>
#include "../View/Vista.h"
#include "../Modelo/Modelo.h"
#include "../include/Controlador.h"
#include "../Modelo/LTexture.h"
#include "../View/Vista_Jugador.h"
#include "Test.h"

const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];
SDL_Rect gSpriteClipsFondo[ 0];
SDL_Texture* loadTexture( std::string path ,SDL_Renderer* gRenderer);
bool loadMedia(SDL_Texture* gTexture);
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool loadMedia( )
{
	//Loading success flag
	bool success = true;


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


	return success;
}

bool loadMediaFondo( )
{
	//Loading success flag
	bool success = true;


		//Set sprite clips
		gSpriteClipsFondo[ 0 ].x =   0;
		gSpriteClipsFondo[ 0 ].y =   160;
		gSpriteClipsFondo[ 0 ].w =  235;
		gSpriteClipsFondo[ 0 ].h = 250;




	return success;
}

int main( int argc, char* args[] )
{/*
    Modelo* modelo=new Modelo();
    Modelo_Jugador* jugador=modelo->getModeloJugador();
    Controlador controlador(modelo->getModeloJugador());
    Vista vista(modelo);
    vista.init();

    //creo una textura
    LTexture* textura=new LTexture();
    LTexture* texturaFondo=new LTexture();

    //consigo la ventana y el render de vista
    SDL_Window* ventana=vista.getWindow();
    SDL_Renderer* renderer=vista.getRenderer();
    //trato de visualizar
    textura->loadFromFile("foo.png",renderer);
    texturaFondo->loadFromFile("total.png",renderer);
    loadMedia( );
    loadMediaFondo();
    //Vista_Jugador* vistaJugador= new Vista_Jugador(jugador);
    //vistaJugador->loadMedia(renderer);
   // vista.loadMedia();
    int quit=0;
    //SDL_Event e;
    while(quit!=1){
        while(controlador.desencolarEvento()!=0){
            quit= controlador.descifrarEvento();

         }

            //Render current frame
            printf("El valor DE CORREr main %d.\n", jugador->getFrame());
            SDL_Rect* currentClip = &gSpriteClips[ jugador->getFrame() ];
            SDL_Rect* currentClipFondo = &gSpriteClipsFondo[ 0 ];
            SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( renderer );
            texturaFondo->render( ( SCREEN_WIDTH -currentClipFondo->w)/2, ( SCREEN_HEIGHT -currentClipFondo->h)/2, currentClipFondo,renderer );
            textura->render(  30, 40, currentClip,renderer );
            //vistaJugador->render(5,6,renderer);
            //textura->render(0,0,NULL,renderer);
            SDL_RenderPresent(renderer);
            jugador->caminar();
            //vistaJugador->setGSpriteActual();
    }
*/
    Test test;
    test.testearMovimiento();
	return 0;
}
