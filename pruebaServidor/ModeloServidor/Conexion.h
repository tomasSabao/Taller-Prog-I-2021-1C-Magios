#ifndef CONEXION_H
#define CONEXION_H


class Conexion
{
    public:
        Conexion();
        virtual ~Conexion();
        void  setearConexion(int socket);


void  setearEstado(bool estado);


    protected:
    bool estado;
    int conexion;


    private:
};

#endif // CONEXION_H
