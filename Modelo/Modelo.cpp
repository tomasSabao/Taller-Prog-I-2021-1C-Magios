#include <random>
#include <iostream>
#include <math.h>
#include "../Modelo/Modelo.h"
#include "../Modelo/Mario.h"
#include "../Modelo/FactoryPersonaje.h"
#include "../Modelo/Modelo_Plataforma.h"

#define persona 0
#define persona2 1
#define mono 2
#define fondo 3
#define fueguito1 4
#define fueguito2 5
#define fuegoPiso 6
#define mario 7


Modelo::Modelo()
{
    //this->mono=new Mono();
    //this->modelosPersonajes=std::vector<Modelo_Jugador*>();
    this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("fondo"));
    //this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("jugador",300,50));
    //this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("jugador",500,20));
    this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("mono",500,12));

    //TODO: borrar esto, van a haber multiples jugadores
    //this->jugador= new Modelo_Jugador();
    //TODO: eliminar esto, agregarlo en el agregarJugador.
    //this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("mario",350,350));
}

Modelo::~Modelo()
{
    //dtor
}

void Modelo::agregarJugador(std::string username, int id)
{
    this->jugador= new Modelo_Jugador(username);
    this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje(username,350,350));
    //Esto es para hacer el getPersonaje(username,..,..).
    this->nombreJugadores.push_back(username);
}

void Modelo::escenario2(std::string tipo_enemigo, int cantidad_fueguitos)
{
    printf("Entre al esceneraio %d\n",modelosPersonajes.size());

    //solo para testear colision
    //la altura debe ser 580 para el piso
    Rectangulo* piso1=new Rectangulo(0,580,160,600);
    Rectangulo* piso2=new Rectangulo(250,580,65,600);
    Rectangulo* piso3=new Rectangulo(405,580,55,600);
    Rectangulo* piso4=new Rectangulo(550,580,60,600);
    Rectangulo* piso5=new Rectangulo(700,580,160,600);
    Rectangulo* piso6=new Rectangulo(0,470,160,50);
    Rectangulo* piso7=new Rectangulo(250,470,65,50);
    Rectangulo* piso8=new Rectangulo(405,470,55,50);
    Rectangulo* piso9=new Rectangulo(550,470,60,50);
    Rectangulo* piso10=new Rectangulo(700,470,160,50);
    Rectangulo* piso11=new Rectangulo(778,380,40,50);
    Rectangulo* piso12=new Rectangulo(0,380,40,50);
    Rectangulo* piso13=new Rectangulo(0,287,40,50);
    Rectangulo* piso14=new Rectangulo(778,287,40,50);
    Rectangulo* piso15=new Rectangulo(778,210,40,50);
    Rectangulo* piso16=new Rectangulo(600,210,100,50);
    Rectangulo* piso17=new Rectangulo(100,200,420,50);
    Rectangulo* piso18=new Rectangulo(340,135,150,50);
    Rectangulo* escalera1=new Rectangulo(111,480,30,800);
    Rectangulo* escalera2=new Rectangulo(780,380,30,110);
    Rectangulo* escalera3=new Rectangulo(0,290,40,95);
    Rectangulo* escalera4=new Rectangulo(780,215,30,110);
    Rectangulo* escalera5=new Rectangulo(470,135,50,30);
    //Rectangulo* escalera_debug=new Rectangulo(350,0,50,800);

    this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("barril",100,0));
    this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("barril",200,0));

    this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("barril",450,0));
    this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("barril",0,0));

    this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("fuegopiso",170,510));
    this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("fuegopiso",315,510));
    this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("fuegopiso",460,510));
    this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("fuegopiso",610,510));
    //meto cuatro plataformas que se mueven a izquierda
    this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("plataforma",400,286));
    this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("plataforma",622,286));
    this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("plataforma",178,286));

    //meto una plataforma que se mueve a derecha
    //valor y original= 310
    this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("plataforma_derecha",400,300));
    this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("plataforma_derecha",622,300));
    this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("plataforma_derecha",178,300));

    //ahora quiero poner una plataforma derecha en el segmento de abajo
    this->modelosPersonajes.push_back( (new FactoryPersonaje() )->getPersonaje("plataforma_derecha",440,375));
    this->modelosPersonajes.push_back( (new FactoryPersonaje() )->getPersonaje("plataforma_derecha",662,375));
    this->modelosPersonajes.push_back( (new FactoryPersonaje() )->getPersonaje("plataforma_derecha",228,375));

    //ahora pongo las plataformas izquierdas en el segmento de abajo
    this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("plataforma",400,395));
    this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("plataforma",622,395));
    this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje("plataforma",178,395));

    for (int i = 0; i < modelosPersonajes.size(); i++) {
        printf("nombre %s", this->modelosPersonajes[i]->getNombre().c_str());
        if(this->modelosPersonajes[i]->getNombre()=="fueguito"){
            this->modelosPersonajes[i]->setPosicionX(10000);
            this->modelosPersonajes[i]->setPosicionY(10000);
        }

        if(this->modelosPersonajes[i]->getNombre()=="fueguito-default"){
            this->modelosPersonajes[i]->setPosicionX(10000);
            this->modelosPersonajes[i]->setPosicionY(10000);
        }

        if(this->modelosPersonajes[i]->getNombre()=="mono"){
            this->modelosPersonajes[i]->setPosicionX(100);
            this->modelosPersonajes[i]->setPosicionY(70);
        }
    }

    int posiciones_x[cantidad_fueguitos]={};
    int posiciones_y[cantidad_fueguitos]={};

    int plataformas_y[5]={155,420,535};
    std::uniform_int_distribution<int> plat_y(0, 2);

    int plataformas_x_1_inicio[2] = {200,590};
    int plataformas_x_1_fin[2] = {400,620};

    int plataformas_x_2_inicio[5] = {0,220,380,530,680};
    int plataformas_x_2_fin[5] = {120,300,450,600,790};

    int* plataformas_x [3] = {plataformas_x_1_inicio,plataformas_x_2_inicio,plataformas_x_2_inicio};

    //esto es para la aleatoriedad
    std::random_device rd_x;
    std::random_device rd_y;
    std::uniform_int_distribution<int> dist_x_1(0, 2);
    std::uniform_int_distribution<int> dist_x_2(0, 4);
    int plat_rand_y;
    int posicion_x_aleatoria;
    int posicion_y_aleatoria;
    int i = 0;
    int cantidad_fueguitos_generados = 0;
    int dist=0;
    int plataforma;
    while(i<cantidad_fueguitos){
        int plataforma_aleatoria_y = plat_y(rd_y);
        posicion_y_aleatoria=plataformas_y[plataforma_aleatoria_y];
        int* plataforma_aleatoria_x=plataformas_x[plataforma_aleatoria_y];
        if (sizeof(plataforma_aleatoria_x[0]>2)){
            plataforma = dist_x_2(rd_x);
            std::uniform_int_distribution<int> distribucion_x_1(plataformas_x_2_inicio[plataforma], plataformas_x_2_fin[plataforma]);
            posicion_x_aleatoria=distribucion_x_1(rd_x);
        }
        else{
            std::uniform_int_distribution<int> distribucion_x_1(plataformas_x_1_inicio[plataforma], plataformas_x_1_fin[plataforma]);
            posicion_x_aleatoria=distribucion_x_1(rd_x);
        }

        dist = 0;
        while(dist<cantidad_fueguitos_generados){
            if((sqrt(pow(posicion_x_aleatoria-posiciones_x[dist],2)+pow(posicion_y_aleatoria-posiciones_y[dist],2)) <= 40) || (sqrt(pow(posicion_x_aleatoria-500,2)+pow(posicion_y_aleatoria-12,2)) <= 130)){
            int plataforma_aleatoria_y = plat_y(rd_y);
            posicion_y_aleatoria=plataformas_y[plataforma_aleatoria_y];
            int* plataforma_aleatoria_x=plataformas_x[plataforma_aleatoria_y];
            if (sizeof(plataforma_aleatoria_x[0]>2)){
                plataforma = dist_x_2(rd_x);
                std::uniform_int_distribution<int> distribucion_x_1(plataformas_x_2_inicio[plataforma], plataformas_x_2_fin[plataforma]);
                posicion_x_aleatoria=distribucion_x_1(rd_x);
            }
            else{
                std::uniform_int_distribution<int> distribucion_x_1(plataformas_x_1_inicio[plataforma], plataformas_x_1_fin[plataforma]);
                posicion_x_aleatoria=distribucion_x_1(rd_x);
                }

                dist=-1;
            }
            dist++;
        }
        posiciones_x[i] = posicion_x_aleatoria;
        posiciones_y[i] = posicion_y_aleatoria;
        this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje(tipo_enemigo,posicion_x_aleatoria,posicion_y_aleatoria));
        i++;
        cantidad_fueguitos_generados++;
    }

    printf("Entre al escenario %d\n",modelosPersonajes.size());

    //tengo que remover a los marios agregado en el primer nivel
    for (int j = 0; j < nombreJugadores.size(); j++) {
        this->colisionador.desconectarJugador(nombreJugadores[j]);
    }
    this->colisionador.removerRectangulos();
    //aca quiero poner el colisionador
    this->agregarObjetosAlColisionador();
    this->agregarRectangulo(piso1);
    this->agregarRectangulo(piso2);
    this->agregarRectangulo(piso3);
    this->agregarRectangulo(piso4);
    this->agregarRectangulo(piso5);
    this->agregarRectangulo(piso6);
    this->agregarRectangulo(piso7);
    this->agregarRectangulo(piso8);
    this->agregarRectangulo(piso9);
    this->agregarRectangulo(piso10);
    this->agregarRectangulo(piso11);
    this->agregarRectangulo(piso12);
    this->agregarRectangulo(piso13);
    this->agregarRectangulo(piso14);
    this->agregarRectangulo(piso15);
    this->agregarRectangulo(piso16);
    this->agregarRectangulo(piso17);
    this->agregarRectangulo(piso18);
    this->agregarEscalera(escalera1);
    this->agregarEscalera(escalera2);
    this->agregarEscalera(escalera3);
    this->agregarEscalera(escalera4);
    this->agregarEscalera(escalera5);
    //this->agregarEscalera(escalera_debug);
}


void Modelo::escenario1(std::string tipo_enemigo, int cantidad_fueguitos)
{
    int posiciones_x[cantidad_fueguitos]={};
    int posiciones_y[cantidad_fueguitos]={};
    int rectas_ordenada[4] = {388,350,222,185};
    double rectas_pendiente[4] = {0.06,-0.06,0.06,-0.06};

    //esto es para la aleatoriedad
    std::random_device rd_x;
    std::random_device rd_y;
    std::random_device platform;
    std::uniform_int_distribution<int> dist_x(0, 700);
    std::uniform_int_distribution<int> dist_platform(0,3);

    int random_platform;
    int posicion_x_aleatoria;
    int posicion_y_aleatoria;
    int i = 0;
    int cantidad_fueguitos_generados = 0;
    int dist=0;

    while(i<cantidad_fueguitos){
        posicion_x_aleatoria=dist_x(rd_x);
        random_platform =dist_platform(platform);
        posicion_y_aleatoria=posicion_x_aleatoria*rectas_pendiente[random_platform] + rectas_ordenada[random_platform];
        dist = 0;
        while(dist<cantidad_fueguitos_generados){
            if((sqrt(pow(posicion_x_aleatoria-posiciones_x[dist],2)+pow(posicion_y_aleatoria-posiciones_y[dist],2)) <= 40) || (sqrt(pow(posicion_x_aleatoria-500,2)+pow(posicion_y_aleatoria-12,2)) <= 130)){
                posicion_x_aleatoria=dist_x(rd_x);
                posicion_y_aleatoria=posicion_x_aleatoria*rectas_pendiente[random_platform] + rectas_ordenada[random_platform];
                dist=-1;
            }
            dist++;
        }
        posiciones_x[i] = posicion_x_aleatoria;
        posiciones_y[i] = posicion_y_aleatoria;
        this->modelosPersonajes.push_back( ( new FactoryPersonaje() )->getPersonaje(tipo_enemigo,posicion_x_aleatoria,posicion_y_aleatoria));
        i++;
        cantidad_fueguitos_generados++;
    }

    printf("Entre al escenario%d\n",cantidad_fueguitos);
    //this->modelosPersonajes=std::vector<Modelo_Jugador*>();

    //esto es para agregar el mario al colisionador
    //ES SOLO PARA TESTEO
    this->agregarObjetosAlColisionador();

    //tengo que empezar agregar los rectangulos
    Rectangulo* piso1=new Rectangulo(0,540,400,50);
    Rectangulo* piso2=new Rectangulo(400,535,62,50);//voy a usar 65 para el ancho de los pedazos
    Rectangulo* piso3=new Rectangulo(462,533,62,50);
    Rectangulo* piso4=new Rectangulo(527,529,62,50);
    Rectangulo* piso5=new Rectangulo(593,527,62,50);
    Rectangulo* piso6=new Rectangulo(655,526,62,50);
    Rectangulo* piso7=new Rectangulo(712,525,62,50);

    Rectangulo* piso8=new Rectangulo(722,472,35,20);
    Rectangulo* piso9=new Rectangulo(663,471,50,20);
    Rectangulo* piso10=new Rectangulo(613,467,50,20);
    Rectangulo* piso11=new Rectangulo(563,464,50,20);
    Rectangulo* piso12=new Rectangulo(503,461,60,20);
    Rectangulo* piso13=new Rectangulo(443,459,60,20);
    Rectangulo* piso14=new Rectangulo(383,457,60,20);//
    Rectangulo* piso15=new Rectangulo(323,454,60,20);
    Rectangulo* piso16=new Rectangulo(263,451,60,20);
    Rectangulo* piso17=new Rectangulo(203,447,60,20);
    Rectangulo* piso18=new Rectangulo(143,443,60,20);
    Rectangulo* piso19=new Rectangulo(83,441,60,20);
    Rectangulo* piso20=new Rectangulo(23,439,60,20);

    Rectangulo* piso21=new Rectangulo(83,390,35,20);
    Rectangulo* piso22=new Rectangulo(118,385,50,20);
    Rectangulo* piso23=new Rectangulo(168,382,60,20);
    Rectangulo* piso24=new Rectangulo(228,379,60,20);
    Rectangulo* piso25=new Rectangulo(288,376,120,20);
    Rectangulo* piso26=new Rectangulo(408,372,120,20);
    Rectangulo* piso27=new Rectangulo(528,369,120,20);
    Rectangulo* piso28=new Rectangulo(608,366,140,20);
    Rectangulo* piso29=new Rectangulo(748,363,100,20);

    Rectangulo* piso30=new Rectangulo(668,306,95,20);
    Rectangulo* piso31=new Rectangulo(543,302,95,20);
    Rectangulo* piso32=new Rectangulo(428,297,95,20);
    Rectangulo* piso33=new Rectangulo(313,292,95,20);
    Rectangulo* piso34=new Rectangulo(200,289,95,20);
    Rectangulo* piso35=new Rectangulo(87,284,95,20);
    Rectangulo* piso36=new Rectangulo(0,276,50,20);

    Rectangulo* piso37=new Rectangulo(87,226,35,20);
    Rectangulo* piso38=new Rectangulo(122,222,50,20);//esta es la que tiene la escalera abajo
    Rectangulo* piso39=new Rectangulo(172,219,120,20);
    Rectangulo* piso40=new Rectangulo(292,215,120,20);
    Rectangulo* piso41=new Rectangulo(412,211,120,20);
    Rectangulo* piso42=new Rectangulo(532,208,120,20);
    Rectangulo* piso43=new Rectangulo(652,203,50,20);
    Rectangulo* piso44=new Rectangulo(702,200,50,20);
    Rectangulo* piso45=new Rectangulo(752,195,60,20);

    Rectangulo* piso46=new Rectangulo(0,132,520,20);
    Rectangulo* piso47=new Rectangulo(520,136,65,20);
    Rectangulo* piso48=new Rectangulo(585,140,65,20);
    Rectangulo* piso49=new Rectangulo(630,145,65,20);//esta es la que tiene la escalera abajo
    Rectangulo* piso50=new Rectangulo(695,149,65,20);

    Rectangulo* piso51=new Rectangulo(350,62,150,20);

    Rectangulo* escalera_debug=new Rectangulo(500,0,50,600);

    Rectangulo* escalera1=new Rectangulo(675,466,50,25);
    Rectangulo* escalera2=new Rectangulo(360,363,20,48);
    Rectangulo* escalera3=new Rectangulo(120,370,20,30);
    Rectangulo* escalera4=new Rectangulo(410,285,20,48);
    Rectangulo* escalera5=new Rectangulo(680,290,20,28);
    Rectangulo* escalera6=new Rectangulo(263,205,20,40);
    Rectangulo* escalera7=new Rectangulo(120,210,20,30);
    Rectangulo* escalera8=new Rectangulo(680,130,5,30);
    Rectangulo* escalera9=new Rectangulo(470,50,10,40);

    this->agregarRectangulo(piso1);
    this->agregarRectangulo(piso2);
    this->agregarRectangulo(piso3);
    this->agregarRectangulo(piso4);
    this->agregarRectangulo(piso5);
    this->agregarRectangulo(piso6);
    this->agregarRectangulo(piso7);

    this->agregarRectangulo(piso8);
    this->agregarRectangulo(piso9);
    this->agregarRectangulo(piso10);
    this->agregarRectangulo(piso11);
    this->agregarRectangulo(piso12);
    this->agregarRectangulo(piso13);
    this->agregarRectangulo(piso14);
    this->agregarRectangulo(piso15);
    this->agregarRectangulo(piso16);
    this->agregarRectangulo(piso17);
    this->agregarRectangulo(piso18);
    this->agregarRectangulo(piso19);
    this->agregarRectangulo(piso20);
    this->agregarRectangulo(piso21);
    this->agregarRectangulo(piso22);
    this->agregarRectangulo(piso23);
    this->agregarRectangulo(piso24);
    this->agregarRectangulo(piso25);
    this->agregarRectangulo(piso26);
    this->agregarRectangulo(piso27);
    this->agregarRectangulo(piso28);
    this->agregarRectangulo(piso29);

    this->agregarRectangulo(piso30);
    this->agregarRectangulo(piso31);
    this->agregarRectangulo(piso32);
    this->agregarRectangulo(piso33);
    this->agregarRectangulo(piso34);
    this->agregarRectangulo(piso35);
    this->agregarRectangulo(piso36);

    this->agregarRectangulo(piso37);
    this->agregarRectangulo(piso38);
    this->agregarRectangulo(piso39);
    this->agregarRectangulo(piso40);
    this->agregarRectangulo(piso41);
    this->agregarRectangulo(piso42);
    this->agregarRectangulo(piso43);
    this->agregarRectangulo(piso44);
    this->agregarRectangulo(piso45);
    this->agregarRectangulo(piso46);
    this->agregarRectangulo(piso47);
    this->agregarRectangulo(piso48);
    this->agregarRectangulo(piso49);
    this->agregarRectangulo(piso50);
    this->agregarRectangulo(piso51);
    this->agregarEscalera(escalera1);
    this->agregarEscalera(escalera2);
    this->agregarEscalera(escalera3);
    this->agregarEscalera(escalera4);
    this->agregarEscalera(escalera5);
    this->agregarEscalera(escalera6);
    this->agregarEscalera(escalera7);
    this->agregarEscalera(escalera8);
    this->agregarEscalera(escalera9);
}


Modelo_Jugador* Modelo::getModeloJugador(int posicion)
{
    return this->modelosPersonajes[posicion] ;
}

int Modelo::getCantJugadores()
{
    return this->modelosPersonajes.size();
}

void Modelo::acciones()
{
    for (int i = 0; i < modelosPersonajes.size(); i++) {
        for (int j = 0; j < nombreJugadores.size(); j++) {
            //TODO hay que recorrer nombreJugadores en vez de hardcodear el "mario"
            if (this->modelosPersonajes[i]->getNombre()==nombreJugadores[j])
            {
            this->modelosPersonajes[i]->fijarAnimacionMovimiento();
            }
        }
        if (this->modelosPersonajes[i]->getNombre()=="barril")
        {
          this->modelosPersonajes[i]->caminar() ;

        } else
        {
          this->modelosPersonajes[i]->caminar();

          if(this->modelosPersonajes[i]->getNombre()=="fueguito"){
              /*if(this->contador<=100){
              this->modelosPersonajes[i]->setPosicionX(this->modelosPersonajes[i]->getPosicionX()+1);
              }
              else{
                  this->modelosPersonajes[i]->setPosicionX(this->modelosPersonajes[i]->getPosicionX()-1);
              }
                  if (this->contador>=200){
                      this->contador = 0;
                  }*/
          }
          else if (this->modelosPersonajes[i]->getNombre()=="fueguito-default") {
             /* if(this->contador<100){
              this->modelosPersonajes[i]->setPosicionX(this->modelosPersonajes[i]->getPosicionX()+1);
              }
              else{
                  this->modelosPersonajes[i]->setPosicionX(this->modelosPersonajes[i]->getPosicionX()-1);
              }
                  if (this->contador>200){
                      this->contador = 0;
                  }*/
          }

          //condicion para la plataforma
          if(this->modelosPersonajes[i]->getNombre()=="plataforma"){
              this->modelosPersonajes[i]->caminar2();
          }
          if(this->modelosPersonajes[i]->getNombre()=="plataforma_derecha"){
              this->modelosPersonajes[i]->caminar2();
          }
          this->contador = this->contador+1;
        }
    }

    //aca quiero chequear las colisiones, al final de las acciones
    this->colisionador.mantenerElementosEnPantalla();
    this->colisionador.chequearColision();
}


void Modelo::agregarObjetosAlColisionador()
{
    for(int i=0; i < modelosPersonajes.size(); i++){
        //NOTA: ESTO FUNCIONA SOLO PORQUE TENGO UN SOLO MARIO
        //AMPLIAR AL MOMENTO DE AGREGAR VARIOS MARIOS AL COLISIONADOR
        for (int j = 0; j < nombreJugadores.size(); j++) {
            //TODO hay que recorrer nombreJugadores en vez de hardcodear el "mario"
            if (this->modelosPersonajes[i]->getNombre()==nombreJugadores[j])
            {
                this->colisionador.agregarJugador(nombreJugadores[j],this->modelosPersonajes[i]);
            }
        }

        if(this->modelosPersonajes[i]->getNombre() == "plataforma"){
            this->colisionador.agregarPlataformaIzquierda(this->modelosPersonajes[i]);
        }
        if(this->modelosPersonajes[i]->getNombre() == "plataforma_derecha"){
            this->colisionador.agregarPlataformaDerecha(this->modelosPersonajes[i]);
        }
        if(this->modelosPersonajes[i]->getNombre() == "fueguito"){
            this->colisionador.agregarFueguito(this->modelosPersonajes[i]);
        }
    }
}

void Modelo::agregarRectangulo(Rectangulo* rectangulo){
    this->colisionador.agregarRectangulo(rectangulo);
}

void Modelo::recibirTecla(int tecla_apretada, std::string nombre_jugador){
    this->colisionador.recibirTecla(tecla_apretada,nombre_jugador);
}

void Modelo::agregarEscalera(Rectangulo* rectangulo){
    this->colisionador.agregarEscalera(rectangulo);
}
