#ifndef CONEXION_H
#define CONEXION_H
typedef enum{DESCONECTADO=0,LOGIN=1,ACTIVO=2} status_t;

typedef struct Modelo Modelo;

class Conexion
{
    public:
        Conexion();
        virtual ~Conexion();
        void  setearSocket(int socket);
        void  setearEstado(status_t estado);
        status_t  getEstado( );
        int getSocket( );


    protected:
   status_t estado;// 0 es desconectado, 1 es paso login , 2 es activo
    int socket;


    private:
};

#endif // CONEXION_H
