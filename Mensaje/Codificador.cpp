#include "Codificador.h"

Codificador::Codificador()
{
    //ctor
}

Codificador::~Codificador()
{
    //dtor
}



int Codificador::codificarMensajeTeclaDos(Mensaje* msj,int tecla_apretada,char id_jugador){
	int success=0;
	if(msj->getTamanio()!=2){
		success=msj->redimensionarMemoria(2);
		if(success==1){
			//fallo
			return 1;
		}
	}
	void* puntero_mensaje=msj->getMensaje();
	char tipo_y_tecla=this->conseguirTipoTecla(tecla_apretada);
	//se copia
	memcpy(puntero_mensaje,&tipo_y_tecla,sizeof(char));
	//se desplaza un byte
	puntero_mensaje=(void*) ( (char*)puntero_mensaje+1);
	memcpy(puntero_mensaje,&id_jugador,sizeof(char));
	return success;
}


int Codificador::codificarMensajeConexionDos(Mensaje* msj,std::string usuario,std::string contrasenia){
	int success=0;
	int longitud_usuario=usuario.size();
	if(longitud_usuario>15){
		printf("El usuario tiene un limite de 15 caracteres. Se supero esa longitud\n");
		return 1;
	}
	int longitud_contrasenia=contrasenia.size();
	if(longitud_contrasenia>15){
		printf("La contrasenia tiene un limite de 15 caracteres. Se supero esa longitud\n");
		return 1;
	}
	if(msj->getTamanio()!=longitud_usuario+longitud_contrasenia+2){
		//hay que redimensionar
		printf("Se redimensiona Memoria\n");
		success=msj->redimensionarMemoria(longitud_usuario+longitud_contrasenia+2);
		if(success==-1){
			return 1;
		}
	}
	std::cout<<"Tamanio de memoria en bytes: "<<msj->getTamanio()<<std::endl;
	//tengo el espacio, armo el mensaje
	char tipo_y_longitud=longitud_usuario;
	int aux=1<<4;
	tipo_y_longitud=tipo_y_longitud | aux;
	//tengo bien escrito tipo y longitud
	//escribo ahora la longitud de la contrasenia
	void* puntero_a_escribir=(void*) (msj->getMensaje());
	//esta posicionado ya el puntero, se hace la copia
	/*
	printf("Voy a hacer la copia del mensaje\n");
	printf("Tamanio del mensaje: %d\n",msj->getTamanio());
	printf("Posicion del puntero: %d\n",puntero_a_escribir);
	*/
	memcpy(puntero_a_escribir,&tipo_y_longitud,sizeof(char));
	//tengo que hacer un movimiento
	puntero_a_escribir=(void*) ( (char*)puntero_a_escribir +1);
	memcpy(puntero_a_escribir,&longitud_contrasenia,sizeof(char));
	puntero_a_escribir=(void*) ( (char*)puntero_a_escribir +1);
	std::cout<<"Valor del usuario: "<<usuario<<std::endl;
	memcpy(puntero_a_escribir,usuario.data(),sizeof(char)*longitud_usuario);
	puntero_a_escribir=(void*) ( (char*)puntero_a_escribir+longitud_usuario);
	std::cout<<"Valor de la contrasenia: "<<contrasenia<<std::endl;
	memcpy(puntero_a_escribir,contrasenia.data(),sizeof(char)*longitud_contrasenia);
	return success;
}

//Esta funcion se llama solo cuando el juego todavia no inicio. El user_id es asignado por el servidor
//es un valor entre 1 y 4, char.
int Codificador::codificarMensajeRespuestaLoginPositiva(Mensaje* msj,char user_id,int numero_jugadores){
	char tipo_msj='p';
	int success=0;
	char num_players;
	//necesito que el tamanio del mensaje sea suficiente
	//necesito 1 byte para el tipo, 1 byte para el user_id y 1 byte para el numero de jugadores
	//(en realidad necesito menos, pero dado que se manda de a byte, lo dejo asi)
	//total: 3 bytes
	if(msj->getTamanio() !=3){
		success=msj->redimensionarMemoria(3);
		if(success==-1){
			return 1;
		}
	}
	void* puntero_mensaje=msj->getMensaje();
	//tenemos la memoria para generar el mensaje
	memcpy(puntero_mensaje,&tipo_msj,sizeof(char));
	puntero_mensaje=(void*) ((char*)puntero_mensaje+1);
	memcpy(puntero_mensaje,&user_id,sizeof(char));
	puntero_mensaje=(void*) ((char*)puntero_mensaje+1);
	if(numero_jugadores==1){
		num_players=0x1;
	}
	if(numero_jugadores==2){
		num_players=0x2;
	}
	if(numero_jugadores==3){
		num_players=0x3;
	}
	if(numero_jugadores==4){
		num_players=0x4;
	}
	memcpy(puntero_mensaje,&num_players,sizeof(char));
	return success;

}




int Codificador::codificarMensajeActualizacionPosiciones(Mensaje* msj,int numero_jugadores){
	return 0;

}





//PRE: la tecla apretada ES uno de los valores validos que pueden alterar el estado de juego
char Codificador::conseguirTipoTecla(int tecla_apretada){
	char tecla=12;
	//supongo que el tipo tecla va a ser 0000
	//el codigo seria, en binario: 0000xxxx, donde xxxx va a ser la id del jugador
	//veamos los distintos casos
	if(tecla_apretada==5){
		tecla=0;
		return tecla;
	}

	if(tecla_apretada==4){
		tecla=1;
		return tecla;
	}

	if(tecla_apretada==6){
		tecla=2;
		return tecla;
	}

	if(tecla_apretada==2){
		tecla=3;
		return tecla;
	}

	if(tecla_apretada==8){
		tecla=4;
		return tecla;
	}

	if(tecla_apretada==9){
		tecla=5;
		return tecla;
	}

	if(tecla_apretada==51){
		tecla=6;
		return tecla;
	}

	if(tecla_apretada==41){
		tecla=7;
		return tecla;
	}

	if(tecla_apretada==61){
		tecla=8;
		return tecla;
	}

	if(tecla_apretada==32){
		tecla=9;
		return tecla;
	}

	if(tecla_apretada==81){
		tecla=10;
		return tecla;
	}

	if(tecla_apretada==91){
		tecla=11;
		return tecla;
	}
	return tecla;
}

//en teoria el id del jugador es un valor en 2 bits nomas. Voy a necesitar 2 bytes para el msj
int Codificador::codificarMensajeSalaVaciaAceptacion(Mensaje* msj, char id_jugador, int numero_max_jugadores){
	int success=0;
	if(msj->getTamanio() != 1){
		success=msj->redimensionarMemoria(1);
		if (success == -1){
			return 1;
		}
	}
	//en este punto tengo el espacio suficiente para mandar el mensaje
	char resultado=0;
	//se pone el tipo de mensaje
	char aux=1<<5;
	resultado=resultado | aux;
	char char_id=this->mapearIdJugador(id_jugador);
	char numero_max=this->mapearNumeroMaxJugadores(numero_max_jugadores);
	numero_max=numero_max<<2;
	//TODO: error en numero max
	printf("Valor de numero max: %d\n",numero_max);
	resultado=resultado | char_id;
	resultado=resultado | numero_max;
	printf("valor del mensaje: %d\n",resultado);
	//ahora falta copiar el contenido al mensaje
	void* puntero_a_msj=msj->getMensaje();
	memcpy(puntero_a_msj,&resultado,sizeof(char));
	return success;
}

int Codificador::codificarMensajeSalaLlenaRechazo(Mensaje* msj){
	int success=0;
	if(msj->getTamanio()!=1){
		success=msj->redimensionarMemoria(1);
		if(success == -1){
			return 1;
		}
	}
	//se tiene el tamanio conocido
	char resultado=0;
	char aux= 3;
	aux=aux<<4;
	resultado=resultado | aux;
	//necesito ahora copiar el resultado
	printf("Valor del mensaje: %d\n",resultado);
	memcpy(msj->getMensaje(),&resultado,sizeof(char));
	return success;
}


int Codificador::codificarMensajeErrorUsuarioContraseniaRechazo(Mensaje* msj){
	int success=0;
	if(msj->getTamanio() != 1){
		success=msj->redimensionarMemoria(1);
		if(success==-1){
			return 1;
		}
	}
	//esta el espacio, lo que sigue es meter el valor
	char resultado=4;
	resultado=resultado<<4;
	memcpy(msj->getMensaje(),&resultado,sizeof(char));
	return success;
}

//los mapas tienen todos que tener el mismo tamanio y las mismas claves
int Codificador::codificarMensajeActualizacion(Mensaje* msj,std::map<char,int>mapa_posiciones_x,std::map<char,int>mapa_posiciones_y,std::map<char,int>mapa_frames){
	int success=0;
	int num_jugadores=mapa_posiciones_x.size();
	int tamanio_en_bytes=1+4*num_jugadores;
	if(msj->getTamanio()!=tamanio_en_bytes){
		success=msj->redimensionarMemoria(tamanio_en_bytes);
		if(success==-1){
			return 1;
		}
	}
	//primero necesito asignar el tipo de mensaje
	char resultado=5;
	char num_players=num_jugadores;
	resultado=resultado<<4;
	resultado=resultado | num_players;
	//se copia ahora
	void * puntero_a_msj=msj->getMensaje();
	memcpy(puntero_a_msj,&resultado,sizeof(char));
	printf("valor de resultado: %d\n",resultado);
	puntero_a_msj=(void*) ( (char*)puntero_a_msj + 1);
	//ahora tengo que armar el entero con los valores
	std::map<char,int>::iterator it;
	char tipo_mensaje=5;

	for (it=mapa_posiciones_x.begin();it!=mapa_posiciones_x.end();it++){
		char id_jugador=it->first;
		int elementoACopiar=0;
		int posX=mapa_posiciones_x[id_jugador];
		//y ahora tengo que partir 10 bits en un byte
		int aux=posX<<15;
		elementoACopiar=elementoACopiar | aux;
		int posY=mapa_posiciones_y[id_jugador];
		aux=posY;
		aux=aux<<5;
		elementoACopiar=elementoACopiar|aux;
		int frame=mapa_frames[id_jugador];
		aux=frame;
		elementoACopiar=elementoACopiar | aux;
		//me comi el guardar el id, lo hago aca
		aux=this->mapearIdJugador(id_jugador);
		aux=aux<<25;
		elementoACopiar=elementoACopiar|aux;
		memcpy(puntero_a_msj,&elementoACopiar,sizeof(int));
		printf("Valor de elementoACopiar: %d\n",elementoACopiar);
		puntero_a_msj=(void*) ( (int*)puntero_a_msj + 1);

	}
	return 0;



}


char Codificador::mapearIdJugador(char id_jugador){
	if(id_jugador=='1'){
		return 0;
	}
	if(id_jugador=='2'){
		return 1;
	}
	if(id_jugador=='3'){
		return 2;
	}
	if(id_jugador=='4'){
		return 3;
	}
}



char Codificador::mapearNumeroMaxJugadores(int numero_max){
	if(numero_max==1){
		return 0;
	}
	if(numero_max==2){
		return 1;
	}
	if(numero_max==3){
		return 2;
	}
	if(numero_max==4){
		return 3;
	}
	//en este caso el numero maximo no es valido, entonces se pone por defecto uno
	printf("El valor de numero maximo no es valido. Se pone por defecto 1\n");
	return 0;
}

char Codificador::mapearNumeroDeFrame(int numero_frame){
	char valor=numero_frame;
	return valor;
}


int Codificador::codificarMensajeInicioJuego(Mensaje* msj){
	//el mensaje es de un solo byte entonces necesito ese espacio
	int tipo_mensaje=10;
	int success=0;
	if(msj->getTamanio()!=1){
		success=msj->redimensionarMemoria(1);
	}
	if(success==-1){
		printf("Fallo la redimension de la memoria\n");
		return success;
	}
	//tengo el espacio suficiente para guardar la memoria
	char mensaje=tipo_mensaje;
	//necesito hacer el shifteo
	mensaje=mensaje<<4;
	//nada mas, con esto basta
	memcpy(msj->getMensaje(),&mensaje,1);
	return success;
}

int Codificador::codificarMensajeDesconexionDeUnJugador(Mensaje* msj,char id_jugador){
	int tipo_mensaje=12;
	int success=0;
	if(msj->getTamanio()!=1){
		success=msj->redimensionarMemoria(1);
	}
	if(success==-1){
		printf("Fallo la redimension de la memoria\n");
		return success;
	}
	//tengo el espacio para guardar la memoria
	char mensaje=tipo_mensaje;
	mensaje=mensaje<<4;
	mensaje=mensaje | id_jugador;

	memcpy(msj->getMensaje(),&mensaje,1);
	return success;
}

int Codificador::codificarMensajeReconexionDeUnJugador(Mensaje* msj,char id_jugador){
	int tipo_mensaje=13;
	int success=0;
	if(msj->getTamanio()!=1){
		success=msj->redimensionarMemoria(1);
	}
	if(success == -1){
		printf("Fallo la redimension de la memoria\n");
		return success;
	}
	char mensaje=tipo_mensaje;
	mensaje=mensaje<<4;
	mensaje=mensaje | id_jugador;

	memcpy(msj->getMensaje(),&mensaje,1);
	return success;
}

int Codificador::codificarMensajeAvanceDeNivel(Mensaje* msj, int numero_fueguitos){
	//necesito 2 bytes de espacio
	int success=0;
	if(msj->getTamanio() !=2){
		success=msj->redimensionarMemoria(2);
	}
	//en teoria tengo todo el espacio para mandar el mensaje
	int tipo_mensaje=6;
	char tipo_msj=tipo_mensaje;
	tipo_msj=tipo_msj<<4;

	char fuegos=numero_fueguitos;
	//entonces lo que falta es copiar
	void* puntero=msj->getMensaje();
	//copiamos el tipo
	memcpy(puntero,&tipo_msj,1);
	//movemos el puntero
	puntero=(void*)( (char*)puntero +1);
	memcpy(puntero,&fuegos,1);
	return success;
}
//esta hardcodeado en 4 barriles, eso es lo que se va a codificar
//vamos con 17 bytes en lugar
int Codificador::codificarMensajeActualizacionPosicionesBarriles(Mensaje* msj, std::vector<int>posiciones_x, std::vector<int>posiciones_y,std::vector<int>frames){
	int tipo_mensaje=8;
	int success=0;
	if(msj->getTamanio() != 17){
		success=msj->redimensionarMemoria(17);
	}
	if(success!=0){
		printf("Fallo la redimension\n");
		return success;
	}
	//tengo el espacio para escribir el mensaje
	//necesito un buffer
	void* puntero=msj->getMensaje();
	//necesito primero codificar el tipo del mensaje
	char tipo_msj=tipo_mensaje;
	tipo_msj=tipo_msj<<4;
	//escribo el tipo
	memcpy(puntero,&tipo_msj,1);
	//muevo el puntero una posicion a la derecha
	puntero=(void*) ((char*)puntero +1);
	//ahora tengo que recorrer la totalidad de los vectores
	for(int i=0;i<4;i++){
		int posX=posiciones_x[i];
		int posY=posiciones_y[i];
		int frame=frames[i];
		int buffer=0;
		posX=posX<<12;
		posY=posY<<2;
		//ahora queda armar esta parte del mensaje
		buffer=frame | posX | posY;
		//ahora faltaria copiarlo
		memcpy(puntero,&buffer,4);
		puntero=(void*)(((char*)puntero)+4);
	}
	return 0;
}


//las plataformas son 12 siempre
int Codificador::codificarMensajeActualizacionPosicionesPlataformas(Mensaje* msj, std::vector<int>posiciones_x, std::vector<int>posiciones_y){
	int tipo_mensaje=7;
	int success=0;
	int tamanio=2 + 12*4;
	if(msj->getTamanio() != tamanio){
		success=msj->redimensionarMemoria(tamanio);
	}
	if(success!=0){
		printf("Fallo la redimension\n");
		return success;
	}
	//tengo el espacio para escribir el mensaje
	//necesito un buffer
	void* puntero=msj->getMensaje();
	//necesito primero codificar el tipo del mensaje
	char tipo_msj=tipo_mensaje;
	tipo_msj=tipo_msj<<4;
	//escribo el tipo
	memcpy(puntero,&tipo_msj,1);
	//muevo el puntero una posicion a la derecha
	puntero=(void*) ((char*)puntero +1);
	//ahora tengo que recorrer la totalidad de los vectores
	for(int i=0;i<12;i++){
		int posX=posiciones_x[i];
		int posY=posiciones_y[i];
		//int frame=frames[i];
		int buffer=0;
		posX=posX<<10;
		//posY=posY<<2;
		//ahora queda armar esta parte del mensaje
		buffer= posX | posY;
		//ahora faltaria copiarlo
		memcpy(puntero,&buffer,4);
		puntero=(void*)(((char*)puntero)+4);
	}
	return 0;
}


int Codificador::codificarMensajePathFondo(Mensaje* msj,std::string path_fondo){
	int success=0;
	int longitud=path_fondo.length()+2;
	//necesito el numero de bytes para poder codificar el mensae
	if(msj->getTamanio() != longitud){
		success=msj->redimensionarMemoria(longitud);
	}
	if(success!=0){
		printf("Fallo la redimension\n");
		return -1;
	}
	//tengo el espacio, codifico el mensaje
	void* puntero=msj->getMensaje();
	char tipo_msj=14;
	tipo_msj=tipo_msj<<4;
	memcpy(puntero, &tipo_msj,1);
	puntero=((char*)puntero + 1);
	memcpy(puntero,&longitud,4);
	puntero=((char*)puntero +1);
	for(int i=0;i<longitud;i++){
		char letra=path_fondo[i];
		memcpy(puntero,&letra,1);
		puntero=( (char*)puntero + 1);
	}
	//en teoria tengo todo aca
	return 0;

}



int Codificador::codificarMensajeActualizacionPosicionesFueguitos(Mensaje* msj, std::vector<int>posiciones_x, std::vector<int>posiciones_y,std::vector<int> frames){
	//frames=2 bits, posiciones son de 10 bits cada una
	//el numero de fueguitos va a estar dado por el tamanio del vector
	int success=0;
	char numero_fuegos=posiciones_x.size();
	//la formula de tamanio es entonces 1 byte para el tipo,1 byte para el numero de fuegos
	//4 bytes para los datos por fueguito
	//total: 2 + 4 x #numero de fuegos
	int numero_bytes=2+4*numero_fuegos;
	if(msj->getTamanio() != numero_bytes){
		success=msj->redimensionarMemoria(numero_bytes);
	}
	if(success!=0){
		return -1;
	}
	char tipo_msj= 11;
	void* puntero=msj->getMensaje();
	memcpy(puntero,&tipo_msj,1);
	puntero=(void*) ( (char*)puntero + 1);
	//escribo ahora el numero de fueguitos
	memcpy(puntero,&numero_fuegos,1);
	puntero=(void*) ( (char*)puntero + 1);
	int buffer=0;
	for(int i=0; i <numero_fuegos; i++){
		int posX=posiciones_x[i];
		posX=posX<<12;
		int posY=posiciones_y[i];
		posY=posY<<2;
		int frame=frames[i];
		buffer= posX | posY | frame;
		//se copia
		memcpy(puntero,&buffer,4);
		//se mueve
		puntero=(void*) ( (char*)puntero + 4);
	}
	return 0;
}

int Codificador::codificarMensajeLoginRepetido(Mensaje* msj) {
	char tipo_msj = 15;
	tipo_msj = tipo_msj<<4;
	if (msj->getTamanio() != 1) {
		msj->redimensionarMemoria(1);
	}
	memcpy(msj->getMensaje(), &tipo_msj, 1);
	return 0;
}
