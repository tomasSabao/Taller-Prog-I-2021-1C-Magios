//Using SDL, SDL_image, standard IO, and strings

#include <stdio.h>
#include <string>
#include "../View/Vista.h"
#include "../Modelo/Modelo.h"
#include "../include/Controlador.h"
#include "../Modelo/LTexture.h"
#include "../View/Vista_Jugador.h"
#include "../View/VistaMono.h"
#include "Test.h"
#include "../lib/Logger.h"
#include "../lib/Parser.h"

#define CDAD_ARGUMENTOS 2
#define POS_ARCHIVO_CONFIGURACION 1





//////////////////////


#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

bool init();
void kill();
bool loop();

// Pointers to our window, renderer, texture, music, and sound
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture *texture, *text1,*text2,*text3;
TTF_Font* font;
string input1;
string input2;
string input3;
bool scroll = true;
bool escape = false;




int login() {

	if ( !init() ) {
		system("pause");
		return 1;
	}

	while ( loop() ) {
		// wait before processing the next frame
		SDL_Delay(10);
	}

	kill();

}


bool loop() {

	static const unsigned char* keys = SDL_GetKeyboardState( NULL );

	SDL_Event e;
	SDL_Rect dest1;
    SDL_Rect border1;
	SDL_Rect dest2;
    SDL_Rect border2;
    SDL_Rect dest3;


	// Clear the window to white
	SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
	SDL_RenderClear( renderer );

	// Event loop

	while ( SDL_PollEvent( &e ) != 0 ) {
		switch (e.type) {

			case SDL_QUIT:
				return false;

			case SDL_TEXTINPUT:
                if (scroll){
                    input1 += e.text.text;
                    }
                else if (!scroll){
                    input2 += e.text.text;
                    }
				break;


			case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_ESCAPE){
                    escape = true;
                    }
                else if (scroll){
                    if (e.key.keysym.sym == SDLK_BACKSPACE && input1.size()) {
                        input1.pop_back();
                    }
				}
                else if (!scroll){
                    if (e.key.keysym.sym == SDLK_BACKSPACE && input2.size()) {
                        input2.pop_back();
                    }
				}
				break;

            case SDL_MOUSEBUTTONDOWN:
                scroll = !scroll;
				break;

		}
	}

	// Render texture
	SDL_RenderCopy(renderer, texture, NULL, NULL);

	SDL_Color foreground = { 0, 0, 0 };
	if (escape){
    if (input1 == "mario" && input2 == "donkey"){
    	cout << "CONTRASEÑA CORRECTA" << endl;
        return false;


    }
    else{
    cout << "CONTRASEÑA INCORRECTA" << endl;
        input3 ="Wrong user or password";
    }
    escape = false;


	}
	else if ( input1.size() ||  input2.size() || input3.size()) {
		if(input1.size()){
		SDL_Surface* text_surf1 = TTF_RenderText_Solid(font, input1.c_str(), foreground);
		text1 = SDL_CreateTextureFromSurface(renderer, text_surf1);

		dest1.x = 320 - (text_surf1->w / 2.0f);
		dest1.y = 180;
		dest1.w = text_surf1->w;
		dest1.h = text_surf1->h;

		SDL_RenderCopy(renderer, text1, NULL, &dest1);

		SDL_DestroyTexture(text1);
		SDL_FreeSurface(text_surf1);
}
        if (input2.size()){
        SDL_Surface* text_surf2 = TTF_RenderText_Solid(font, input2.c_str(), foreground);
		text2 = SDL_CreateTextureFromSurface(renderer, text_surf2);

		dest2.x = 320 - (text_surf2->w / 2.0f);
		dest2.y = 360;
		dest2.w = text_surf2->w;
		dest2.h = text_surf2->h;


		SDL_RenderCopy(renderer, text2, NULL, &dest2);


		SDL_DestroyTexture(text2);
		SDL_FreeSurface(text_surf2);
        }

        if (input3.size()){
                SDL_Surface* text_surf3 = TTF_RenderText_Solid(font, input3.c_str(), foreground);
		text3 = SDL_CreateTextureFromSurface(renderer, text_surf3);

		dest3.x = 320 - (text_surf3->w / 2.0f);
		dest3.y = 460;
		dest3.w = text_surf3->w;
		dest3.h = text_surf3->h;


		SDL_RenderCopy(renderer, text3, NULL, &dest3);


		SDL_DestroyTexture(text3);
		SDL_FreeSurface(text_surf3);
        }
	}
	    //borde rect dest1

    border1.x = 130;
	border1.y = 180;
	border1.w = 400;
	border1.h = 70;
    SDL_RenderDrawRect(renderer,&border1);

    border2.x = 130;
	border2.y = 360;
	border2.w = 400;
	border2.h = 70;
    SDL_RenderDrawRect(renderer,&border2);


	// Update window
	SDL_RenderPresent( renderer );

	return true;
}

bool init() {
	if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
		cout << "Error initializing SDL: " << SDL_GetError() << endl;
		return false;
	}

	if ( IMG_Init(IMG_INIT_PNG) < 0 ) {
		cout << "Error initializing SDL_image: " << IMG_GetError() << endl;
		return false;
	}

	// Initialize SDL_ttf
	if ( TTF_Init() < 0 ) {
		cout << "Error intializing SDL_ttf: " << TTF_GetError() << endl;
		return false;
	}

	window = SDL_CreateWindow( "Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN );
	if ( !window ) {
		cout << "Error creating window: " << SDL_GetError()  << endl;
		return false;
	}

	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
	if ( !renderer ) {
		cout << "Error creating renderer: " << SDL_GetError() << endl;
		return false;
	}

	SDL_Surface* buffer = IMG_Load("test.png");
	if ( !buffer ) {
		cout << "Error loading image test.png: " << SDL_GetError() << endl;
		return false;
	}

	texture = SDL_CreateTextureFromSurface( renderer, buffer );
	SDL_FreeSurface( buffer );
	buffer = NULL;
	if ( !texture ) {
		cout << "Error creating texture: " << SDL_GetError() << endl;
		return false;
	}

	// Load font
	font = TTF_OpenFont("font.ttf", 72);
	if ( !font ) {
		cout << "Error loading font: " << TTF_GetError() << endl;
		return false;
	}

	// Start sending SDL_TextInput events
	SDL_StartTextInput();

	return true;
}

void kill() {
	SDL_StopTextInput();

	TTF_CloseFont( font );
	SDL_DestroyTexture( texture );
	texture = NULL;

	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}


////////////////////
















extern Logger logger;
Parser parser = Parser();

int main( int argc, char* argv[] )
{
    ///////////
    login();
    if (input1 != "mario" && input2 != "donkey"){
    	return 1;
    }
    ////////////



    std::string archivo_configuracion;

    if (argc >= CDAD_ARGUMENTOS) {
        archivo_configuracion = argv[POS_ARCHIVO_CONFIGURACION];
    } else {
        archivo_configuracion = "lib/default.json";
    }

    parser.obtenerJson(archivo_configuracion);
    std::string nivel_log = parser.obtenerNivelLog();
    logger.setNivelLog(nivel_log);
    //continua el flujo



    logger.log("info","Inicio del juego.");

    std::map<std::string, std::string> enemigos = parser.obtenerEnemigos();
    std::vector<std::string> fondos = parser.obtenerFondos();

    Modelo* modelo=new Modelo();
    //Modelo_Jugador* jugador=modelo->getModeloJugador();
    //VistaMono *vistaMono = new vistaMono(jugador);

    if (enemigos.find("fuego-1") != enemigos.end()) {
        cout << "Se encontro fuego-1 con "<< enemigos["fuego-1"] << " enemigos" << endl;
        modelo->escenario1("fueguito", std::stoi(enemigos["fuego-1"]));
    }
    else
    {
        cout << "Se encontro fuego-default-1 con "<< enemigos["fuego-default-1"] << " enemigos" << endl;
        modelo->escenario1("fueguito-default", std::stoi(enemigos["fuego-default-1"]));
    }

    //Modelo* modelo=new Modelo();
    // Modelo_Jugador* jugador=modelo->getModeloJugador();
    Controlador controlador(modelo);

    cout << "antes de crear la Vista" << endl;

    //TODO: rompe ACA
    Vista* vista=new Vista(modelo);

    cout << "antes del init de vista" << endl;

    vista->init();
    vista->loadMedia();
    //
    Modelo_Jugador* mario=NULL;
    for (int i = 0; i < modelo->getCantJugadores( ); i++) {

        cout << "loop de jugadores" << i << endl;

        if  (  modelo->getModeloJugador(i)->getNombre()=="mario")
        {
          mario=modelo->getModeloJugador(i);
        }

    }


    //
    int quit=0;

    //SDL_Event e;
    while(quit!=1){
        while(controlador.desencolarEvento()!=0){
            //
            quit= controlador.descifrarEvento();
            if(quit==32)
            {

            if (enemigos.find("fuego-2") != enemigos.end()) {
                cout << "Se encontro fuego-1 con "<< enemigos["fuego-1"] << " enemigos" << endl;
                modelo->escenario2("fueguito", std::stoi(enemigos["fuego-2"]));
            }
            else
            {
                cout << "Se encontro fuego-default-2 con "<< enemigos["fuego-default-2"] << " enemigos" << endl;
                modelo->escenario2("fueguito-default", std::stoi(enemigos["fuego-default-2"]));
            }
            vista->escenario2();
            }
            mario->traducirTecla(quit);
            mario->mover();
            mario->imprimirPosicion();
            mario->imprimirVelocidad();
            modelo->acciones();
            vista->render(quit);

         }
            mario->aplicarGravedad();
            mario->mover();
            modelo->acciones();
            vista->render(quit);
            //modelo->getModeloJugador(0)->caminar();


            //modelo->getMono()->caminar();
            //printf("Evento numero: %d\n",modelo->getModeloJugador(7)->getFrame());


    }
    /*Test unTest;
    //unTest.testearMovimiento();
    unTest.testearCreacionVistaMario();*/
    return 0;

}
