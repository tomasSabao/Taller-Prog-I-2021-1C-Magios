#ifndef CONTROLADOR_H
#define CONTROLADOR_H
#include "Modelo.h"
#include <SDL2/SDL.h>

class Controlador
{
    public:
        Controlador(Modelo* modelo);
        int desencolarEvento();
        int descifrarEvento();

        void enviar_mensaje(std::string tecla_apretada);

        virtual ~Controlador();

    protected:

    private:
    Modelo_Jugador* jugador;
    SDL_Event e;
    const Uint8* current_key_states;

};

#endif // CONTROLADOR_H
