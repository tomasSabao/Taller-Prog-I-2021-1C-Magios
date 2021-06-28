#ifndef CONTROLADOR_H
#define CONTROLADOR_H
#include <SDL2/SDL.h>
#include <string>
#include "../Modelo/Modelo_Jugador.h"

class Controlador
{
    public:
        Controlador();
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
