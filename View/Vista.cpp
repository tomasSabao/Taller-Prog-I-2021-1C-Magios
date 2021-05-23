#include "Vista.h"
#include "../View/VistaMono.h"
#include "../View/VistaFondo.h"
#include "../View/VistaFueguito.h"
#include "../View/VistaFuegoPiso.h"
#include "../View/VistaMario.h"
#include "../View/VistaBarril.h"
#include "../lib/Logger.h"
#include "../lib/Parser.h"

#include "../View/FactoryVistaPersonaje.h"

#define WINDOW_TITLE "Donkey Kong II - Magios"

extern Parser parser;
extern Logger logger;

Vista::Vista(Modelo* modelo)
{

    this->modelo=modelo;
    this->gWindow=NULL;
    this->gRenderer=NULL;
    //this->vista_jugador=new Vista_Jugador(this->modelo->getModeloJugador());
    //this->Vistamono=new VistaMono( this->modelo->getModeloJugador() );
    //this->vista_jugador[0]=new Vista_Jugador(this->modelo->getModeloJugador());
    //this->vista_jugador[1]=new VistaMono( this->modelo->getModeloJugador() );
     this->personajes=std::vector<Vista_Jugador*>();
 /*   personajes.push_back(new Vista_Jugador(this->modelo->getModeloJugador(0)));
    personajes.push_back(new Vista_Jugador( this->modelo->getModeloJugador(1) ));
     personajes.push_back(new VistaMono( this->modelo->getModeloJugador(2) ));
     personajes.push_back(new VistaFondo( this->modelo->getModeloJugador(3) ));
     personajes.push_back(new VistaFueguito(this->modelo->getModeloJugador(4)));
     personajes.push_back(new VistaFueguito(this->modelo->getModeloJugador(5)));
    personajes.push_back(new VistaFuegoPiso(this->modelo->getModeloJugador(6)));
    personajes.push_back(new VistaMario(this->modelo->getModeloJugador(7)));*/
      //printf("%d\n",this->modelo->getCantJugadores());


     for (int i = 0; i <this->modelo->getCantJugadores(); i++) {
     Modelo_Jugador* jugador=  this->modelo->getModeloJugador(i);
        printf("%s\n",jugador->getNombre().c_str());

     personajes.push_back(  ( new FactoryVistaPersonaje( jugador ) )->getVistaPersonaje(jugador->getNombre() ));
     printf("%s\n","exito de init");
        }

         printf("%d\n",personajes.size());
}

Vista::~Vista()
{
    //dtor
}


void  Vista::escenario1( )
{

  printf("entra a vistra ecsenario 1 %s\n", "sdf");
  for (int i = this->personajes.size(); i <this->modelo->getCantJugadores(); i++) {
  Modelo_Jugador* jugador=  this->modelo->getModeloJugador(i);

  printf("%s\n",jugador->getNombre().c_str());
  personajes.push_back(  ( new FactoryVistaPersonaje( jugador ) )->getVistaPersonaje(jugador->getNombre() ));
  personajes[i]->loadMedia(this->gRenderer);
  }

}

void  Vista::escenario2( )
{   //posicion 0 es el fondo siempre

   printf("entra a vista ecsenario 2 %s\n", "sdf");
  for (int i = this->personajes.size(); i <this->modelo->getCantJugadores(); i++) {
  Modelo_Jugador* jugador=  this->modelo->getModeloJugador(i);

  printf("%s\n",jugador->getNombre().c_str());
  personajes.push_back(  ( new FactoryVistaPersonaje( jugador ) )->getVistaPersonaje(jugador->getNombre() ));
  personajes[i]->loadMedia(this->gRenderer);
  }

  //TODO: ver tema de scope, no se deberia volver a obtener json para que levante el fondo
  parser.obtenerJson("");
  vector<string> fondos = parser.obtenerFondos();
  personajes[0]->setearFondo((fondos.at(1)),600,350);
   //personajes[0]->setearFondo("fondo2.png",600,350);
  personajes[0]->loadMedia(this->gRenderer);

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
		auxGWindow = SDL_CreateWindow( WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,800  , 600, SDL_WINDOW_SHOWN );
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
    bool success= true;
  for (int i = 0; i <  personajes.size(); i++) {
    success=personajes[i]->loadMedia(this->gRenderer);
    if( success== false)
    {
       return success;
       }
  }

  /*for (auto* s : personajes)
  {
    s->loadMedia(this->gRenderer);
  }
*/


    return success;
    //return this->vista_jugador->loadMedia(this->gRenderer);

}


 void Vista::render(int event = 0)
 {

    SDL_SetRenderDrawColor( this->gRenderer, 0xFF, 0xFF, 0, 0xFF );
	SDL_RenderClear( this->gRenderer );

    for (int i = 0; i < personajes.size(); i++) {
     //printf("%d\n",personajes.size());



    // personajes[3]->render( 0 , 0,this->getRenderer());


    //personajes[1]->render(  0 ,   0 ,this->getRenderer());
    // personajes[2]->render(  100 ,   0 ,this->getRenderer());
    // personajes[4]->render(280, 220,this->getRenderer());
   //  personajes[5]->render(480, 200,this->getRenderer());
    //  personajes[6]->render(350, 510,this->getRenderer());
       if(personajes[i]->getModeloJugador()->getNombre()=="mario")
       {
      personajes[i]->render(personajes[i]->getModeloJugador()->getPosicionX(),\
        500-personajes[i]->getModeloJugador()->getPosicionY(),this->getRenderer());

        }else
        {
            personajes[i]->render( personajes[i]->getModeloJugador()->getPosicionX(),\
         personajes[i]->getModeloJugador()->getPosicionY(),this->getRenderer());
        }
          //mono posicionado al azar
    //if(personajes[i]->getModeloJugador()->getNombre()=="mono")
    //{
     //   printf("%s\n", "hola mono");
    // personajes[i]->render(   i*i +20, i*i +20,this->getRenderer());

   // }

    }

	SDL_RenderPresent( this->gRenderer );
 }

 void Vista::close()

 {

   for (int i = 0; i < personajes.size(); i++) {
    personajes[i]->close();

  }
        //Destroy window
        SDL_DestroyRenderer( this->gRenderer );
        SDL_DestroyWindow( this->gWindow );
        gWindow = NULL;
        gRenderer = NULL;

        //Quit SDL subsystems
        IMG_Quit();
        SDL_Quit();


 }

