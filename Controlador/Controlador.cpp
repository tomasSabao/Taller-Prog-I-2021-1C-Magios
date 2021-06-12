#include "Controlador.h"
#include "../Modelo/Modelo.h"




Controlador::Controlador(Modelo * modelo )
{
    this->jugador=modelo->getModeloJugador(0);
    this->current_key_states=SDL_GetKeyboardState(NULL);
    //ctor
}
Controlador::~Controlador()
{
    //dtor
}

int Controlador::desencolarEvento(){
    return SDL_PollEvent(&this->e);
}

int Controlador::descifrarEvento(){
    if(e.type==SDL_QUIT){
        return 1;
    }
    if(this->e.type==SDL_KEYDOWN && this->e.key.repeat == 0){

            switch(e.key.keysym.sym){
                case SDLK_RIGHT: return 5;
                case SDLK_LEFT: return 4;
                case SDLK_z: return 6;
                case SDLK_SPACE: return 2;
                case SDLK_UP: return 8; //agregado para hacer la suba en escaleras
                case SDLK_DOWN: return 9;//agregado para hacer el descenso en escaleras
                default :   break;
            }
        }
    else if(this->e.type==SDL_KEYUP && this->e.key.repeat==0){
            switch(e.key.keysym.sym){
                case SDLK_RIGHT: return 51;
                case SDLK_LEFT: return 41;
                case SDLK_z: return 61;
                case SDLK_SPACE: return 32;
                case SDLK_UP: return 81; //agregados para hacer la suba en escaleras
                case SDLK_DOWN: return 91;//agregados para hacer el descenso en escaleras
                default: break;
            }
        }


    return 0;
}




