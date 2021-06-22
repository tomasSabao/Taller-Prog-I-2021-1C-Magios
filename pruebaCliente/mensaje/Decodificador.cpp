#include "Decodificador.h"

Decodificador::Decodificador()
{
    //ctor
}

Decodificador::~Decodificador()
{
    //dtor
}





//faltaria una funcion que decodifique el significado de cada valor asignado a tecla apretada, a su correspondiente
//int
void Decodificador::decodificarMensajeDos(void* msj){
	unsigned char contenedor=*(char*)msj;
	unsigned char tipo_msj=contenedor>>4;
	if(tipo_msj==0){
		//el tipo de mensaje es tecla, ahora hay que recuperar el valor de la tecla
		printf("Tipo de mensaje tecla\n");
		int tecla_apretada=contenedor;
		printf("Valor de tecla_apretada: %d\n",tecla_apretada);
		char id_jugador=*( (char*)msj +1);
		printf("Valor de id_jugador: %c\n",id_jugador);
		return;
	}
	if(tipo_msj==1){
		printf("Tipo de mensaje login\n");
		unsigned char longitud_usuario=contenedor<<4;
		longitud_usuario=longitud_usuario>>4;
		printf("Longitud de usuario: %d\n",longitud_usuario);
		unsigned char longitud_contrasenia=*((char*)msj  +1);
		printf("Longitud de contrasenia: %d\n",longitud_contrasenia);
		void* puntero_iterador=(void*)( (char*)msj +2);
		std::string usuario;
		std::string contrasenia;
		for(int i=0;i<(int)longitud_usuario;i++){
			usuario+=* ( (char*)puntero_iterador   + i);
		}
		std::cout<<"Valor de usuario: "<<usuario<<std::endl;
		puntero_iterador=(void*) ( (char*)puntero_iterador + longitud_usuario);
		for(int i=0;i<longitud_contrasenia;i++){
			contrasenia+=* ( (char*)puntero_iterador  + i);
		}
		std::cout<<"Valor de contrasenia: "<<contrasenia<<std::endl;
		return;
	}
	if(tipo_msj==2){
		printf("Tipo de mensaje login aceptacion\n");
		unsigned char user_id=contenedor<<6;
		user_id=user_id>>6;
		printf("User id asignado: %d",user_id+1);
		unsigned char numero_max=contenedor<<4;
		numero_max=numero_max >> 6;
		printf("Numero max de jugadores: %d\n",numero_max+1);
		return;
	}
	if(tipo_msj==3){
		printf("Se decodifico tipo de mensaje rechazo conexion sala llena\n");
		return;
	}
	if(tipo_msj==4){
		printf("Se decodifico tipo de mensaje rechazo error usuario contrasenia\n");
		return;
	}
	if(tipo_msj==5){
		printf("Se decodifico tipo de mensaje de actualizacion de posiciones\n");
		//saco las cosas 
		char numero_jugadores=contenedor<<4;
		numero_jugadores=numero_jugadores>>4;
		printf("Actualizacion. Numero de jugadores: %d\n",numero_jugadores);
		int buffer_x;
		int buffer_y;
		int buffer_frame;
		char id_jugador;
		void* puntero=(void*)((char*)msj+1);

		for(int i=0;i<numero_jugadores;i++){	//quiero ciclar por todos los jugadores en el servidor
			id_jugador=*(int*)puntero;
			id_jugador=id_jugador>>25;
			id_jugador=this->mapearIdJugador(id_jugador);
			printf("Valor del id jugador: %c\n",id_jugador);
			//la id del jugador funciona bien
			buffer_frame=*(int*)puntero;
			buffer_frame=buffer_frame<<27;
			buffer_frame=buffer_frame>>27;
			printf("Valor de buffer frame : %d\n",buffer_frame);
			//el buffer de frame esta funcionando
			buffer_y=*(int*)puntero;
			buffer_y=buffer_y<<17;
			buffer_y=buffer_y>>22;
			printf("Valor de buffer_y: %d\n",buffer_y);
			//el buffer de frame y esta funcionando
			buffer_x=*(int*)puntero;
			buffer_x=buffer_x<<7;
			buffer_x=buffer_x>>22;
			printf("Valor de buffer x: %d\n",buffer_x);
			//TODO: FUNCIONES QUE LE PASEN ESTOS VALORES AL CLIENTE
			return;
		}
		
	}
}


char Decodificador::mapearIdJugador(int id_jugador){
	if(id_jugador==0){
		return '1';
	}
	if(id_jugador==1){
		return '2';
	}
	if(id_jugador==2){
		return '3';
	}
	return '4';
}