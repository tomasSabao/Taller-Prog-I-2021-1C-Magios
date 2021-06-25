#ifndef CONEXION_H
#define CONEXION_H


class Conexion
{
    public:
        Conexion();
        virtual ~Conexion();
        void setearConexion(int socket);
        void setearId(int id);
        void setearEstado(bool estado);
        int getConexion();
        bool getEstado();
        int getId();

    protected:
        bool estado;
        int conexion;
        int id;

    private:
};

#endif // CONEXION_H
