#include "Colisionador.h"

Colisionador::Colisionador()
{
    //ctor
}

Colisionador::~Colisionador()
{
    //dtor
}

void Colisionador::agregarJugador(std::string nombre_jugador,Modelo_Jugador* mario){
	this->jugadores_conectados.insert({nombre_jugador,mario});
}


//PRE: el nombre_jugador debe ser un valor valido. Esto se llama cuando uno de 
//los jugadores se desconecte. El puntero al mario desconectado pasa a manos
//de otro mapa, cosa de no tomarlo en cuenta para colisionar
//POST:el puntero al mario esta en el vector jugadores_desconectados
void Colisionador::desconectarJugador(std::string nombre_jugador){
	Modelo_Jugador* puntero=this->jugadores_conectados.find(nombre_jugador)->second;
	this->jugadores_conectados.erase(nombre_jugador);
	this->jugadores_desconectados.insert({nombre_jugador,puntero});
}


//PRE: el jugador tiene que estar en el vector jugadores_desconectados
//POST: el jugador esta en el vector jugadores_conectados
void Colisionador::reconectarJugador(std::string nombre_jugador){
	Modelo_Jugador* puntero=this->jugadores_conectados.find(nombre_jugador)->second;
	this->jugadores_desconectados.erase(nombre_jugador);
	this->jugadores_conectados.insert({nombre_jugador, puntero});
}

void Colisionador::agregarPlataformaIzquierda(Modelo_Jugador* plataforma_izquierda){
	this->vector_plataformas_izquierdas.push_back(plataforma_izquierda);
	this->size_plataformas_izq++;
}

void Colisionador::agregarPlataformaDerecha(Modelo_Jugador* plataforma_derecha){
	this->vector_plataformas_derechas.push_back(plataforma_derecha);
	this->size_plataformas_der++;
}

void Colisionador::agregarFueguito(Modelo_Jugador* fueguito){
	this->vector_fueguitos.push_back(fueguito);
}

void Colisionador::agregarRectangulo(Rectangulo* rectangulo){
	this->vector_rectangulos.push_back(rectangulo);
}

void Colisionador::removerPlataformasDerechas(){
	while(this->size_plataformas_der!=0){
		this->vector_plataformas_derechas.pop_back();
		this->size_plataformas_der--;
	}
}

void Colisionador::removerPlataformasIzquierdas(){
	while(this->size_plataformas_izq!=0){
		this->vector_plataformas_izquierdas.pop_back();
		this->size_plataformas_der--;
	}
}
//Esto va a mantener los elementos del escenario todos en pantalla(igual con esto solo me 
//refiero a los marios y a los fueguitos). No olvidar de remover los fueguitos del nivel 
//anterior ANTES  de hacer la transicion del nivel, sino en el nivel siguiente vamos a 
//tener a todos en pantalla
void Colisionador::mantenerElementosEnPantalla(){
	//primero se chequea el valor de los marios 
	int posX; 
	std::map<std::string,Modelo_Jugador*>::iterator it;
	for(it=this->jugadores_conectados.begin();it!=this->jugadores_conectados.end();it++){
		posX=it->second->getPosicionX();
		if(posX<0){
			it->second->setPosicionX(0);
		}
		if(posX > 770){
			it->second->setPosicionX(770);
		}
	}

	//despues se chequea el valor de los fueguitos
	std::vector<Modelo_Jugador*>::iterator it2;
	for(it2=this->vector_fueguitos.begin();it2!=this->vector_fueguitos.end();it2++){
		posX=(*it2)->getPosicionX();
		if(posX<0){
			(*it2)->setPosicionX(0);
		}
		if(posX >770){
			(*it2)->setPosicionX(770);
		}
	}
}



bool Colisionador::chequearSuperposicionX(int pos1, int ancho1, int pos2, int ancho2){
	//los comentarios se hacen tomando el sprite del objeto 1
	//primero se chequea el lado izquierdo del sprite
	if( (pos2 <= pos1)  &  (pos1 <= pos2+ancho2)){
		return true;
	}
	//se chequea el lado derecho del sprite
	if( (pos2 <= (pos1+ancho1))  & ((pos1+ancho1) <= (pos2+ancho2) ) ){
		return true;
	}
	//se chequea si el objeto 1 esta dentro del ancho del objeto 2
	if(   (pos2 <= pos1) & (pos1+ancho1 <= pos2+ancho2)  ){
		return true;
	}
	//se chequea si el objeto 2 esta dentro del ancho del objeto 1
	if( (pos1 <= pos2)  & (pos2+ancho2 <= pos1+ancho1)){
		return true;
	}
	return false;
}

bool Colisionador::chequearSuperposicionY(int pos1,int alto1,int pos2,int alto2){
	//primero se chequea el lado superior del sprite
	if( (pos2 <= pos1) & (pos1 <= pos2+alto2)){
		return true;
	}
	//ahora se chequea el lado inferior del sprite
	if( (pos1 <= pos2) &  (pos2 <= pos1 + alto1)){
		return true;
	}
	//ahora se chequea si el objeto 1 esta dentro del objeto 2
	if( (pos2 <= pos1) & (pos1+alto1 <= pos2+alto2)){
		return true;
	}
	//ahora se chequea si el objeto 2 esta dentro del objeto 1
	if( (pos1 <= pos2) & (pos2+alto2 <= pos1+alto1)){
		return true;
	}
	return false;
}


void Colisionador::chequearColision(){
	std::map<std::string,Modelo_Jugador*>::iterator mario_it;
	std::vector<Modelo_Jugador*>::iterator derecha_it;
	std::vector<Modelo_Jugador*>::iterator izquierda_it;
	std::vector<Modelo_Jugador*>::iterator fueguitos_it;
	std::vector<Rectangulo*>::iterator rectangulo_it;
	std::vector<Rectangulo*>::iterator escaleras_it;
	for(mario_it=this->jugadores_conectados.begin(); mario_it!=this->jugadores_conectados.end();mario_it++){
		//se hace un chequeo si el mario esta en una escalera, si lo esta, saltamos al siguiente mario
		//necesito los datos de la escalera para setear la animacion correspondiente
		//entonces 

		//la voy a reemplazar por una busqueda sobre todas las escaleras
		/*
		for(escaleras_it=this->vector_escaleras.begin(); escaleras_it!=this->vector_escaleras.end();escaleras_it++){
			if(this->chequearSuperposicionX(mario_it->second->getPosicionX(),45,(*escaleras_it)->getPosX(),(*escaleras_it)->getAncho())
				& this->chequearSuperposicionY(550-mario_it->second->getPosicionY(),48,(*escaleras_it)->getPosY(),(*escaleras_it)->getAncho())){
				if(mario_it->second->getEstaEnEscalera()==true){
					mario_it->second->resetVelocidadY();
					mario_it->second->setPosicionY(mario_it->second->getPosicionY()+1);
					mario_it->second->fijarAnimacionesEnEscalera();
					//mario_it->second->fijarAnimacionBordeSuperior(*escaleras_it);
					continue;
				}
			}
		}

*/


//ESTA ES LA VERSION QUE ESTA FUNCIONANDO
		
		if(mario_it->second->getEstaEnEscalera()==true){
			mario_it->second->resetVelocidadY();
			mario_it->second->setPosicionY(mario_it->second->getPosicionY()+1);
			mario_it->second->fijarAnimacionesEnEscalera();
			//TODO: codigo que maneja el sprite en funcion de la posicion en la escalera
			//como se que hay un mario que esta en colision con una escalera hago la busqueda por todos
			//las escaleras
			for(escaleras_it=this->vector_escaleras.begin(); escaleras_it!=this->vector_escaleras.end(); escaleras_it++){
				if(this->chequearSuperposicionX(mario_it->second->getPosicionX(),45,(*escaleras_it)->getPosX(),(*escaleras_it)->getAncho())
			& this->chequearSuperposicionY(550-mario_it->second->getPosicionY(),48,(*escaleras_it)->getPosY(),(*escaleras_it)->getAlto())){
					mario_it->second->fijarAnimacionBordeSuperior(*escaleras_it);
					break;

				}
			}
			continue;
		}





//DE ACA EN ADELANTE TODO ANDA BIEN
		//se hace colision entre mario y los rectangulos del escenario
		for(rectangulo_it=this->vector_rectangulos.begin(); rectangulo_it!=this->vector_rectangulos.end(); rectangulo_it++){
			if(this->chequearSuperposicionX(mario_it->second->getPosicionX(),45,(*rectangulo_it)->getPosX(),(*rectangulo_it)->getAncho())
			 & this->chequearSuperposicionY(550-mario_it->second->getPosicionY(),48,(*rectangulo_it)->getPosY(),(*rectangulo_it)->getAlto())){


			if(this->chequearColisionLadoSuperior(550-mario_it->second->getPosicionY(),48,(*rectangulo_it)->getPosY(),(*rectangulo_it)->getAlto())){
				mario_it->second->setPosicionY(550-((*rectangulo_it)->getPosY()-48));
				mario_it->second->resetVelocidadY();
				mario_it->second->setEstaEnPiso();
				mario_it->second->fijarAnimacionMovimiento();
				break;
			}
		}
		}

		//se hace  colision entre mario y plataformas derechas
		for(derecha_it=this->vector_plataformas_derechas.begin(); derecha_it!=this->vector_plataformas_derechas.end();derecha_it++){
			if(this->chequearSuperposicionX(mario_it->second->getPosicionX(),45,(*derecha_it)->getPosicionX(),42)
			 & this->chequearSuperposicionY(550-mario_it->second->getPosicionY(),48,(*derecha_it)->getPosicionY(),19)){

			//chequeo superior
			if(this->chequearColisionLadoSuperior(550-mario_it->second->getPosicionY(),48,(*derecha_it)->getPosicionY(),19)){
				mario_it->second->setPosicionY(550-((*derecha_it)->getPosicionY()-48));
				mario_it->second->resetVelocidadY();
				mario_it->second->setPosicionX(mario_it->second->getPosicionX()+1);
				mario_it->second->setEstaEnPiso();
				break;
			}
			//chequeo derecho
			if(this->chequearColisionLadoDerecho(mario_it->second->getPosicionX(),45,(*derecha_it)->getPosicionX(),19)){
				mario_it->second->setPosicionX((*derecha_it)->getPosicionX() + 45 + 1);
				break;
			}
			//chequeo izquierdo
			if(this->chequearColisionLadoIzquierdo(mario_it->second->getPosicionX(),45,(*derecha_it)->getPosicionX(),19)){
				mario_it->second->setPosicionX((*derecha_it)->getPosicionX()-45);
				break;
			}
			}
		}

		//se chequea la colision entre mario y plataformas izquierdas
		for(izquierda_it=this->vector_plataformas_izquierdas.begin(); izquierda_it!=this->vector_plataformas_izquierdas.end();izquierda_it++){
			if(this->chequearSuperposicionX(mario_it->second->getPosicionX(),45,(*izquierda_it)->getPosicionX(),42)
			 & this->chequearSuperposicionY(550-mario_it->second->getPosicionY(),48,(*izquierda_it)->getPosicionY(),19)){
				//printf("Hay colision entre mario y plataforma izquierda\n");
			//TODO: CODIGO QUE HACE ALGO SEGUN LA COLSION
			//chequeo superior
			if(this->chequearColisionLadoSuperior(550-mario_it->second->getPosicionY(),48,(*izquierda_it)->getPosicionY(),19)){
				mario_it->second->setPosicionY(550-((*izquierda_it)->getPosicionY()-48));
				mario_it->second->resetVelocidadY();
				mario_it->second->setPosicionX(mario_it->second->getPosicionX()-1);
				mario_it->second->setEstaEnPiso();
				break;
			}
			//chequeo derecho
			if(this->chequearColisionLadoDerecho(mario_it->second->getPosicionX(),45,(*izquierda_it)->getPosicionX(),19)){
				mario_it->second->setPosicionX((*izquierda_it)->getPosicionX() +45+1);
				break;
			}
			//chequeo izquierdo
			if(this->chequearColisionLadoIzquierdo(mario_it->second->getPosicionX(),45,(*izquierda_it)->getPosicionX(),19)){
				mario_it->second->setPosicionX((*izquierda_it)->getPosicionX()-45);
				break;
			}

			}
		}
		//se chequea la colision entre mario y los fueguitos
		for(fueguitos_it=this->vector_fueguitos.begin(); fueguitos_it!=this->vector_fueguitos.end();fueguitos_it++){
			if(this->chequearSuperposicionX(mario_it->second->getPosicionX(),45,(*fueguitos_it)->getPosicionX(),46)
			 & this->chequearSuperposicionY(550-mario_it->second->getPosicionY(),48,(*fueguitos_it)->getPosicionY(),46)){
				printf("Hay colision entre mario y un fueguito\n");
			//TODO: CODIGO QUE HACE ALGO SEGUN LA COLISION con fueguito
			}
		}
	//terminamos de chequear las colisiones de los marios	
	}

	//chequeo de los fueguitos segun las plataformas en las que se paran
	for(fueguitos_it=this->vector_fueguitos.begin();fueguitos_it!=this->vector_fueguitos.end();fueguitos_it++){
		for(izquierda_it=this->vector_plataformas_izquierdas.begin();izquierda_it!=this->vector_plataformas_izquierdas.end();izquierda_it++){

			if(this->chequearSuperposicionX((*fueguitos_it)->getPosicionX(),46,(*izquierda_it)->getPosicionX(),42) & 
				this->chequearSuperposicionY((*fueguitos_it)->getPosicionY(),46,((*izquierda_it)->getPosicionY()),19)){
				printf("Hay colision entre un fueguito y una plataforma izquierda\n");
			}
		}
		for(derecha_it=this->vector_plataformas_derechas.begin();derecha_it!=this->vector_plataformas_derechas.end();derecha_it++){

			if(this->chequearSuperposicionX((*fueguitos_it)->getPosicionX(),46,(*derecha_it)->getPosicionX(),42) & 
				this->chequearSuperposicionY((*fueguitos_it)->getPosicionY(),46,((*derecha_it)->getPosicionY()),19)){
				printf("Hay colision entre un fueguito y una plataforma derecha\n");
			}
		}
	}
}

//esta funcionando, se considera que esta en el lado superior solo si esta por encima de la 
//mitad del punto medio de la plataforma. se toma a 1 como el elemento que choca, y a 2 
//como el elemento que es chocado
//factor divisor me dice por cuanto quiero que se divida el alto para considerar a mario por encima
bool Colisionador::chequearColisionLadoSuperior(int pos1_y,int alto1,int pos2_y,int alto2){
	int factor_divisor=2;
	if((pos2_y <= pos1_y + alto1)  & (pos1_y+alto1 <= pos2_y + alto2/factor_divisor)){
		return true;
	}
	return false;
}

bool Colisionador::chequearColisionLadoDerecho(int pos1_x,int ancho1,int pos2_x,int ancho2){
	int factor_divisor=4;
	int factor_multiplicador=3;
	if( (pos2_x+factor_multiplicador*ancho2/factor_divisor <=pos1_x)  &  (pos2_x + ancho2 <= pos1_x + ancho1)){
		return true;
	}
	return false;
}

bool Colisionador::chequearColisionLadoIzquierdo(int pos1_x,int ancho1,int pos2_x,int ancho2){
	int factor_divisor=4;
	int factor_multiplicador=3;
	if( (pos1_x <= pos2_x)   &  (pos1_x+ancho1 <= pos2_x + ancho2 * factor_multiplicador / factor_divisor)){
		return true;
	}
	return false;
}

//pre: estoy asumiendo que si se recibe la tecla, el jugador que la apreto debe 
//estar si o si conectado


//ESTA FUNCIONANDO 
void Colisionador::recibirTecla(int tecla_apretada,std::string nombre_jugador){
	int valor_desplazamiento=3;
	Modelo_Jugador* mario=this->jugadores_conectados[nombre_jugador];
	std::vector<Rectangulo*>::iterator escaleras_it;
	for(escaleras_it=this->vector_escaleras.begin();escaleras_it!=this->vector_escaleras.end();escaleras_it++){
		//se chequea si hay superposicion de escalera con mario
		if(this->chequearSuperposicionX(mario->getPosicionX(),45,(*escaleras_it)->getPosX(),(*escaleras_it)->getAncho())
			& this->chequearSuperposicionY(550-mario->getPosicionY(),48,(*escaleras_it)->getPosY(),(*escaleras_it)->getAlto())){
			//caso hay superposicion entre mario y una escalera. 
			//caso se apreto la tecla para subir
			if(tecla_apretada==8 || tecla_apretada==81){

				//necesito condiciones de stop voy a detener el ascenso cuando mario
				//tenga la mitad del cuerpo por encima del borde superior de la escalera
				if(550-mario->getPosicionY()+23 < (*escaleras_it)->getPosY()){
					mario->setPosicionY(mario->getPosicionY() - 1);
					//printf("RecibirTecla: mario se esta movimiendo\n");
					mario->setEstaMoviendo();
					return ;
				}
				mario->setEstaEnEscalera();
				mario->setPosicionX((*escaleras_it)->getPosX());
				mario->setPosicionY(mario->getPosicionY() + valor_desplazamiento );
				mario->resetVelocidadY();
				//printf("RecibirTecla: mario se esta movimiendo\n");
				mario->setEstaMoviendo();
				return;
			}
			//caso hay superposicion entre mario y una escalera
			//caso se apreto la tecla para bajar
			if(tecla_apretada==9 || tecla_apretada==91){

				//quiero que mario no pueda bajar mas del borde inferior de la escalera
				if(550-mario->getPosicionY() >= (*escaleras_it)->getPosY() + (*escaleras_it)->getAlto()){
					mario->setPosicionY(550-(*escaleras_it)->getPosY()-(*escaleras_it)->getAlto());
					//printf("RecibirTecla: mario se esta movimiendo\n");
					mario->setEstaMoviendo();
					return;
				}
				//caso en el que estoy en el borde inferior de la escalera
				mario->setEstaEnEscalera();
				mario->setPosicionX((*escaleras_it)->getPosX());
				mario->setPosicionY(mario->getPosicionY()-valor_desplazamiento);
				mario->resetVelocidadY();
				//printf("RecibirTecla: mario se esta movimiendo\n");
				mario->setEstaMoviendo();
				return;
			}
		//aca esta que esta colisionando con una escalera, pero no se apreto arriba o abajo
			mario->setEstaQuieto();
		}
	}
}


void Colisionador::agregarEscalera(Rectangulo* rectangulo){
	this->vector_escaleras.push_back(rectangulo);
}

void Colisionador::removerRectangulos(){
	int elementos_en_vector=this->vector_rectangulos.size();
	while(elementos_en_vector!=0){
		this->vector_rectangulos.pop_back();
		elementos_en_vector--;
	}
}