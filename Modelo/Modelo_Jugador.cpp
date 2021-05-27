#include "../Modelo/Modelo_Jugador.h"
#include "../lib/Logger.h"

#define WALKING_ANIMATION_FRAMES 4

extern Logger logger;

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
	char mensaje[150];
	sprintf(mensaje,"posicion x: %d, posicion y: %d\n",this->posicion_x,this->posicion_y);
	logger.log("debug", mensaje);
}

void Modelo_Jugador::imprimirVelocidad(){
	char mensaje[150];
	sprintf(mensaje, "velocidad x: %d, velocidad y: %d\n",this->velocidad_x,this->velocidad_y);
	logger.log("debug", mensaje);
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

//OJO ACA, SI TIENEN 4 SPRITE ENTONCES PONER 3 (SPRITE 0,1,2)
 //la logica seria esta, prueben valores para darse cuaenta. mientras mas grande cuantosframeactualizo mas lento
void Modelo_Jugador::setearEpilepsia(int cantFrameActualizar, int cantidadDeSprite)
{
 this->cuantosFrameActualizo=cantFrameActualizar;
 this->cantidadDeSprite=cantidadDeSprite;//OJO ACA, SI TIENEN 4 SPRITE ENTONCES PONER 3 (SPRITE 0,1,2)
 //la logica seria esta, prueben valores para darse cuaenta. mientras mas grande cuantosframeactualizo mas lento
   /*
  if(this->frames / cuantosFrameActualizo >= cantidadDeSprite)
   {
            this->frames = 0;
        }

        this->frames+= 1;*/

}
int Modelo_Jugador::getCantFrameActualizar()
{   //esto lo voy a necesitar para renderizar ya que en el renderizado tenemos que poner que frame vamos a poner render(frame/getCantFrameActualizar)
    return this->cuantosFrameActualizo ;
}

int Modelo_Jugador::getCantFrameDelPersonaje()
{   //esto lo voy a necesitar para renderizar ya que en el renderizado tenemos que poner que frame vamos a poner render(frame/getCantFrameActualizar)
    return this->cantidadDeSprite;
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
/*
	//en animacion cero va a estar en el borde derecho superior
	if(this->ultima_animacion==0){
		this->reducirVelocidadX();
	}
	//aca baja
	if(this->ultima_animacion==100){
		this->aumentarVelocidadX();
	//	this->aumentarVelocidadX();
		this->aumentarVelocidadY();
	}
	//aca va para la derecha
	if(this->ultima_animacion==140){
		this->reducirVelocidadY();
		this->aumentarVelocidadX();
	}
	if(this->ultima_animacion==240){
		this->reducirVelocidadY();
		this->reducirVelocidadX();
	}
	if(this->ultima_animacion==280){
		this->aumentarVelocidadY();
		this->ultima_animacion=0;
		return;
	}
	this->mover();
	this->ultima_animacion++;
	*/


//vamos a usar ultima dirección

	//primero evaluamos la posicion
	if(this->getPosicionX()<=30){
		this->setPosicionX(719);
		return;
	}
	if(this->getPosicionX()>=770){
		this->setPosicionX(31);
		return;
	}

	this->mover();
}



void Modelo_Jugador::setVelocidadHorizontal(int numero){
	this->velocidad_horizontal=numero;
}

void Modelo_Jugador::setVelocidadVertical(int numero){
	this->velocidad_vertical=numero;
}

void Modelo_Jugador::setDireccion(int numero){
	this->ultima_direccion=numero;
}
