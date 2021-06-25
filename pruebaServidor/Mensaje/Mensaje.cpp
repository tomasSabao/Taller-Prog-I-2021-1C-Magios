#include "Mensaje.h"

Mensaje::Mensaje()
{
    //ctor
}

Mensaje::~Mensaje()
{
    //dtor
}

void* Mensaje::getMensaje(){
	return this->msj;
}


int Mensaje::asignarMemoria(int numero_elementos, int tamanio){
	void* puntero_aux=calloc(numero_elementos,tamanio);
	if(puntero_aux!=NULL){
		this->msj=puntero_aux;
		this->tamanio=tamanio;
		return 0;
	}
	return 1;
}

int Mensaje::getTamanio(){
	return this->tamanio;
}

void Mensaje::liberarMemoria(){
	if(this->tamanio==0){
		return;
	}
	free(this->msj);
	this->tamanio=0;
}

int Mensaje::redimensionarMemoria(int numero_elementos){
	void* puntero_aux=realloc(this->msj,numero_elementos);
	if(puntero_aux==NULL){
		return -1;
	}
	this->tamanio=numero_elementos;
	return 0;
}
