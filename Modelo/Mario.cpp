#include "Mario.h"

Mario::Mario(std::string username, int posicion_x,int posicion_y):Modelo_Jugador(username, posicion_x,posicion_y)
{
     this->nombre=username;
     this->posicion_x=posicion_x;
     this->posicion_y=posicion_y;
     this->velocidad_horizontal=3;
     this->gravedad=1;
     this->velocidad_vertical=8;
     this->cuantosFrameActualizo=0;
}

Mario::~Mario()
{
    //dtor
}
