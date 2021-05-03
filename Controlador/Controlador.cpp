#include "Controlador.h"





Controlador::Controlador(Modelo_Jugador* modelo_jugador)
{
    this->jugador=modelo_jugador;
    //ctor
}
Controlador::~Controlador()
{
    //dtor
}

int Controlador::desencolar_evento(){
    return SDL_PollEvent(&this->e);
}

int Controlador::descifrar_evento(){
    if(e.type==SDL_QUIT){
        return 1;
    }
    if(e.type==SDL_KEYDOWN){
    //codigo basado en el tipo de tecla presionada
        switch(this->e.key.keysym.sym){
            case SDLK_UP:
                printf("El controlador detecto tecla: arriba\n");
               // this->enviar_mensaje("TeclaArriba");
                break;
            case SDLK_DOWN:
            printf("El controlador detecto tecla: abajo\n");
                //this->enviar_mensaje("TeclaAbajo");
                break;
            case SDLK_LEFT:
            printf("El controlador detecto tecla: izq \n");
           // this->enviar_mensaje("TeclaIzquierda");
                this->jugador->caminar();
                printf("El valor DE CORREr es %d.\n",this->jugador->getFrame());
                break;
            case SDLK_RIGHT:
            printf("El controlador detecto tecla: der\n");
           // this->enviar_mensaje("TeclaDerecha");
                this->jugador->caminar();
                printf("El valor DE CORREr es %d.\n",this->jugador->getFrame());
                break;
            default:
            printf("El controlador detecto tecla: alguna\n");
                this->jugador->caminar();
                 printf("El valor DE CORREr es %d.\n",this->jugador->getFrame());
                break;
                //pasar al siguiente nivel
        }
    }
    return 0;
}




