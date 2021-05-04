#include "Controlador.h"





Controlador::Controlador(Modelo_Jugador* modelo_jugador)
{
    this->jugador=modelo_jugador;
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
                default :   break;
            }
        }
    else if(this->e.type==SDL_KEYUP && this->e.key.repeat==0){
            switch(e.key.keysym.sym){
                case SDLK_RIGHT: return 51;
                case SDLK_LEFT: return 41;
                case SDLK_z: return 61;
                default: break;
            }
        }


    return 0;
}




