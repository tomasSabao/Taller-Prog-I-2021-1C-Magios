#ifndef FONDODOS_H
#define FONDODOS_H

#include <Modelo_Jugador.h>


class FondoDos : public Modelo_Jugador
{
    public:
        FondoDos(int posicion_x=0,int posicion_y=0);
        virtual ~FondoDos();
         void  caminar();

    protected:

    private:
};

#endif // FONDODOS_H
