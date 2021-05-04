class Mario{

public:
	Mario();
	virtual ~Mario();

	void traducirTecla(int tecla_apretada);
	int getPosicionX();
	int getPosicionY();
	void mover();
	void imprimirPosicion();
	void imprimirVelocidad();
	void aplicarGravedad();

private:
	void aumentarVelocidadX();
	void reducirVelocidadX();
	void aumentarVelocidadY();
	void reducirVelocidadY();





	int velocidad_horizontal=5;

	//con velocidad_vertical=20 el pico del salto es de 50
	int velocidad_vertical=20;
	int gravedad=5;

	int velocidad_x=0;
	int velocidad_y=0;
	int posicion_x=0;
	int posicion_y=0;

};
