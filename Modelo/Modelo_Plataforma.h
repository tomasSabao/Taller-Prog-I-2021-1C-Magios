#ifndef MODELO_PLATAFORMA_H
#define MODELO_PLATAFORMA_H

#include "Modelo_Jugador.h"

class Modelo_Plataforma: public Modelo_Jugador
{
    public:
        Modelo_Plataforma(int posicion_x=0,int posicion_y=0);
        virtual ~Modelo_Plataforma();
        //quiero redefinir el método del modelo jugador
        void Caminar();

    protected:

    private:

};

#endif // MODELO_PLATAFORMA_H
