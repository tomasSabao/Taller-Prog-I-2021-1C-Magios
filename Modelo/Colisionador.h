#ifndef COLISIONADOR_H
#define COLISIONADOR_H

#include "../Modelo/Modelo_Jugador.h"
#include "../Modelo/Modelo_Plataforma.h"
#include "../Modelo/Rectangulo.h"
#include <map>
#include <vector>


class Colisionador
{
    public:
        Colisionador();
        void agregarJugador(std::string nombre_jugador,Modelo_Jugador* mario);
        void agregarFueguito(Modelo_Jugador* fueguito);
        void agregarPlataformaDerecha(Modelo_Jugador* plataforma_derecha);
        void agregarPlataformaIzquierda(Modelo_Jugador* plataforma_izquierda);
        void agregarRectangulo(Rectangulo* rectangulo);
        void agregarEscalera(Rectangulo* rectangulo);
        void removerPlataformasDerechas();
        void removerPlataformasIzquierdas();
        void removerRectangulos();
        void desconectarJugador(std::string nombre_jugador);
        void reconectarJugador(std::string nombre_jugador);
        void chequearColision();
        void mantenerElementosEnPantalla();

        //estos se usan para detectar si los elementos se superponen
        bool chequearSuperposicionX(int pos1,int ancho1, int pos2,int ancho2);
        bool chequearSuperposicionY(int pos1,int alto1, int pos2, int alto2);
        //estos van a ser para detectar que tipo de colision se dio se dio
        bool chequearColisionLadoSuperior(int pos1_y,int alto1,int pos2_y,int alto2);
        bool chequearColisionLadoDerecho(int pos1_x,int ancho1,int pos2_x,int ancho2);
        bool chequearColisionLadoIzquierdo(int pos1_x,int ancho1,int pos2_x,int ancho2);
        //esto se usa solo para la nueva funcionalidad de subir escaleras
        void recibirTecla(int tecla_apretada,std::string nombre_jugador);
        virtual ~Colisionador();

    protected:

    private:
    	//la idea es hardcodear las velocidades
    	//cosa de que mario se mueva esa cantidad
    	std::map<std::string, Modelo_Jugador*> jugadores_conectados;
    	std::map<std::string, Modelo_Jugador*> jugadores_desconectados;
    	std::vector<Modelo_Jugador*> vector_plataformas_derechas;
    	std::vector<Modelo_Jugador*> vector_plataformas_izquierdas;
    	std::vector<Modelo_Jugador*> vector_fueguitos;

        //aca voy a tener las plataformas invisibles que forman los niveles
        std::vector<Rectangulo*>vector_rectangulos;
        //aca voy a tener las escaleras
        std::vector<Rectangulo*>vector_escaleras;
    	int size_plataformas_izq=0;
    	int size_plataformas_der=0;

       



};

#endif // COLISIONADOR_H
