#include "Conexion.h"

Conexion::Conexion()
{
    //ctor
}

Conexion::~Conexion()
{
    //dtor
}


void Conexion::setearConexion(int socket)
{
    this->conexion=socket;
}

void Conexion::setearEstado(bool estado)
{
    this->estado=estado;
}
