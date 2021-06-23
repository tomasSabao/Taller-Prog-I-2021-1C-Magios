#include "Rectangulo.h"

Rectangulo::Rectangulo(int posX,int posY,int ancho,int alto)
{
    //ctor
    this->posx=posX;
    this->posy=posY;
    this->ancho=ancho;
    this->alto=alto;

}

int Rectangulo::getPosX(){
	return this->posx;
}
int Rectangulo::getPosY(){
	return this->posy;
}
int Rectangulo::getAncho(){
	return this->ancho;
}

int Rectangulo::getAlto(){
	return this->alto;
}
Rectangulo::~Rectangulo()
{
    //dtor
}
