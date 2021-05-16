#include "../Modelo/Modelo_Jugador.h"
#define WALKING_ANIMATION_FRAMES 4
Modelo_Jugador::Modelo_Jugador(int posicion_x,int posicion_y)
{
     this->frames=0;
     this->nombre="jugador";
     this->posicion_x=posicion_x;
     this->posicion_y=posicion_y;


}

Modelo_Jugador::~Modelo_Jugador()
{
    //dtor
}


int Modelo_Jugador::getFrame()
{
 return this->frames;
}

std::string Modelo_Jugador::getNombre()
{
 return this->nombre;
}

void Modelo_Jugador::traducirTecla(int tecla_apretada){
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


int Modelo_Jugador::getPosicionX(){
	return this->posicion_x;
}

int Modelo_Jugador::getPosicionY(){
	return this->posicion_y;
}

/*void Mario::saltar(){
	this->posicion_y+=this->velocidad_salto;
}
*/

void Modelo_Jugador::aumentarVelocidadX(){
	this->velocidad_x =this->velocidad_x + this->velocidad_horizontal;

}

void Modelo_Jugador::reducirVelocidadX(){
	//dejarlo escrito asi, usando -= no funciona por alguna razon
	this->velocidad_x = this->velocidad_x - this->velocidad_horizontal;
}

void Modelo_Jugador::aumentarVelocidadY(){
	this->velocidad_y+=this->velocidad_vertical;
}

void Modelo_Jugador::reducirVelocidadY(){
	this->velocidad_y-=this->velocidad_vertical;
}

void Modelo_Jugador::aplicarGravedad(){
	this->velocidad_y-=this->gravedad;
}

void Modelo_Jugador::mover(){
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


void Modelo_Jugador::imprimirPosicion(){
	printf("posicion x: %d, posicion y: %d\n",this->posicion_x,this->posicion_y);
}

void Modelo_Jugador::imprimirVelocidad(){
	printf("velocidad x: %d, velocidad y: %d\n",this->velocidad_x,this->velocidad_y);
}

void Modelo_Jugador::setPosicionX(int pos_x){
	this->posicion_x=pos_x;
}

void Modelo_Jugador::setPosicionY(int pos_y){
	this->posicion_y=pos_y;
}
//nueva_gravedad: numero positivo
void Modelo_Jugador::setGravedad(int nueva_gravedad){
	this->gravedad=nueva_gravedad;
}

void Modelo_Jugador::caminar()
{

    if(  this->frames / 4 >= WALKING_ANIMATION_FRAMES )
        {
            this->frames = 0;
        }
     this->frames+= 1;

   // this->frames++;
    //this->frames=this->frames%WALKING_ANIMATION_FRAMES;
}



void Modelo_Jugador::fijarAnimacionMovimiento(){

	//caso en el que el jugador esta en el piso
	//
	if(this->estaParadoEnPiso()){
		if(this->velocidad_x >0){
		if(this->ultima_animacion==1){
			this->frames=5;
			this->ultima_animacion=2;
			this->ultima_direccion=1;
			return;
		}
		else{
			this->frames=3;
			this->ultima_animacion=1;
			this->ultima_direccion=1;
			return;
		}
	}
	if(this->velocidad_x<0){
		if(this->ultima_animacion==1){
			this->frames=4;
			this->ultima_animacion=2;
			this->ultima_direccion=2;
			return;
		}
		else{
			this->frames=2;
			this->ultima_animacion=1;
			this->ultima_direccion=2;
			return;
		}
	}
	if(this->velocidad_x ==0){
		if(this->ultima_direccion==1){
			this->frames=1;
			this->ultima_animacion=2;
			return;
		}
		else{
			this->frames=0;
			this->ultima_animacion=2;
			return;
		}
	}
	}
	//en este caso mario esta saltando
	else{
		if(this->ultima_direccion==1){
			this->frames=7;
			return;
		}
		else{
			this->frames=6;
		}
	}

}
bool Modelo_Jugador::estaParadoEnPiso(){
	return this->posicion_y==0;
}
void Modelo_Jugador::caminar2()
{

    if(  this->frames / 8 >= WALKING_ANIMATION_FRAMES )
        {
            this->frames = 0;
        }
     this->frames+= 1;

   // this->frames++;
    //this->frames=this->frames%WALKING_ANIMATION_FRAMES;
}
