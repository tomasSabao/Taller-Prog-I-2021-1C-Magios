#ifndef RECTANGULO_H
#define RECTANGULO_H


class Rectangulo
{
    public:
        Rectangulo(int posX,int posY,int ancho,int alto);
        int getPosX();
        int getPosY();
        int getAncho();
        int getAlto();
        virtual ~Rectangulo();

    protected:

    private:

   	int posx;
   	int posy;
   	int ancho;
   	int alto;
};

#endif // RECTANGULO_H
