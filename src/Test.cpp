#include "Test.h"
#include "Mario.h"

Test::Test(){
	//ctor
}
Test::~Test(){
	//dtor
}

void Test::testearMovimiento(){


	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* ventana=SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,640   , 480, SDL_WINDOW_SHOWN );
	SDL_Renderer* renderer=SDL_CreateRenderer( ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );


	Modelo* modelo= new Modelo();
 	Controlador controlador(modelo );
	LTexture* textura=new LTexture();

	textura->loadFromFile("jumpman.png",renderer);
	SDL_Rect unRect;
	unRect.x=0;
	unRect.y=0;
	unRect.w=0.03*640;
	unRect.h=0.03*480;

	Mario* mario=new Mario();

	int boton_apretado=0;
	int contador=0;
	while(boton_apretado!=1){
		while(controlador.desencolarEvento()!=0){
			printf("Evento numero: %d\n",contador);
			contador++;
			SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( renderer );
			boton_apretado=controlador.descifrarEvento();
			printf("valor descifrado: %d\n",boton_apretado);
			mario->traducirTecla(boton_apretado);
			mario->mover();
			mario->imprimirPosicion();
			mario->imprimirVelocidad();
			textura->render(mario->getPosicionX(),420-mario->getPosicionY(),&unRect,renderer);
			SDL_RenderPresent(renderer);
		}
		printf("Evento numero: %d\n",contador);
		contador++;
		//esto se activa cuando no hay inputs
		SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( renderer );
		//aplicamos gravedad para que mario no se vaya volando fuera de la pantalla
		mario->aplicarGravedad();
		mario->mover();
		mario->imprimirPosicion();
		mario->imprimirVelocidad();
		textura->render(mario->getPosicionX(),420-mario->getPosicionY(),&unRect,renderer);
		SDL_RenderPresent(renderer);

	}




}
