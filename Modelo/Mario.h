#ifndef MARIO_H
#define MARIO_H

#include <Modelo_Jugador.h>


class Mario : public Modelo_Jugador
{
    public:
        Mario(int posicion_x=0,int posicion_y=0);
        void fijarAnimacionMovimiento();
        virtual ~Mario();

    protected:

    private:
    	bool estaba_parado;
};

#endif // MARIO_H
