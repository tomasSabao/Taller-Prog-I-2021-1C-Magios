//Using SDL, SDL_image, standard IO, and strings

#include <stdio.h>
#include <string>
#include "../View/Vista.h"
#include "../Modelo/Modelo.h"
#include "../include/Controlador.h"
#include "../Modelo/LTexture.h"



SDL_Texture* loadTexture( std::string path ,SDL_Renderer* gRenderer);
bool loadMedia(SDL_Texture* gTexture,SDL_Renderer* gRenderer);


int main( int argc, char* args[] )
{
    Modelo* modelo=new Modelo();
    Modelo_Jugador* jugador=modelo->getModeloJugador();
    Controlador controlador(modelo->getModeloJugador());
    Vista vista(modelo);
    vista.init();

    //creo una textura
    LTexture* textura=new LTexture();
    //consigo la ventana y el render de vista
    SDL_Window* ventana=vista.getWindow();
    SDL_Renderer* renderer=vista.getRenderer();
    //trato de visualizar
    textura->loadFromFile("foo.png",renderer);
    int quit=0;
    //SDL_Event e;
    while(quit!=1){
        while(controlador.desencolar_evento()!=0){
            quit= controlador.descifrar_evento();
            SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( renderer );
            textura->render(0,0,NULL,renderer);
            SDL_RenderPresent(renderer);
            jugador->caminar();
         }
    }

	return 0;
}
