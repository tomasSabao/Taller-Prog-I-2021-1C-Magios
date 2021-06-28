#include "Decodificador.h"

#define TIPO_TECLA 0
#define TIPO_LOGIN 1
#define TIPO_ACEPTACION 2
#define TIPO_SALA_LLENA 3
#define TIPO_ERROR_LOGIN 4
#define TIPO_ACTUALIZAR 5

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


int Decodificador::obtenerTipo(void* msj){
	unsigned char tipo_msj=* (char*)msj;
	tipo_msj=tipo_msj>>4;
	return tipo_msj;
}


//asumiendo que el tipo de msj es login
std::string Decodificador::obtenerUsuario(void* msj){
	void* puntero=msj;
	//el usuario va a estar dos char a derecha
	unsigned char longitud_usuario=*(char*)msj;
	longitud_usuario=longitud_usuario<<4;
	longitud_usuario=longitud_usuario>>4;
	puntero=(void*)((char*)puntero +2 );
	//unsigned char longitud_contrasenia=*(char* puntero);
	std::string usuario="";
	for(int i=0; i<longitud_usuario;i++){
		char letra=*((char*)puntero +i);
		usuario+=letra;
	}
	return usuario;
}

//se asume obviamente que el mensaje es del tipo login
std::string Decodificador::obtenerContrasenia(void* msj){
	void* puntero=msj;
	unsigned char longitud_usuario=*(char*)msj;
	longitud_usuario=longitud_usuario<<4;
	longitud_usuario=longitud_usuario>>4;
	puntero=((char*)puntero  +1);
	unsigned char longitud_contrasenia=*(char*)puntero;
	puntero=  (void*)((char*)puntero+longitud_usuario);
	puntero=(void*)((char*)puntero  +1);
	
	//ahora que esta movido el puntero
	std::string contrasenia="";
	for(int i=0;i<longitud_contrasenia;i++){
		char letra=*( (char*)puntero + i);
		contrasenia+=letra;
	}
	return contrasenia;
}

//se asume que el tipo de mensaje recibido es del tipo tecla
int Decodificador::obtenerTecla(void* msj){
	char tecla=*(char*)msj;
	tecla=tecla<<4;
	tecla=tecla>>4;
	return tecla;
}

char Decodificador::obtenerIdJugador(void* msj){
	void* puntero=(void*)((char*)msj+1);
	char id_jugador=*(char*)puntero;
	return id_jugador;
}


//i entre 1 y 12
int Decodificador::obtenerPosicionXPlataforma(void*msj, int i){
	void* puntero=msj;
	puntero=(void*) ( (char*)puntero +1);
	for(int n =0;n<i;n++){
		puntero=(void*) ((char*)puntero +4);
	}
	int posX= *(int*)puntero;
	posX=posX>>10;
	printf("Valor x devuelto: %d\n",posX);
	return posX;
}

int Decodificador::obtenerPosicionYPlataforma(void* msj, int i){
	void* puntero=msj;
	puntero=(void*)( (char*)puntero +1);
	for(int n=0;n<i;n++){
		puntero=(void*)( (char*)puntero+4);
	}
	int posY=*(int*)puntero;
	posY=posY<<22;
	posY=posY>>22;
	printf("Valor y devuelto %d\n",posY);
	return posY;
}


//el tipo del mensaje es un mensaje de seteo de path de fondo
std::string Decodificador::obtenerPathDeFondo(void* msj){
	std::string path="";
	void* puntero=msj;
	puntero=(void*)( (char*)puntero +1);
	int longitud_path=*(char*)puntero;
	puntero=(void*)((char*)puntero +1 );
	for (int i=0; i<longitud_path;i++){
		char letra=*(char*)(puntero);
		path+=letra;
		puntero=(void*)( (char*)puntero + 1);
	}
	return path;
}

//el mensaje enviado tiene que ser de actualizacion de plataformas
std::vector<int> Decodificador::obtenerPosicionesXBarriles(void* msj){
	std::vector<int>posiciones;
	void* puntero=msj;
	//salteo el primer byte, es el del tipo
	puntero=(void*)( (char*)puntero + 1);
	//se sabe que hay 12 plataformas, eso esta hardcodeado
	for(int i=0;i<4;i++){
		int buffer=*(int*)puntero;
		buffer=buffer>>12;
		printf("Valor x de barril: %d\n",buffer);
		posiciones.push_back(buffer);
		puntero=(void*)((char*)puntero + 4);
	}
	return posiciones;
}


std::vector<int> Decodificador::obtenerPosicionesYBarriles(void* msj){
	std::vector<int>posiciones;
	void* puntero=msj;
	//salteo el primer byte que tiene solo el tipo
	puntero=(void*) ( (char*)puntero +1 );
	//se sabe que hay 12 plataformas, entonces
	for(int i=0;i<4;i++){
		int posY=*((int*)puntero);
		posY=posY>>2;
		posY=posY<<22;
		posY=posY>>22;
		printf("Valor y de los barriles: %d\n",posY);
		posiciones.push_back(posY);
		puntero=(void*) ( (char*)puntero + 4);
	}
	return posiciones;
}

//funciona
std::vector<int> Decodificador::obtenerPosicionesXFueguitos(void* msj){
	std::vector<int> posiciones;
	void* puntero=msj;
	puntero=(void*)( (char*)puntero +1);
	int num_fuegos=*(char*)(puntero);
	puntero=(void*)( (char*)puntero +1);
	for (int i=0; i < num_fuegos;i++){
		int buffer=*(int*)puntero;
		buffer=buffer>>12;
		//y ahora lo coloco en el vector
		printf("Valor de la posicion x: %d\n",buffer);
		posiciones.push_back(buffer);
		//muevo el puntero
		puntero=(void*) ((char*)puntero + 4);
	}
	return posiciones;
}
//funciona
std::vector<int> Decodificador::obtenerPosicionesYFueguitos(void* msj){
	std::vector<int> posiciones;
	void* puntero=msj;
	puntero=(void*)( (char*)puntero +1);
	int num_fuegos=*(char*)(puntero);
	printf("Numero de fuegos: %d\n",num_fuegos);
	puntero=(void*)( (char*)puntero +1);
	for (int i=0; i < num_fuegos;i++){
		int buffer=*(int*)puntero;
		buffer=buffer>>2;
		buffer=buffer<<22;
		buffer=buffer>>22;
		//y ahora lo coloco en el vector
		posiciones.push_back(buffer);
		//muevo el puntero
		puntero=(void*) ((char*)puntero + 4);
	}
	return posiciones;
}
//funciona
std::vector<int> Decodificador::obtenerFramesFueguitos(void* msj){
	std::vector<int> posiciones;
	void* puntero=msj;
	puntero=(void*)( (char*)puntero +1);
	int num_fuegos=*(char*)(puntero);
	printf("Numero de fuegos: %d\n",num_fuegos);
	puntero=(void*)( (char*)puntero +1);
	for (int i=0; i < num_fuegos;i++){
		unsigned int buffer=*(int*)puntero;
		buffer=buffer<<30;
		buffer=buffer>>30;
		printf("Valor del frame: %d\n",buffer);
		//y ahora lo coloco en el vector
		posiciones.push_back(buffer);
		//muevo el puntero
		puntero=(void*) ((char*)puntero + 4);
	}
	return posiciones;

}


std::vector<int> Decodificador::obtenerFramesBarriles(void* msj){
	std::vector<int> frames;
	void* puntero=msj;
	puntero=(void*)( (char*)puntero + 1);
	int numero_barriles=4;
	puntero=(void*)( (char*)puntero + 1);
	for(int i=0; i<numero_barriles;i++){
		int buffer=*(int*)puntero;
		buffer=buffer<<30;
		buffer=buffer>>30;
		printf("Valor del frame: %d\n",buffer);
		frames.push_back(buffer);
		puntero=(void*)( (char*)puntero + 4);
	}
	return frames;
}