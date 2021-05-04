#include "Vista.h"

Vista::Vista(Modelo* modelo)
{

    this->modelo=modelo;
    this->gWindow=NULL;
    this->gRenderer=NULL;
    this->vista_jugador=new Vista_Jugador(modelo->getModeloJugador());
}

Vista::~Vista()
{
    //dtor
}


bool Vista::init(   )
{
    printf("Scope: vista::init\n");
    SDL_Window* auxGWindow=NULL;
    SDL_Renderer*  auxGgRenderer=NULL;
    //Initialization flag
	bool success = true;

	//Initialize SDL
	/*printf("vista::init iniciacion de sdl_video");
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;

	}*/

	if(this->iniciar_sdl_video()==false){
	printf("fallo detectado. Saliendo de Vista::init()\n");
    return false;
    }

	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		auxGWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,800  , 600, SDL_WINDOW_SHOWN );
		if( auxGWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			auxGgRenderer = SDL_CreateRenderer( auxGWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( auxGgRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( auxGgRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

        this->gWindow=auxGWindow;
        this->gRenderer =auxGgRenderer;
        return success;

}

bool Vista::iniciar_sdl_video(){
   if( SDL_Init(SDL_INIT_VIDEO) < 0){
    printf("no se pudo iniciar sdl video\n");
    return false;
   }
   printf("se pudo iniciar SDL_video\n");
   return true;

}

void Vista::cerrar_sdl_video(){
    SDL_Quit();
}

bool  Vista::loadMedia()
{
    return this->vista_jugador->loadMedia(this->gRenderer);

}


 void Vista::render(   )
 {

    SDL_SetRenderDrawColor( this->gRenderer, 0xFF, 0xFF, 0, 0xFF );
	SDL_RenderClear( this->gRenderer );

    this->vista_jugador->render(  SCREEN_WIDTH  ,   SCREEN_HEIGHT ,gRenderer);
    //Update screen
	SDL_RenderPresent( this->gRenderer );
 }

 void Vista::close()
 {   this->vista_jugador->close();
    //Destroy window
	SDL_DestroyRenderer( this->gRenderer );
	SDL_DestroyWindow( this->gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

 }
