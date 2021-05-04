#include "Mario.h"
#include <stdio.h>


Mario::Mario()
{
    //ctor
}

Mario::~Mario()
{
    //dtor
}

void Mario::traducirTecla(int tecla_apretada){
	//aprete tecla derecha
	if(tecla_apretada ==5){
		this->aumentarVelocidadX();
	}
	//solte tecla derecha 
	if(tecla_apretada==51){
		this->reducirVelocidadX();
		/*if(this->posicion_y > 0){
			this->aplicarGravedad();
		}*/
	}
	if(tecla_apretada==4){
		this->reducirVelocidadX();
	}
	if(tecla_apretada==41){
		this->aumentarVelocidadX();
	}
	if(tecla_apretada==6){
		this->aumentarVelocidadY();
	}
	if(tecla_apretada == 61){
		this->reducirVelocidadY();
		if(this->posicion_y > 0){
			this->aplicarGravedad();
		}
	}
	//no se apreto ninguna tecla
	if(tecla_apretada ==0){
		if(this->posicion_y>0){
			this->aplicarGravedad();
		}
	}
	
}


int Mario::getPosicionX(){
	return this->posicion_x;
}

int Mario::getPosicionY(){
	return this->posicion_y;
}

/*void Mario::saltar(){
	this->posicion_y+=this->velocidad_salto;
}
*/

void Mario::aumentarVelocidadX(){
	this->velocidad_x =this->velocidad_x + this->velocidad_horizontal;

}

void Mario::reducirVelocidadX(){
	//dejarlo escrito asi, usando -= no funciona por alguna razon
	this->velocidad_x = this->velocidad_x - this->velocidad_horizontal;
}

void Mario::aumentarVelocidadY(){
	this->velocidad_y+=this->velocidad_vertical;
}

void Mario::reducirVelocidadY(){
	this->velocidad_y-=this->velocidad_vertical;
}

void Mario::aplicarGravedad(){
	this->velocidad_y-=this->gravedad;
}

void Mario::mover(){
	this->posicion_x+=this->velocidad_x;
	//tratemos de mantener la posicion este en el piso
	//esto lo quiero dejar en manos de un camarografo o algo asi
	//pero para probar el controlador vamos con esto
	this->posicion_y+=this->velocidad_y;
	if(this->posicion_y<0){
		this->posicion_y=0;
		this->velocidad_y= 0;
	}
}


void Mario::imprimirPosicion(){
	printf("posicion x: %d, posicion y: %d\n",this->posicion_x,this->posicion_y);
}

void Mario::imprimirVelocidad(){
	printf("velocidad x: %d, velocidad y: %d\n",this->velocidad_x,this->velocidad_y);
}